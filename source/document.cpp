#include "document.h"
#include "libxml/parser.h"
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>


#include <raptor2.h>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

using namespace sbol;
using namespace std;

unordered_map<string, SBOLObject&(*)()> sbol::SBOL_DATA_MODEL_REGISTER =
{
	// Typecast proxy constructors to a constructor for SBOL
	// This makes some ugly syntax, but library users should never see it.
	make_pair(UNDEFINED, &create<SBOLObject>),
	make_pair(SBOL_COMPONENT_DEFINITION, (SBOLObject&(*)()) &create<ComponentDefinition>),
	make_pair(SBOL_SEQUENCE_ANNOTATION, (SBOLObject&(*)()) &create<SequenceAnnotation>),
	make_pair(SBOL_SEQUENCE, (SBOLObject&(*)()) &create<Sequence>),
	make_pair(SBOL_COMPONENT, (SBOLObject&(*)()) &create<Component>),
	make_pair(SBOL_FUNCTIONAL_COMPONENT, (SBOLObject&(*)()) &create<FunctionalComponent>),
	make_pair(SBOL_MODULE_DEFINITION, (SBOLObject&(*)()) &create<ModuleDefinition>),
	make_pair(SBOL_MODULE, (SBOLObject&(*)()) &create<Module>),
	make_pair(SBOL_INTERACTION, (SBOLObject&(*)()) &create<Interaction>),
	make_pair(SBOL_PARTICIPATION, (SBOLObject&(*)()) &create<Participation>),
	make_pair(SBOL_MODEL, (SBOLObject&(*)()) &create<Model>),
	make_pair(SBOL_SEQUENCE_CONSTRAINT, (SBOLObject&(*)()) &create<SequenceConstraint>),
	make_pair(SBOL_RANGE, (SBOLObject&(*)()) &create<Range>)
};

void sbol::seekElement(std::istringstream& xml_buffer, std::string uri)
{
	string SEARCH_TOKEN = NODENAME_ABOUT "=\"" + uri + "\"";

	seekNextElement(xml_buffer);
	while (xml_buffer)
	{
		int START_OF_ELEMENT = xml_buffer.tellg();
		// Parse element into qname and tag 
		// This assumes xml elements have a certain form which is not generally true,
		// so sometimes the parsed qname and about_id will not make sense
		vector<string> subtokens = parseElement(xml_buffer);
		std::string qname = subtokens.front();
		std::string about_id = subtokens.back();
		if (about_id.compare(SEARCH_TOKEN) == 0 && isOpenNode(xml_buffer))
		{
			cout << "Found element" << about_id << endl;
			xml_buffer.seekg(START_OF_ELEMENT);
			return;
		}
		xml_buffer.get();  // Advance the stream one byte, so we don't get trapped in an infinite loop
		seekNextElement(xml_buffer);
	}
	return;
};

void sbol::seekNextElement(std::istringstream& xml_buffer)
{
	char inchar;
	while (xml_buffer.get(inchar))
	{
		if (inchar == '<')
		{
			xml_buffer.unget();
			return;
		}
	}
	return;
};

void sbol::seekEndOfElement(std::istringstream& xml_buffer)
{
	// Scan to end of XML element
	char inchar;
	while (xml_buffer.get(inchar))
	{
		if (inchar == '>')
		{
			xml_buffer.unget();
			return;
		}
	}
};

string sbol::getQName(istringstream& xml_buffer)
{
	vector<string> subtokens = parseElement(xml_buffer);
	return subtokens.front();
};

string sbol::getLocalPart(string qname)
{
	size_t pos;
	if ((pos = qname.find(':')) == std::string::npos)
		return "";
	else
		return qname.substr(pos + 1, qname.length() - pos);
};

string sbol::getPrefix(string qname)
{
	size_t pos;
	if ((pos = qname.find(':')) == std::string::npos)
		return "";
	else
		return qname.substr(0, pos);
};

void sbol::seekEndOfNode(std::istringstream& xml_buffer, std::string uri)
{
	seekElement(xml_buffer, uri);  // Seek open element
	int START_OF_ELEMENT = xml_buffer.tellg();

	// The qname for open element is the search term for close element
	vector<string> subtokens = parseElement(xml_buffer);
	std::string qname = subtokens.front();
	std::string SEARCH_TOKEN = qname;  
	
	seekNextElement(xml_buffer);
	while (xml_buffer)
	{
		
		// Parse element into qname and tag 
		// This assumes xml elements have a certain form which is not generally true,
		// so sometimes the parsed qname and about_id will not make sense
		vector<string> subtokens = parseElement(xml_buffer);
		std::string qname = subtokens.front();
		if (qname.compare(SEARCH_TOKEN) == 0 && !isOpenNode(xml_buffer)) // Check if it's a close node
		{
			seekEndOfElement(xml_buffer);
			return;
		}
		xml_buffer.get();  // Advance the stream one byte, so we don't get trapped in an infinite loop
		seekNextElement(xml_buffer);
	}
	return;
};

void sbol::seekNewLine(std::istringstream& xml_buffer)
{
	char inchar;
	while (xml_buffer.unget())
	{
		xml_buffer.get(inchar);
		if (inchar == '\n')
			return;
		else
			xml_buffer.unget();
	}
	return;
};

void sbol::seekEndOfLine(std::istringstream& xml_buffer)
{
	char inchar;
	while (xml_buffer.get(inchar))
	{
		if (inchar == '\n')
			return;
	}
	return;
};

void sbol::seekResource(std::istringstream& xml_buffer, std::string uri)
{
	string SEARCH_TOKEN = NODENAME_RESOURCE "=\"" + uri + "\"";
	seekNextElement(xml_buffer);
	while (xml_buffer)
	{
		int START_OF_ELEMENT = xml_buffer.tellg();
		// Parse element into qname and tag 
		// This assumes xml elements have a certain form which is not generally true,
		// so sometimes the parsed qname and resource_id will not make sense
		vector<string> subtokens = parseElement(xml_buffer);
		std::string resource_id = subtokens.back();

		if (resource_id.compare(SEARCH_TOKEN) == 0 && isOpenNode(xml_buffer))
		{
			cout << "Found resource " << resource_id << endl;
			xml_buffer.seekg(START_OF_ELEMENT);
			return;
		}
		xml_buffer.get();  // Advance the stream one byte, so we don't get trapped in an infinite loop
		seekNextElement(xml_buffer);
	}
	return;
}

std::vector<std::string> sbol::parseElement(std::istringstream& xml_buffer)
{
	// Parse XML element into qname and attribute tags
	vector<string> element_subtokens;
	int START_OF_ELEMENT = xml_buffer.tellg();
	bool END_OF_ELEMENT = false;

	std::string token;
	xml_buffer >> token;
	while (!END_OF_ELEMENT && token.size() > 0)
	{

		// Trim angle brackets
		if (token[0] == '<')
		{
			token = token.substr(1, token.size() - 1);
			if (token[0] == '/') token = token.substr(1, token.size() - 1);
		}
		if (token[token.size() - 1] == '>')
		{
			END_OF_ELEMENT = true;
			token = token.substr(0, token.size() - 1);
			if (token[token.size() - 1] == '/') token = token.substr(0, token.size() - 1);
		}
		element_subtokens.push_back(token);
		xml_buffer >> token;
	}
	xml_buffer.seekg(START_OF_ELEMENT);
	return element_subtokens;
};

bool sbol::isOpenNode(std::istringstream& xml_buffer)
{
	bool IS_OPEN_NODE;
	int START_OF_ELEMENT = xml_buffer.tellg();
	char inchar;

	if (xml_buffer.get() == '<')
	{
		IS_OPEN_NODE = true;
		if (xml_buffer.get() == '/')
		{
			IS_OPEN_NODE = false;
		}
	}
	xml_buffer.seekg(START_OF_ELEMENT);
	return IS_OPEN_NODE;
};

std::string sbol::cut(std::istringstream& xml_buffer, int start, int length)
{
	char * cut_buffer = new char[length + 1];
	cut_buffer[length] = '\0';
	xml_buffer.seekg(start);
	xml_buffer.read(cut_buffer, length);
	string cut_string = string(cut_buffer);
	delete cut_buffer;
	return cut_string;
};

void sbol::indent(std::string& text, int indentation)
{
	size_t LINE_START = 0;
	size_t END_OF_LINE = 0;
	while ((END_OF_LINE = text.find('\n', LINE_START)) != std::string::npos)
	{
		text.insert(LINE_START, string(indentation, ' '));
		END_OF_LINE = END_OF_LINE + indentation;
		LINE_START = END_OF_LINE + 1;
	}
};

std::string sbol::getXMLNode(std::string xml_buffer, std::string uri)
{
	string search_token = NODENAME_ABOUT "=\"" + uri + "\"";
	string search_qname;
	bool OPEN_ELEMENT, CLOSE_ELEMENT;
	istringstream buffer_stream;
	buffer_stream.str(xml_buffer);
	char inchar = 1;
	char * element;

	int EOL = 0;
	int start_tag, end_tag, start_node, end_node;
	while (buffer_stream.get(inchar)) 
	{
		// Make note of newlines, because it's important for determining indentation level
		if (inchar == '\n') EOL = buffer_stream.tellg();
		
		// Start reading XML element
		if (inchar == '<') 
		{
			start_tag = buffer_stream.tellg();
			start_tag = start_tag - 1;

			// Scan the next char to determine if this is an open or close XML element
			buffer_stream.get(inchar);
			if (inchar == '/')
			{
				CLOSE_ELEMENT = true;
				OPEN_ELEMENT = false;
			}
			else
			{
				CLOSE_ELEMENT = false;
				OPEN_ELEMENT = true;
			}
			// Scan to end of XML element
			while (inchar != '>')
			{
				buffer_stream.get(inchar);
			}
			end_tag = buffer_stream.tellg();
			end_tag = end_tag - 1;
			
			// Parse XML element into qname and attribute tags
			istringstream element;
			vector<string> element_subtokens;
			std::string qname = "";
			std::string about_id = "";
			element.str(xml_buffer);  // Begin from last EOL, including white space for indentation preceding XML element
			element.seekg(start_tag);
			while (element.tellg() < end_tag)
			{
				std::string token;
				element >> token;

				// Trim angle brackets
				if (token[0] == '<')
				{
					token = token.substr(1, token.size() - 1);
					if (token[0] == '/') token = token.substr(1, token.size() - 1);
				}
				if (token[token.size() - 1] == '>')
				{
					token = token.substr(0, token.size() - 1);
					if (token[token.size() - 1] == '/') token = token.substr(0, token.size() - 1);
				}
				element_subtokens.push_back(token);
			}

			// Parse element into qname and tag
			about_id = element_subtokens.back();
			qname = element_subtokens.front();

			if (OPEN_ELEMENT)
			{
				// Check if this element matches the uri we are searching for 
				if (about_id.compare(search_token) == 0)
				{
					start_node = EOL;  // Cut text from raptor output starting at last EOL
					search_qname = qname;
				}
			}
			else if (CLOSE_ELEMENT)
			{
				if (qname.compare(search_qname) == 0)
				{
					end_node = end_tag + 1;

					std::string cut_string = xml_buffer.substr(start_node, end_node - start_node);
					cout << cut_string;
					cout << (int)cut_string[cut_string.size() - 2] << (int)cut_string[cut_string.size() - 1] << endl << endl;
					return cut_string;

				}
			}
		}
	}
	cout << "Done " << endl;
	buffer_stream.clear();
	return "";
};

// Not finished!  A general recursive algorith which returns a flattened vector of all the objects in the document
vector<SBOLObject *> Document::flatten()
{
	vector<SBOLObject *> list_of_sbol_obj;
	// Iterate through objects in document and serialize them
	for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
	{
		//obj_i->second->serialize(sbol_serializer);
		list_of_sbol_obj.push_back(obj_i->second);
		cout << obj_i->second->identity.get() << endl;
	}
	return list_of_sbol_obj;
};

std::string SBOLObject::nest(std::string& rdfxml_string)
{
	// Serialize all properties corresponding to black diamonds in UML diagrams
	// RDF-XML list/container elements
	for (auto i = owned_objects.begin(); i != owned_objects.end(); ++i)
	{
		// Recurse through each object in the object store that belongs to this property
		std::string property_name = i->first;
		vector<SBOLObject*> object_store = i->second;

		if (object_store.size() > 0)
		{
			for (auto o = object_store.begin(); o != object_store.end(); ++o)
			{
				SBOLObject* obj = *o;
		 		rdfxml_string = obj->nest(rdfxml_string);
				istringstream rdfxml_buffer;
				rdfxml_buffer.str(rdfxml_string);

				// Procedure for structuring the data starts here
				int repl_start, repl_end, repl_length;  // Marks the start and end of the reference node to be replaced
				int cut_start, cut_end, cut_length;  // Marks the start and end of the child node that will be substituted in place of the reference node
				int node_start, indentation;

				// Find the cut for the OwnedObject.
				seekElement(rdfxml_buffer, obj->identity.get());
				cout << "found element at " << rdfxml_buffer.tellg() << endl;
				node_start = rdfxml_buffer.tellg();
				
				//// Reformat the QName, it should have the format sbol:sbolProperty
				//string qname = getQName(rdfxml_buffer);
				//string local_part = getLocalPart(qname);
				//local_part[0] = tolower(local_part[0]);
				//string prefix = getPrefix(qname);
				//qname = prefix + ":" + local_part;

				seekNewLine(rdfxml_buffer);
				cut_start = rdfxml_buffer.tellg();
				cout << "start cut at " << cut_start << endl;
				seekEndOfNode(rdfxml_buffer, obj->identity.get());
				seekEndOfLine(rdfxml_buffer);
				cut_end = rdfxml_buffer.tellg();
				cout << "end cut at " << cut_end << endl;
				cut_length = cut_end - cut_start;

				// Cut text
				//string cut_string = cut(rdfxml_buffer, cut_start, cut_length);
				string cut_string = rdfxml_string.substr(cut_start, cut_length);
				rdfxml_string.replace(cut_start, cut_length, "");  // Cut

				// Find uri reference to resource (a reference to the OwnedObject)
				//rdfxml_buffer.seekg(0);
				rdfxml_buffer.str(rdfxml_string);
				cout << "Seeking " << obj->identity.get() << endl;
				cout << "start" << rdfxml_buffer.tellg() << endl;
				seekResource(rdfxml_buffer, obj->identity.get());
				cout << "Resource at " << rdfxml_buffer.tellg() << endl;
				node_start = rdfxml_buffer.tellg();
				//string qname = getQName(rdfxml_buffer);
				seekNewLine(rdfxml_buffer);
				cout << "Start replacement at " << rdfxml_buffer.tellg() << endl;
				repl_start = rdfxml_buffer.tellg();
				indentation = node_start - repl_start;
				// Reformat the QName, it should have the format sbol:sbolProperty
				string qname = getQName(rdfxml_buffer);
				string local_part = getLocalPart(qname);
				local_part[0] = tolower(local_part[0]);
				string prefix = getPrefix(qname);
				qname = prefix + ":" + local_part;

				seekEndOfLine(rdfxml_buffer);
				repl_end = rdfxml_buffer.tellg();
				cout << "End replacement at " << rdfxml_buffer.tellg() << endl;
				repl_length = repl_end - repl_start;
				string repl_string = rdfxml_string.substr(repl_start, repl_length);
				indent(cut_string, indentation);
				string open_element = string(indentation, ' ') + "<" + qname + ">\n";
				string close_element = string(indentation, ' ') + "</" + qname + ">\n";
				string modified_cut_string = open_element + cut_string + close_element;

				rdfxml_string.replace(repl_start, repl_length, modified_cut_string);
				cout << rdfxml_string << endl;
				getchar();
			}
		}
	}
	return rdfxml_string;
};

void Document::parse_objects(void* user_data, raptor_statement* triple)
{
	Document *doc = (Document *)user_data;

	string subject = reinterpret_cast<char*>(raptor_term_to_string(triple->subject));
	string predicate = reinterpret_cast<char*>(raptor_term_to_string(triple->predicate));
	string object = reinterpret_cast<char*>(raptor_term_to_string(triple->object));
	
	subject = subject.substr(1, subject.length() - 2);  // Removes flanking < and > from uri
	predicate = predicate.substr(1, predicate.length() - 2);  // Removes flanking < and > from uri
	object = object.substr(1, object.length() - 2);  // Removes flanking < and > from uri

	// Triples that have a predicate matching the following uri signal to the parser that a new SBOL object should be constructred
	if (predicate.compare("http://www.w3.org/1999/02/22-rdf-syntax-ns#type") == 0)
	{
		// Checks if the object has already been created and whether a constructor for this type of object exists
		if ((doc->SBOLObjects.count(subject) == 0) && (SBOL_DATA_MODEL_REGISTER.count(object) == 1))
		{
			SBOLObject& new_obj = SBOL_DATA_MODEL_REGISTER[ object ]();  // Call constructor for the appropriate SBOLObject

			// Wipe default property values passed from default constructor. New property values will be added as properties are parsed from the input file
			for (auto it = new_obj.properties.begin(); it != new_obj.properties.end(); it++)
			{
				std::string token = it->second.front();
				if (token[0] == '<')  // clear defaults and re-initialize this property as a URI
				{
					new_obj.properties[it->first].clear();
					new_obj.properties[it->first].push_back("<>");
				} 
				else if (token[0] == '"')  // clear defaults and re-initialize as a literal
				{
					new_obj.properties[it->first].clear();
					new_obj.properties[it->first].push_back("\"\"");
				}
			}
			new_obj.identity.set(subject);

			// All created objects are placed in the document's object store.  However, only toplevel objects will be left permanently.
			// Owned objects are kept in the object store as a temporary convenience and will be removed later.
			doc->add<SBOLObject>(new_obj);
		}
	}

}

void Document::parse_properties(void* user_data, raptor_statement* triple)
{
	Document *doc = (Document *)user_data;

	string subject = reinterpret_cast<char*>(raptor_term_to_string(triple->subject));
	string predicate = reinterpret_cast<char*>(raptor_term_to_string(triple->predicate));
	string object = reinterpret_cast<char*>(raptor_term_to_string(triple->object));



	string id = subject.substr(1, subject.length() - 2);  // Removes flanking < and > from the uri
	string property_uri = predicate.substr(1, predicate.length() - 2);  // Removes flanking < and > from uri
	//string property_value = object.substr(1, object.length() - 2);  // Removes flanking " from literal
	string property_value = object;


	std::size_t found = property_uri.find('#');
	if (found != std::string::npos)
	{
		string property_ns = property_uri.substr(0, found);
		string property_name = property_uri.substr(found + 1, subject.length() - 1);
		// If property name is something other than "type" than the triple matches the pattern for defining properties
		if (property_uri.compare(RDF_URI "#type") != 0)
		{
			cout << "Parsing " << property_uri << endl;
			// Checks if the object to which this property belongs already exists
			if (doc->SBOLObjects.find(id) != doc->SBOLObjects.end())
			{
				TopLevel *sbol_obj = doc->SBOLObjects[id];
				// Decide if this triple corresponds to a simple property, a list property, an owned property or a referenced property
				if (sbol_obj->properties.find(property_uri) != sbol_obj->properties.end())
				{
					// TODO: double-check this, is there a memory-leak here?
					// sbol_obj->properties[property_uri].clear();
					sbol_obj->properties[property_uri].push_back(property_value);
				}
				// TODO: the list_properties member should be deprecated, use properties member instead
				else if (sbol_obj->list_properties.find(property_uri) != sbol_obj->list_properties.end())
				{
					sbol_obj->list_properties[property_uri].push_back(property_value);
				}
				else if (sbol_obj->owned_objects.find(property_uri) != sbol_obj->owned_objects.end())
				{
					// Strip off the angle brackets from the URI value.  Note that a Document's object_store
					// and correspondingly, an SBOLObject's property_store uses stripped URIs as keys,
					// while libSBOL uses as a convention angle brackets or quotes for Literal values
					string owned_obj_id = property_value.substr(1, property_value.length() - 2);
					
					// Form a composite SBOL data structure.  The owned object is added to its parent
					// TopLevel object.  The owned object is then removed from its temporary location in the Document's object store
					// and is now associated only with it's parent TopLevel object.
					TopLevel *owned_obj = doc->SBOLObjects[owned_obj_id];
					sbol_obj->owned_objects[property_uri].push_back(owned_obj);			
					doc->SBOLObjects.erase(owned_obj_id);
				}
				else if (doc->SBOLObjects.find(property_value.substr(1,property_value.length()-2)) != doc->SBOLObjects.end())
				{
					cout << property_name << " is owned by " << id << endl;
				}
				else
				{
					cout << property_value.substr(1, property_value.length() - 2) << " is not in property store" << endl;
					cout << property_name << " is not recognized as a property of " << id << endl;
				}
			}
		}
	}
}


void Document::read(std::string filename)
{
	// Wipe existing contents of this Document
	raptor_free_world(this->rdf_graph);  //  Probably need to free other objects as well...
	this->rdf_graph = raptor_new_world();
	SBOLObjects.clear();

	FILE* fh = fopen(filename.c_str(), "rb");
	raptor_parser* rdf_parser = raptor_new_parser(this->rdf_graph, "rdfxml");
	raptor_iostream* ios = raptor_new_iostream_from_file_handle(this->rdf_graph, fh);
	unsigned char *uri_string;
	raptor_uri *uri, *base_uri;
	
	void *user_data = this;
	raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_objects);
	raptor_uri *sbol_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)SBOL_URI "#");
	raptor_parser_parse_iostream(rdf_parser, ios, sbol_uri);

	raptor_free_iostream(ios);
	rewind(fh);
	ios = raptor_new_iostream_from_file_handle(this->rdf_graph, fh);
	raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_properties);
	raptor_parser_parse_iostream(rdf_parser, ios, sbol_uri);

	raptor_free_uri(sbol_uri);
	raptor_free_iostream(ios);
	raptor_free_parser(rdf_parser);

	fclose(fh);

}



void SBOLObject::serialize(raptor_serializer* sbol_serializer, raptor_world *sbol_world)
{
	// Check if there is an RDF graph associated with this SBOLObject.  Only TopLevel objects can be belong to SBOL Documents, so
	// only TopLevel objects have a valid back-pointer.
	//
	// The only other type of SBOL Object that can serialize besides TopLevel are objects
	// that form a composite with a TopLevel object.  In this case, the TopLevel object will pass the
	// pointer to the RDF graph to its composite objects


	if (doc)
	{
		sbol_world = doc->getWorld();
	}
	if (sbol_world)
	{
				
		// This RDF triple makes the following statement:
		// "This instance of an SBOL object belongs to class X"
		raptor_statement *triple = raptor_new_statement(sbol_world);
		std::string subject = identity.get();
		std::string predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
		std::string object = type;

		triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
		triple->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
		triple->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());

		// Write the triples
		raptor_serializer_serialize_statement(sbol_serializer, triple);

		// Delete the triple 
		raptor_free_statement(triple);

		for (auto it = properties.begin(); it != properties.end(); ++it)
		{

			// This RDF triple makes the following statement:
			// "This SBOL object has a property called X and its value is Y"
			raptor_statement *triple2 = raptor_new_statement(sbol_world);

			std::string new_predicate = it->first;  // The triple's predicate identifies an SBOL property

			// Serialize each of the values in a List property as an RDF triple
			vector<std::string> property_values = it->second;
			for (auto i_val = property_values.begin(); i_val != property_values.end(); ++i_val)
			{
				std::string new_object = *i_val;
				triple2->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
				triple2->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)new_predicate.c_str());
				
				// TODO:  the condition below, new_object.length() > 2, should be replaced with a function is_empty()
				if (new_object.length() > 2 && new_object.front() == '<' && new_object.back() == '>') // Angle brackets indicate a uri
				{
					new_object = new_object.substr(1, new_object.length() - 2);  // Strip angle brackets
					triple2->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)new_object.c_str());

					// Write the triples, but don't write the identity property (it results in a redundant XML element)
					// TODO: squelching the identity property like this is kludgey.  There's probably a more efficient way to squelch properties
					if (new_predicate.compare(SBOL_IDENTITY) != 0) raptor_serializer_serialize_statement(sbol_serializer, triple2);
				}
				else if (new_object.length() > 2 && new_object.front() == '"' && new_object.back() == '"')  // Quotes indicate a literal
				{
					new_object = new_object.substr(1, new_object.length() - 2);  // Strip quotes
					triple2->object = raptor_new_term_from_literal(sbol_world, (const unsigned char *)new_object.c_str(), NULL, NULL);

					// Write the triples
					raptor_serializer_serialize_statement(sbol_serializer, triple2);
				}
			}

			// Delete the triple 
			raptor_free_statement(triple2);
		}

		// Serialize all properties corresponding to black diamonds in UML diagrams
		// RDF-XML list/container elements
		for (auto i = owned_objects.begin(); i != owned_objects.end(); ++i)
		{
			// Serialize each object in the object store that belongs to this property
			std::string property_name = i->first;
			vector<SBOLObject*> object_store = i->second;

			if (object_store.size() > 0)
			{
				// TODO:  this triple appears to be unneccessary and creates an extra 
				// xml node in serialization <rdf:type rdf:resource="someSBOLProperty">
				// Double check this conclusion and remove code as necessary

				// This RDF triple makes the following statement:
				// "This instance of an SBOL object has property called X"
				raptor_statement *triple2 = raptor_new_statement(sbol_world);
				subject = identity.get();
				predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
				object = property_name;

				triple2->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
				triple2->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
				triple2->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());

				// Write the triples
				//raptor_serializer_serialize_statement(sbol_serializer, triple2);

				// Delete the triple 
				raptor_free_statement(triple2);

				int i_o = 0;
				for (auto o = object_store.begin(); o != object_store.end(); ++o)
				{
					SBOLObject* obj = *o;
					++i_o;

					// This RDF triple makes the following statement:
					// "This instance of an SBOL object owns another SBOL object"
					raptor_statement *triple = raptor_new_statement(sbol_world);
					std::string subject = identity.get();
					std::string predicate = property_name;
					std::string object = obj->identity.get();

					//std::string subject = property_name;
					//std::string predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#_" + std::to_string(i_o);
					//std::string object = obj->identity.get();

					//triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
					triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
					triple->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
					triple->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());

					// Write the triples
					raptor_serializer_serialize_statement(sbol_serializer, triple);

					// Delete the triple 
					raptor_free_statement(triple);

					// Recursive call to serialize child objects
					obj->serialize(sbol_serializer, sbol_world);
				}

			}  // if

		} // for
		// End serialization 
	} // if
}

void TopLevel::addToDocument(Document& doc)
{
	//doc.SBOLObjects[this->identity.get()] = this;
	doc.add(*this);
};

TopLevel& Document::getTopLevel(string uri)
{
    // @TODO validate if object is TopLevel or else trigget a libSBOL error
	// @TODO return libSBOL error if URI not found
	return *(this->SBOLObjects[uri]);
};

raptor_world* Document::getWorld()
{
	// @TODO validate if object is TopLevel or else trigget a libSBOL error
	// @TODO return libSBOL error if URI not found
	return (this->rdf_graph);
};

void Document::write(std::string filename)
{

	// Initialize raptor serializer
	FILE* fh = fopen(filename.c_str(), "wb");
	raptor_world* world = getWorld();
	raptor_serializer* sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");

	// Add default namespaces to Document
	//raptor_iostream* ios = raptor_new_iostream_to_file_handle(world, fh);
	raptor_uri *sbol_uri = raptor_new_uri(world, (const unsigned char *)SBOL_URI "#");
	raptor_uri *purl_uri = raptor_new_uri(world, (const unsigned char *)PURL_URI "#");
	raptor_uri *prov_uri = raptor_new_uri(world, (const unsigned char *)PROV_URI "#");

	const unsigned char *sbol_prefix = (const unsigned char *)"sbol";
	const unsigned char *purl_prefix = (const unsigned char *)"dcterms";
	const unsigned char *prov_prefix = (const unsigned char *)"prov";

	raptor_namespace_stack *sbol_namespaces = raptor_new_namespaces(world, 0);
	raptor_namespace *sbol_namespace = raptor_new_namespace_from_uri(sbol_namespaces, sbol_prefix, sbol_uri, 1);
	raptor_namespace *purl_namespace = raptor_new_namespace_from_uri(sbol_namespaces, purl_prefix, purl_uri, 1);
	raptor_namespace *prov_namespace = raptor_new_namespace_from_uri(sbol_namespaces, prov_prefix, prov_uri, 1);

	raptor_serializer_set_namespace_from_namespace(sbol_serializer, sbol_namespace);
	raptor_serializer_set_namespace_from_namespace(sbol_serializer, purl_namespace);
	raptor_serializer_set_namespace_from_namespace(sbol_serializer, prov_namespace);
	//raptor_serializer_start_to_file_handle(sbol_serializer, NULL, fh);

	char * sbol_buffer = "";
	size_t sbol_buffer_len;

	raptor_iostream* ios = raptor_new_iostream_to_string(world,
		(void **)&sbol_buffer,
		&sbol_buffer_len,
		NULL);
	int err = raptor_serializer_start_to_iostream(sbol_serializer, NULL, ios);
	if (err) cout << "Error starting iostream" << endl;
	err = raptor_serializer_start_to_string(sbol_serializer, NULL, (void **)&sbol_buffer, &sbol_buffer_len);
	if (err) cout << "Error " << err << "starting string" << endl;


	// Iterate through objects in document and serialize them
	for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
	{
		obj_i->second->serialize(sbol_serializer);
	}

	// Finalize serialization
	raptor_serializer_serialize_end(sbol_serializer);
	raptor_free_serializer(sbol_serializer);

	std::string sbol_buffer_string = std::string((char*)sbol_buffer);
	const int size = (const int)sbol_buffer_len;
	if (sbol_buffer)
	{
		cout << "Serializing " << size << " of document" << endl;
		cout << sbol_buffer_string << endl;
		// Iterate through objects in document and nest them
		for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
		{
			sbol_buffer_string = obj_i->second->nest(sbol_buffer_string);
		}
		fputs(sbol_buffer_string.c_str(), fh);
		//parseXMLNodes(sbol_buffer);
		//stringstream ss;
		//ss << sbol_buffer;
		//char buffer[255];
		//while (ss.getline(buffer, 255)) {
		//	cout << buffer << strlen(buffer) << endl;
		//	string sbol_buffer_string = string(buffer);
		//	size_t pos;
		//	if ((pos = sbol_buffer_string.find(identity.get())) != std::string::npos) {
		//		cout << "Found " << identity.get() << " at " << int(pos) << endl;
		//	}
		//}
		//ss.clear();
	}
	else
	{
		cout << "Serialization failed" << endl;
	}
	//std::string delimiter = "\n";
	//size_t pos = 0;
	//std::string token;
	//while ((pos = s.find(delimiter)) != std::string::npos) {
	//	token = s.substr(0, pos);
	//	std::cout << token << std::endl;
	//	s.erase(0, pos + delimiter.length());
	//}
	//std::cout << s << std::endl;
	raptor_free_iostream(ios);
	fclose(fh);

	// Begin pretty-writer of nested SBOL elements
	//xmlInitParser();
	//xmlDoc* xml_doc = xmlParseFile(filename.c_str());
	//xmlXPathContext* xml_context = xmlXPathNewContext(xml_doc);
	//xmlXPathObject* xpath_object;
	//
	//xmlNode* rdf_root = xmlDocGetRootElement(xml_doc);
	//xmlNode* sbol_root = rdf_root->children;
	//cout << sbol_root->name << endl;
	//xmlNode* sbol_node = sbol_root;
	//unordered_map<SBOLObject*, xmlNode*> top_level_objects;
	//unordered_map<std::string, xmlNode*> owned_objects;
	//while (sbol_node)
	//{
	//	if (sbol_node->type == XML_ELEMENT_NODE)
	//	{
	//		std::string uri = (std::string)(const char *)xmlGetNsProp(sbol_node, BAD_CAST NODENAME_ABOUT, BAD_CAST RDF_URI);
	//		//TopLevel& tl = getTopLevel((std::string)(const char *)uri_xml);
	//		cout << "Searching for " << uri << endl;
	//		// Check if this xml element corresponds to a TopLevel SBOL object.
	//		// If it is TopLevel, it should be registered in this Document's object store
	//		if (this->SBOLObjects.find(uri) != this->SBOLObjects.end())
	//		{
	//			SBOLObject* obj = this->SBOLObjects[uri];
	//			top_level_objects[obj] = sbol_node;
	//		}
	//		else
	//		{
	//			owned_objects[uri] = sbol_node;
	//		}
	//	}
	//	for (auto i_obj = this->SBOLObjects.begin(); i_obj != this->SBOLObjects.end(); ++i_obj)
	//	{
	//		SBOLObject* parent_obj = i_obj->second;
	//		xmlNode* parent_node = top_level_objects[parent_obj];
	//		for (auto i = parent_obj->owned_objects.begin(); i != parent_obj->owned_objects.end(); ++i)
	//		{
	//			// Serialize each object in the object store that belongs to this property
	//			std::string property_name = i->first;
	//			vector<SBOLObject*> object_store = i->second;
	//			cout << property_name << object_store.size() << endl;
	//			if (object_store.size() > 0)
	//			{
	//				for (auto o = object_store.begin(); o != object_store.end(); ++o)
	//				{
	//					//SBOLObject* child = *o;
	//					SBOLObject* child_obj = *o;
	//					cout << child_obj->identity.get() << endl;
	//					xmlNode* child_node = owned_objects[child_obj->identity.get()];
	//					parent_node = xmlAddChild(parent_node, child_node);
	//					cout << xmlChildElementCount(parent_node) << endl;
	//				}
	//			}
	//		}
	//	}
	//	sbol_node = sbol_node->next;
	//}
	//fh = fopen(filename.c_str(), "wb");

	//int test = xmlDocDump(fh, xml_doc);
	//cout << test << endl;
	////xmlFreeDoc(xml_doc);

};