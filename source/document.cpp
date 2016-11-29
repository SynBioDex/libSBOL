#include "document.h"

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

void sbol::seek_element(std::istringstream& xml_buffer, std::string uri)
{
	string SEARCH_TOKEN = NODENAME_ABOUT "=\"" + uri + "\"";

	seek_next_element(xml_buffer);
	while (xml_buffer)
	{
		int START_OF_ELEMENT = xml_buffer.tellg();
		// Parse element into qname and tag 
		// This assumes xml elements have a certain form which is not generally true,
		// so sometimes the parsed qname and about_id will not make sense
		vector<string> subtokens = parse_element(xml_buffer);
		std::string qname = subtokens.front();
		std::string about_id = subtokens.back();
		if (about_id.compare(SEARCH_TOKEN) == 0 && is_open_node(xml_buffer))
		{
			xml_buffer.seekg(START_OF_ELEMENT);
			return;
		}
		xml_buffer.get();  // Advance the stream one byte, so we don't get trapped in an infinite loop
		seek_next_element(xml_buffer);
	}
	return;
};

void sbol::seek_next_element(std::istringstream& xml_buffer)
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

void sbol::seek_end_of_element(std::istringstream& xml_buffer)
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

string sbol::get_qname(istringstream& xml_buffer)
{
	vector<string> subtokens = parse_element(xml_buffer);
    if (subtokens.size() == 0)
        throw SBOL_ERROR_SERIALIZATION;
	return subtokens.front();
};

string sbol::get_local_part(string qname)
{
	size_t pos;
	if ((pos = qname.find(':')) == std::string::npos)
		return "";
	else
		return qname.substr(pos + 1, qname.length() - pos);
};

string sbol::get_prefix(string qname)
{
	size_t pos;
	if ((pos = qname.find(':')) == std::string::npos)
		return "";
	else
		return qname.substr(0, pos);
};

void sbol::seek_end_of_node(std::istringstream& xml_buffer, std::string uri)
{
	seek_element(xml_buffer, uri);  // Seek open element
	int START_OF_ELEMENT = xml_buffer.tellg();

	// The qname for open element is the search term for close element
	vector<string> subtokens = parse_element(xml_buffer);
	std::string qname = subtokens.front();
	std::string SEARCH_TOKEN = qname;  
	
	seek_next_element(xml_buffer);
	while (xml_buffer)
	{
		
		// Parse element into qname and tag 
		// This assumes xml elements have a certain form which is not generally true,
		// so sometimes the parsed qname and about_id will not make sense
		vector<string> subtokens = parse_element(xml_buffer);
		std::string qname = subtokens.front();
		if (qname.compare(SEARCH_TOKEN) == 0 && !is_open_node(xml_buffer)) // Check if it's a close node
		{
			seek_end_of_element(xml_buffer);
			return;
		}
		xml_buffer.get();  // Advance the stream one byte, so we don't get trapped in an infinite loop
		seek_next_element(xml_buffer);
	}
	return;
};

void sbol::seek_new_line(std::istringstream& xml_buffer)
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

void sbol::seek_end_of_line(std::istringstream& xml_buffer)
{
	char inchar;
	while (xml_buffer.get(inchar))
	{
		if (inchar == '\n')
			return;
	}
	return;
};

void sbol::seek_resource(std::istringstream& xml_buffer, std::string property_name, std::string uri)
{
	string SEARCH_TOKEN = NODENAME_RESOURCE "=\"" + uri + "\"";
	seek_next_element(xml_buffer);
	while (xml_buffer)
	{
		int START_OF_ELEMENT = xml_buffer.tellg();
		// Parse element into qname and tag 
		// This assumes xml elements have a certain form which is not generally true,
		// so sometimes the parsed qname and resource_id will not make sense
		vector<string> subtokens = parse_element(xml_buffer);
        string qname = subtokens.front();
        string sbol_property_id = SBOL_URI "#" + get_local_part(qname);
		string resource_id = subtokens.back();
        if (resource_id.compare(SEARCH_TOKEN) == 0 && sbol_property_id.compare(property_name) == 0 && is_open_node(xml_buffer))
		{
			xml_buffer.seekg(START_OF_ELEMENT);
			return;
		}
		xml_buffer.get();  // Advance the stream one byte, so we don't get trapped in an infinite loop
		seek_next_element(xml_buffer);
	}
	return;
}

std::vector<std::string> sbol::parse_element(std::istringstream& xml_buffer)
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

bool sbol::is_open_node(std::istringstream& xml_buffer)
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

/*
As the first step in turning the flat RDF/XML serialization produced by Raptor into structured SBOL,
this procedure cuts the node corresponding to the specified resource. 
*/
std::string sbol::cut_sbol_resource(std::string& xml_string, const std::string resource_id)
{
	int cut_start, cut_end, cut_length;  // Marks the start and end of the child node that will be substituted in place of the reference node

	istringstream xml_buffer;
	xml_buffer.str(xml_string);

	// Find the cut for the OwnedObject.
	seek_element(xml_buffer, resource_id);
	seek_new_line(xml_buffer);
	cut_start = xml_buffer.tellg();
	seek_end_of_node(xml_buffer, resource_id);
	seek_end_of_line(xml_buffer);
	cut_end = xml_buffer.tellg();
	cut_length = cut_end - cut_start;

	// Cut text
	string cut_string = xml_string.substr(cut_start, cut_length);
	xml_string.replace(cut_start, cut_length, "");  // Cut

	return cut_string;
};

void sbol::seek_property_element(istringstream& xml_buffer, string property_name)
{
//    string SEARCH_TOKEN = getClassName(property_name);
//    cout << SEARCH_TOKEN << endl;
//    seek_next_element(xml_buffer);
//    while (xml_buffer)
//    {
//        int START_OF_ELEMENT = xml_buffer.tellg();
//        // Parse element into qname and tag
//        // This assumes xml elements have a certain form which is not generally true,
//        // so sometimes the parsed qname and resource_id will not make sense
//        vector<string> subtokens = parse_element(xml_buffer);
//        std::string resource_id = subtokens.back();
//        
//        if (resource_id.compare(SEARCH_TOKEN) == 0 && is_open_node(xml_buffer))
//        {
//            xml_buffer.seekg(START_OF_ELEMENT);
//            return;
//        }
//        xml_buffer.get();  // Advance the stream one byte, so we don't get trapped in an infinite loop
//        seek_next_element(xml_buffer);
//    }
};


/* 
Replace a reference node in flat RDF/XML with a nested node. The resource text is modified before inserting
it 
*/
void sbol::replace_reference_to_resource(std::string& xml_string, const std::string property_name, const std::string resource_id, std::string& replacement_text)
{
	int repl_start, repl_end, repl_length, node_start, indentation;
	string qname;
    
	istringstream xml_buffer;
	xml_buffer.str(xml_string);
    seek_property_element(xml_buffer, property_name);
	seek_resource(xml_buffer, property_name, resource_id);
	node_start = xml_buffer.tellg();
    seek_new_line(xml_buffer);
    repl_start = xml_buffer.tellg();
    try
    {
        qname = get_qname(xml_buffer);
    }
    catch(...)
    {
        throw SBOL_ERROR_SERIALIZATION;
    }
    seek_end_of_line(xml_buffer);
    repl_end = xml_buffer.tellg();
    repl_length = repl_end - repl_start;
    
    // Before inserting the new nested SBOL node, a few modifications have to be made first.
    // New open and close elements for the nested node are created.
    // Then the original node text is indented.
    string open_element, close_element;
    indentation = node_start - repl_start;
    open_element = string(indentation, ' ') + "<" + qname + ">\n";
    close_element = string(indentation, ' ') + "</" + qname + ">\n";
    indent(replacement_text, indentation);
    replacement_text.insert(0,open_element);
    replacement_text.append(close_element);
    xml_string.replace(repl_start, repl_length, replacement_text);
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
                rdfxml_string = obj->nest(rdfxml_string);  // Recurse, start nesting with leaf objects
                string id = obj->identity.get();
				string cut_text = cut_sbol_resource(rdfxml_string, id);
                try
                {
                    replace_reference_to_resource(rdfxml_string, property_name, id, cut_text);
                }
                catch(...)
                {
                    throw SBOLError(SBOL_ERROR_SERIALIZATION, "Error serializing " + getClassName(property_name) + " property of " + id);
                }
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
			// Owned objects are kept in the object store as a temporary convenience and will be removed later by the parse_properties handler.
			//doc->add<SBOLObject>(new_obj);
            doc->SBOLObjects[new_obj.identity.get()] = &new_obj;
            new_obj.doc = doc;  //  Set's the objects back-pointer to the parent Document
            
            // If the new object is TopLevel, add to the Document's property store
            TopLevel* check_top_level = dynamic_cast<TopLevel*>(&new_obj);
            if (check_top_level)
                doc->owned_objects[new_obj.type].push_back(&new_obj);  // Adds objects to the Document's property store, eg, componentDefinitions, moduleDefinitions, etc
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
    std::size_t found = property_uri.find_last_of('#');
    if (found == std::string::npos)
    {
        found = property_uri.find_last_of('/');
    }
	if (found != std::string::npos)
	{
		string property_ns = property_uri.substr(0, found);
		string property_name = property_uri.substr(found + 1, subject.length() - 1);
		// If property name is something other than "type" than the triple matches the pattern for defining properties
		if (property_uri.compare(RDF_URI "#type") != 0)
		{
			// Checks if the object to which this property belongs already exists
			if (doc->SBOLObjects.find(id) != doc->SBOLObjects.end())
			{
				SBOLObject *sbol_obj = doc->SBOLObjects[id];
                
				// Decide if this triple corresponds to a simple property, a list property, an owned property or a referenced property
				if (sbol_obj->properties.find(property_uri) != sbol_obj->properties.end())
				{
					// TODO: double-check this, is there a memory-leak here?
                    if (sbol_obj->properties[property_uri][0].compare("<>") == 0 || sbol_obj->properties[property_uri][0].compare("\"\"") == 0 )
                        sbol_obj->properties[property_uri].clear();  //
					sbol_obj->properties[property_uri].push_back(property_value);
				}
				// TODO: the list_properties member should be deprecated, use properties member instead
				else if (sbol_obj->list_properties.find(property_uri) != sbol_obj->list_properties.end())
				{
                    if (sbol_obj->properties[property_uri][0].compare("<>") == 0 || sbol_obj->properties[property_uri][0].compare("\"\"") == 0 )
                        sbol_obj->properties[property_uri].clear();
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
					SBOLObject *owned_obj = doc->SBOLObjects[owned_obj_id];
					sbol_obj->owned_objects[property_uri].push_back(owned_obj);			
					doc->SBOLObjects.erase(owned_obj_id);
                    // doc->owned_objects.erase(owned_object->type);  // Remove temporary, non-toplevel objects from the Document's property store
				}

			}
		}
	}
}

void sbol::raptor_error_handler(void *user_data, raptor_log_message* message)
{
    cout << "Serialization error:" << endl;
    cout << message->text << endl;
    if (message->level == RAPTOR_LOG_LEVEL_NONE) cout << "RAPTOR_LOG_LEVEL_NONE" << endl;
    if (message->level == RAPTOR_LOG_LEVEL_TRACE) cout << "RAPTOR_LOG_LEVEL_TRACE" << endl;
    if (message->level == RAPTOR_LOG_LEVEL_DEBUG) cout << "RAPTOR_LOG_LEVEL_DEBUG" << endl;
    if (message->level == RAPTOR_LOG_LEVEL_INFO) cout << "RAPTOR_LOG_LEVEL_INFO" << endl;
    if (message->level == RAPTOR_LOG_LEVEL_WARN) cout << "RAPTOR_LOG_LEVEL_WARN" << endl;
    if (message->level == RAPTOR_LOG_LEVEL_ERROR) cout << "RAPTOR_LOG_LEVEL_ERROR" << endl;
    if (message->level == RAPTOR_LOG_LEVEL_FATAL) cout << "RAPTOR_LOG_LEVEL_FATAL" << endl;
    if (message->level == RAPTOR_LOG_LEVEL_LAST) cout << "RAPTOR_LOG_LEVEL_LAST" << endl;
    
    if (message->locator != NULL)
        {
        cout << message->locator->line << ", " << message->locator->column << endl;
        if (message->locator->file) cout << message->locator->file;
        if (message->locator->uri) cout << raptor_uri_as_string(message->locator->uri) << endl;
        }
}

void Document::validate(void *arg)
{
    for (ValidationRules::iterator i_rule = this->validationRules.begin(); i_rule != this->validationRules.end(); ++i_rule)
    {
        ValidationRule& validate_fx = *i_rule;
        validate_fx(this, NULL);
    }
}

std::vector<std::string> Document::getNamespaces()
{
    vector<string> ns_list;
    if (this->namespaces.size() != 0)
    {
        for( auto i_ns = this->namespaces.begin(); i_ns != this->namespaces.end(); ++i_ns )
        {
            ns_list.push_back( i_ns->second );
        }
    }
    return ns_list;
};

int Document::find(std::string uri)
{
    for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
    {
        SBOLObject& obj = *i_obj->second;
        if (obj.find(uri) == 1)
            return 1;
    }
    return 0;
};


void Document::namespaceHandler(void *user_data, raptor_namespace *nspace)
{
    //vector<std::string>* namespaces = (vector<string>*)user_data;
    Document* doc = (Document *)user_data;
    string ns = string((const char *)raptor_uri_as_string(raptor_namespace_get_uri(nspace)));
    string prefix = string((const char *)raptor_namespace_get_prefix(nspace));
    doc->namespaces[prefix] = ns;
}

void Document::read(std::string filename)
{
    // Wipe existing contents of this Document first. This should
    raptor_free_world(this->rdf_graph);  //  Probably need to free other objects as well...
    SBOLObjects.clear();
    properties.clear();
    list_properties.clear();
    for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
    {
        // Destroy all TopLevel objects. Child objects should be destroyed recursively.
        SBOLObject& obj = *i_obj->second;
        obj.close();
    }
    owned_objects.clear();
    namespaces.clear();
    
    // Create new RDF graph
    this->rdf_graph = raptor_new_world();
    this->append(filename);
};

void Document::append(std::string filename)
{

    raptor_world_set_log_handler(this->rdf_graph, NULL, raptor_error_handler); // Intercept raptor errors
    
	FILE* fh = fopen(filename.c_str(), "rb");
    if (!fh)
        throw SBOLError(SBOL_ERROR_FILE_NOT_FOUND, "File not found");
	//raptor_parser* rdf_parser = raptor_new_parser(this->rdf_graph, "rdfxml");
    raptor_parser* rdf_parser = raptor_new_parser(this->rdf_graph, getFileFormat().c_str());

    raptor_parser_set_namespace_handler(rdf_parser, this, this->namespaceHandler);
	raptor_iostream* ios = raptor_new_iostream_from_file_handle(this->rdf_graph, fh);
	unsigned char *uri_string;
	raptor_uri *uri, *base_uri;
	
	void *user_data = this;
	raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_objects);
	//base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)(getHomespace() + "#").c_str());  //This can be used to import URIs into a namespace
   	base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)SBOL_URI "#");

    raptor_parser_parse_iostream(rdf_parser, ios, base_uri);

	raptor_free_iostream(ios);
	rewind(fh);
	ios = raptor_new_iostream_from_file_handle(this->rdf_graph, fh);
	raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_properties);
	raptor_parser_parse_iostream(rdf_parser, ios, base_uri);

	raptor_free_uri(base_uri);
	raptor_free_iostream(ios);
	raptor_free_parser(rdf_parser);
    
    this->validate();

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

        // Add missing namespace to the Document
        //doc->addNameSpace(getNameSpace(type), "", sbol_serializer);
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
};

void TopLevel::addToDocument(Document& doc)
{
    doc.SBOLObjects[this->identity.get()] = this;
    this->doc = &doc;
};

TopLevel& Document::getTopLevel(string uri)
{
    // @TODO validate if object is TopLevel or else trigget a libSBOL error
	// @TODO return libSBOL error if URI not found
	return (TopLevel&)*(this->SBOLObjects[uri]);
};

raptor_world* Document::getWorld()
{
	// @TODO validate if object is TopLevel or else trigget a libSBOL error
	// @TODO return libSBOL error if URI not found
	return (this->rdf_graph);
};

void Document::addNamespace(std::string ns, std::string prefix)
{
    this->namespaces[prefix] = ns;
}

void Document::addNamespace(std::string ns, std::string prefix, raptor_serializer* sbol_serializer)
{
    raptor_world *world = getWorld();
    raptor_uri *ns_uri = raptor_new_uri(world, (const unsigned char *)ns.c_str());
    const unsigned char *ns_prefix = (const unsigned char *)prefix.c_str();
    //ns_prefix = (const unsigned char *)"host_context";  // Kludge to be removed
    raptor_serializer_set_namespace(sbol_serializer, ns_uri, ns_prefix);
};

void Document::write(std::string filename)
{
	// Initialize raptor serializer
	FILE* fh = fopen(filename.c_str(), "wb");
	raptor_world* world = getWorld();
    raptor_serializer* sbol_serializer;
    if (getFileFormat().compare("rdfxml") == 0)
        sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
    else
        sbol_serializer = raptor_new_serializer(world, getFileFormat().c_str());

	// Add default namespaces to Document
	//raptor_iostream* ios = raptor_new_iostream_to_file_handle(world, fh);
	raptor_uri *sbol_uri = raptor_new_uri(world, (const unsigned char *)SBOL_URI "#");
	raptor_uri *purl_uri = raptor_new_uri(world, (const unsigned char *)PURL_URI );
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

	//char * sbol_buffer = "";
    char * sbol_buffer;
	size_t sbol_buffer_len;

    raptor_iostream* ios = raptor_new_iostream_to_string(world, (void **)&sbol_buffer, &sbol_buffer_len, NULL);
    raptor_uri *base_uri = NULL;
    
    // Set the default authority for URIs
//    if (hasHomespace())
//    {
//        cout << "Writing in Homespace " << getHomespace() << endl;
//        base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)(getHomespace() + "#").c_str());
//    }

	int err = raptor_serializer_start_to_iostream(sbol_serializer, base_uri, ios);
	if (err) cout << "Error starting iostream" << endl;
	err = raptor_serializer_start_to_string(sbol_serializer, base_uri, (void **)&sbol_buffer, &sbol_buffer_len);
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
    if (getFileFormat().compare("json") == 0)
        fputs(sbol_buffer_string.c_str(), fh);
    else
    {
        if (sbol_buffer)
        {
            // Iterate through objects in document and nest them
            for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
            {
                sbol_buffer_string = obj_i->second->nest(sbol_buffer_string);
            }
            fputs(sbol_buffer_string.c_str(), fh);
        }
        else
        {
            cout << "Serialization failed" << endl;
        }
    }
	raptor_free_iostream(ios);
    raptor_free_uri(base_uri);
	fclose(fh);

};

void Document::close(std::string uri)
{
    if (uri == "")
    {
        for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
        {
            SBOLObject* obj = i_obj->second;
            obj->close();
        }
        delete this;
    }
    else
    {
        if (SBOLObjects.find(uri) == SBOLObjects.end())
            throw SBOLError(NOT_FOUND_ERROR, "Object " + uri + " is not contained in Document and cannot be deleted");
        else
        {
            SBOLObject* obj = SBOLObjects[uri];
            obj->close();
            SBOLObjects.erase(uri);
        }
    }
};

/// Creates another SBOL object derived from TopLevel and adds it to the Document
/// @param uri In "open world" mode, this is a full URI and the same as the returned URI. If the default namespace for libSBOL has been configured, then this argument should simply be a local identifier. If SBOL-compliance is enabled, this argument should be the intended displayId of the new object. A full URI is automatically generated and returned.
/// @return The full URI of the created object.
std::string ReferencedObject::create(std::string uri)
{
    if (sbol_owner->doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "ReferencedObject::create method requires that this object belongs to a Document");
    Document& doc = *sbol_owner->doc;
    Identified& parent_obj = (Identified&)*sbol_owner;
    if (isSBOLCompliant())
    {
    
        Identified& new_obj = (Identified&)SBOL_DATA_MODEL_REGISTER[ reference_type_uri ]();  // Call constructor for the referenced object
        new_obj.identity.set(getHomespace() + "/" + getClassName(reference_type_uri) + "/" + uri + "/" + parent_obj.version.get());
        new_obj.persistentIdentity.set(getHomespace() + "/" + getClassName(reference_type_uri) + "/" + uri);
        new_obj.displayId.set(uri);
        new_obj.version.set(parent_obj.version.get());
        doc.add<SBOLObject>(new_obj);
        set(new_obj.identity.get());
        return new_obj.identity.get();
    }
    else
    {
        std::string new_id;
        if (hasHomespace())
        {
            new_id = getHomespace() + "/" + uri;
        }
        else
            new_id = uri;
        
        Identified& new_obj = (Identified&)SBOL_DATA_MODEL_REGISTER[ reference_type_uri ]();  // Call constructor for the referenced object
        new_obj.identity.set(new_id);
        new_obj.persistentIdentity.set(new_id);
        new_obj.version.set(parent_obj.version.get());
        doc.add<SBOLObject>(new_obj);
        set(new_obj.identity.get());
        return new_obj.identity.get();
    }
};


