/**
 * @file    document.cpp
 * @brief   Document class, serialization method, and some low-level accessor methods
 * @author  Bryan Bartley, Kiri Choi
 * @email   bartleyba@sbolstandard.org
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBOL.  Please visit http://sbolstandard.org for more
 * information about SBOL and the latest version of libSBOL.
 *
 *  Copyright 2016 University of Washington, WA, USA
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ------------------------------------------------------------------------->*/


#include "document.h"

#include <raptor2.h>
#include <json/json.h>
#include <curl/curl.h>

#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <regex>
#include <stdio.h>
#include <ctype.h>

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
#include "Python.h"
#endif

using namespace sbol;
using namespace std;


// Remove this, no longer needed
void Document::parse_extension_objects()
{

};

Document::~Document()
{
    for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
    {
        SBOLObject* obj = i_obj->second;
        delete obj;
    }
};

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
    make_pair(SBOL_RANGE, (SBOLObject&(*)()) &create<Range>),
    make_pair(SBOL_MAPS_TO, (SBOLObject&(*)()) &create<MapsTo>),
    make_pair(SBOL_CUT, (SBOLObject&(*)()) &create<Cut>),
    make_pair(SBOL_COLLECTION, (SBOLObject&(*)()) &create<Collection>),
    make_pair(SBOL_GENERIC_LOCATION, (SBOLObject&(*)()) &create<GenericLocation>)
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

void sbol::seek_resource(std::istringstream& xml_buffer, std::string qname, std::string resource_uri)
{
	string SEARCH_TOKEN = NODENAME_RESOURCE "=\"" + resource_uri + "\"";
	seek_next_element(xml_buffer);
	while (xml_buffer)
	{
		int START_OF_ELEMENT = xml_buffer.tellg();
		// Parse element into qname and tag 
		// This assumes xml elements have a certain form which is not generally true,
		// so sometimes the parsed qname and resource_id will not make sense
		vector<string> subtokens = parse_element(xml_buffer);
        string qname_query = subtokens.front();
        string sbol_property_id = SBOL_URI "#" + get_local_part(qname);
		string resource_query = subtokens.back();
        if (qname_query.compare(qname) == 0 && resource_query.compare(SEARCH_TOKEN) == 0 && is_open_node(xml_buffer))
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
//    string SEARCH_TOKEN = parseClassName(property_name);
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

string sbol::convert_ntriples_encoding_to_ascii(string s)
{
    s = regex_replace(s, regex("\\\\\""), "\"");
    s = regex_replace(s, regex("\\\\\\\\"), "\\");
//    s = regex_replace(s, regex("\\\""), "x");
//    s = regex_replace(s, regex("\\\\"), "\\");
    return s;
};

//// Not finished!  A general recursive algorith which returns a flattened vector of all the objects in the document
//vector<SBOLObject *> Document::flatten()
//{
//	vector<SBOLObject *> list_of_sbol_obj;
//	// Iterate through objects in document and serialize them
//	for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
//	{
//		//obj_i->second->serialize(sbol_serializer);
//		list_of_sbol_obj.push_back(obj_i->second);
//		cout << obj_i->second->identity.get() << endl;
//	}
//	return list_of_sbol_obj;
//};

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
//                std::cout << rdfxml_string << std::endl;
                rdfxml_string = obj->nest(rdfxml_string);  // Recurse, start nesting with leaf objects
                string id = obj->identity.get();
				string cut_text = cut_sbol_resource(rdfxml_string, id);
//                std::cout << rdfxml_string << std::endl;
//                getchar();
                try
                {
                    replace_reference_to_resource(rdfxml_string, doc->makeQName(property_name), id, cut_text);
                }
                catch(...)
                {
                    throw SBOLError(SBOL_ERROR_SERIALIZATION, "Error serializing " + parseClassName(property_name) + " property of " + id);
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
#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        
        typedef struct {
            PyObject_HEAD
            void *ptr; // This is the pointer to the actual C++ instance
            void *ty;  // swig_type_info originally, but shouldn't matter
            int own;
            PyObject *next;
        } SwigPyObject;
        
        // Instantiate Python extension objects
        if ((doc->PythonObjects.count(subject) == 0) && (Config::PYTHON_DATA_MODEL_REGISTER.count(object) == 1))
        {
            PyObject* constructor = Config::PYTHON_DATA_MODEL_REGISTER[object];
            PyObject* py_obj = PyObject_CallObject(constructor, NULL);
            SwigPyObject* swig_py_object = (SwigPyObject*)PyObject_GetAttr(py_obj, PyString_FromString("this"));
            SBOLObject* new_obj = (SBOLObject *)swig_py_object->ptr;
            
            // Wipe default property values passed from default constructor. New property values will be added as properties are parsed from the input file
            for (auto it = new_obj->properties.begin(); it != new_obj->properties.end(); it++)
            {
                std::string token = it->second.front();
                if (token[0] == '<')  // clear defaults and re-initialize this property as a URI
                {
                    new_obj->properties[it->first].clear();
                    new_obj->properties[it->first].push_back("<>");
                }
                else if (token[0] == '"')  // clear defaults and re-initialize as a literal
                {
                    new_obj->properties[it->first].clear();
                    new_obj->properties[it->first].push_back("\"\"");
                }
            }
            
            // Set identity
            new_obj->identity.set(subject);

            // All created objects are placed in the document's object store.  However, only toplevel objects will be left permanently.
            // Owned objects are kept in the object store as a temporary convenience and will be removed later by the parse_properties handler.
            doc->SBOLObjects[new_obj->identity.get()] = new_obj;
            new_obj->doc = doc;  //  Set's the objects back-pointer to the parent Document
            
            Py_DECREF(py_obj); // Clean up
        }
        else
#endif
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
        // Generic TopLevels
        else if ((doc->SBOLObjects.count(subject) == 0) && (SBOL_DATA_MODEL_REGISTER.count(object) == 0))
        {
            SBOLObject& new_obj = *new SBOLObject();  // Call constructor for the appropriate SBOLObject
            new_obj.identity.set(subject);
            new_obj.type = object;
            // All created objects are placed in the document's object store.  However, only toplevel objects will be left permanently.
            // Owned objects are kept in the object store as a temporary convenience and will be removed later by the parse_properties handler.
            doc->SBOLObjects[new_obj.identity.get()] = &new_obj;
//            std::cout << "Adding extension object " << new_obj.identity.get() << " : " << doc->SBOLObjects.count(subject) << std::endl;
            new_obj.doc = doc;  //  Set's the objects back-pointer to the parent Document
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
	string property_value = convert_ntriples_encoding_to_ascii(object);
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
		if (property_uri.compare("http://www.w3.org/1999/02/22-rdf-syntax-ns#type") != 0)
		{
			// Checks if the object to which this property belongs already exists
			if (doc->SBOLObjects.find(id) != doc->SBOLObjects.end())
			{
				SBOLObject *sbol_obj = doc->SBOLObjects[id];
                
				// Decide if this triple corresponds to a simple property, a list property, an owned property or a referenced property
				if (sbol_obj->properties.find(property_uri) != sbol_obj->properties.end())
				{
					// TODO: double-check this, is there a memory-leak here?`
                    
                    if (sbol_obj->properties[property_uri][0].compare("<>") == 0 || sbol_obj->properties[property_uri][0].compare("\"\"") == 0 )
                        sbol_obj->properties[property_uri].clear();  // Clear an empty property
					sbol_obj->properties[property_uri].push_back(property_value);
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
                    owned_obj->parent = sbol_obj;
					doc->SBOLObjects.erase(owned_obj_id);
                    // doc->owned_objects.erase(owned_object->type);  // Remove temporary, non-toplevel objects from the Document's property store
				}
                // Extension data
                else
                {
//                    cout << "Setting " << property_uri << " of " << id << " to " << property_value << endl;
                    sbol_obj->properties[property_uri].push_back(property_value);
                }
			}
		}
	}
};

void Document::parse_annotation_objects()
{
    // Check if there are any SBOLObjects remaining in the Document's object store which are not recognized as part of the core data model or an explicitly declared extension class
    vector < SBOLObject* > annotation_objects = {};
    for (auto &i_obj : SBOLObjects)
    {
        SBOLObject* obj = i_obj.second;
        if (!dynamic_cast<TopLevel*>(obj))           // If an object can't be cast to TopLevel then it must be a generic annotation object
            annotation_objects.push_back(obj);
    }
    for (auto &obj : annotation_objects)
    {
        // Check if this annotation object is a generic TopLevel
        if (obj->properties.find(SBOL_PERSISTENT_IDENTITY) != obj->properties.end())
        {
            // Copy to a new TopLevel object
            TopLevel* tl = new TopLevel();
            for (auto &i_p : obj->properties)
                tl->properties[i_p.first] = i_p.second;
            for (auto &i_p : obj->owned_objects)
                tl->owned_objects[i_p.first] = i_p.second;
            tl->doc = this;  //  Set's the objects back-pointer to the parent Document
            SBOLObjects[tl->identity.get()] = tl;
        }
        // Since this object is not generic TopLevel, it must be a nested annotation. Find the parent object that references it
        else
        {
            // Determine the RDF type of the member property that contains this kind of annotation object
            string ns = parseNamespace(obj->type);
            string class_name = parseClassName(obj->type);
            string property_name = class_name;
            property_name[0] = tolower(property_name[0]);
            string property_uri = ns + property_name;
                
            // Find all parent objects containing a reference to the annotation object
            vector<SBOLObject*> matches = find_reference(obj->identity.get());
            for (auto &i_match : matches)
            {
                // Does this reference belong to the appropriate member property?
                if (i_match->properties.find(property_uri) != i_match->properties.end())
                {
                    i_match->owned_objects[property_uri].push_back(obj);
                    obj->parent = i_match;
                    i_match->properties.erase(property_uri);
                }
            }
        }
    }
    // Remove annotation objects from the top level Document store
    for (auto &obj : annotation_objects)
    {
        SBOLObjects.erase(obj->identity.get());
    }
}

void sbol::raptor_error_handler(void *user_data, raptor_log_message* message)
{
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
    throw SBOLError(SBOL_ERROR_SERIALIZATION, "An error occurred while parsing or serializing. The file may not contain valid RDF/XML");
}

/**
* @author KC
*/
std::string Document::validate()
{
	raptor_world* world = getWorld();
	raptor_serializer* sbol_serializer;
	if (getFileFormat().compare("rdfxml") == 0)
		sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
	else
		sbol_serializer = raptor_new_serializer(world, getFileFormat().c_str());

	char* sbol_buffer;
	size_t sbol_buffer_len;

	raptor_iostream* ios = raptor_new_iostream_to_string(world, (void **)&sbol_buffer, &sbol_buffer_len, NULL);
	raptor_uri *base_uri = NULL;

	generate(&world, &sbol_serializer, &sbol_buffer, &sbol_buffer_len, &ios, &base_uri);

	std::string sbol_buffer_string = std::string((char*)sbol_buffer);

	std::string response = "";
	if (Config::getOption("validate").compare("True") == 0)
		response = request_validation(sbol_buffer_string);

	raptor_free_iostream(ios);
	raptor_free_uri(base_uri);

	return response;
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

//int Document::find(std::string uri)
//{
//    for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
//    {
//        SBOLObject& obj = *i_obj->second;
//        if (obj.find(uri) == 1)
//            return 1;
//    }
//    return 0;
//};

SBOLObject* Document::find(std::string uri)
{
    for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
    {
        SBOLObject& obj = *i_obj->second;
        SBOLObject* match = obj.find(uri);
        if (match)
            return match;
    }
    return NULL;
};

SBOLObject* Document::find_property(std::string uri)
{
    for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
    {
        SBOLObject& obj = *i_obj->second;
        SBOLObject* match = obj.find_property(uri) ;
        if (match)
            return match;
    }
    return NULL;
};

vector<SBOLObject*> Document::find_reference(string uri)
{
    vector<SBOLObject*> matches = {};
    for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
    {
        SBOLObject& obj = *i_obj->second;
        // @TODO: Need to append matches vector
        vector<SBOLObject*> submatches = obj.find_reference(uri);
        matches.insert(matches.end(), submatches.begin(), submatches.end());
    }
    return matches;
};

void Document::namespaceHandler(void *user_data, raptor_namespace *nspace)
{
    //vector<std::string>* namespaces = (vector<string>*)user_data;
    Document* doc = (Document *)user_data;
    string ns = string((const char *)raptor_uri_as_string(raptor_namespace_get_uri(nspace)));
    if (raptor_namespace_get_prefix(nspace))
    {
        string prefix = string((const char *)raptor_namespace_get_prefix(nspace));
        doc->namespaces[prefix] = ns;
    }
}

void Document::read(std::string filename)
{
    // Wipe existing contents of this Document first. This should
    raptor_free_world(this->rdf_graph);  //  Probably need to free other objects as well...
    for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
    {
        // Destroy all TopLevel objects. Child objects should be destroyed recursively.
        SBOLObject& obj = *i_obj->second;
        obj.close();
    }
    SBOLObjects.clear();
    properties.clear();  // This may cause problems later because the Document object will lose all properties of an SBOLObject
    properties[SBOL_IDENTITY].push_back("<>");  // Re-initialize the identity property. The SBOLObject::compare method needs to get the Document's identity
    //list_properties.clear();
    owned_objects.clear();
    namespaces.clear();
    
    // Create new RDF graph
    this->rdf_graph = raptor_new_world();
    this->append(filename);
};

void Document::append(std::string filename)
{

    raptor_world_set_log_handler(this->rdf_graph, NULL, raptor_error_handler); // Intercept raptor errors
    
    if (filename != "" && filename[0] == '~') {
        if (filename[1] != '/'){
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Malformed input path. Potentially missing slash.");
        }
        char const* home = getenv("HOME");
        if (home || (home = getenv("USERPROFILE"))) {
            filename.replace(0, 1, home);
        }
    }
    FILE* fh = fopen(filename.c_str(), "rb");
    if (!fh)
        throw SBOLError(SBOL_ERROR_FILE_NOT_FOUND, "File " + filename + " not found");
	//raptor_parser* rdf_parser = raptor_new_parser(this->rdf_graph, "rdfxml");
    raptor_parser* rdf_parser = raptor_new_parser(this->rdf_graph, getFileFormat().c_str());

    raptor_parser_set_namespace_handler(rdf_parser, this, this->namespaceHandler);
	raptor_iostream* ios = raptor_new_iostream_from_file_handle(this->rdf_graph, fh);
	unsigned char *uri_string;
	raptor_uri *uri, *base_uri;
    base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)SBOL_URI "#");
    void *user_data = this;
    
    // Read the triple store. On the first pass through the triple store, new SBOLObjects are constructed by the parse_objects handler
	raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_objects);
	//base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)(getHomespace() + "#").c_str());  //This can be used to import URIs into a namespace
    raptor_parser_parse_iostream(rdf_parser, ios, base_uri);
    raptor_free_iostream(ios);

    // Read the triple store again. On the second pass through the triple store, property values are assigned to each SBOLObject's member properties by the parse_properties handler
	rewind(fh);
	ios = raptor_new_iostream_from_file_handle(this->rdf_graph, fh);
	raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_properties);
	raptor_parser_parse_iostream(rdf_parser, ios, base_uri);
    raptor_free_iostream(ios);
    
    raptor_free_uri(base_uri);
	raptor_free_parser(rdf_parser);

    // On the final pass, nested annotations not in the SBOL namespace are identified
    parse_annotation_objects();

    // A dummy parser which can be extended by SWIG to attach Python extension code
    parse_extension_objects();
//@TODO fix validation on read
//    this->validate();

    fclose(fh);
}

void Document::readString(std::string& sbol)
{
    raptor_world_set_log_handler(this->rdf_graph, NULL, raptor_error_handler); // Intercept raptor errors
    
    raptor_parser* rdf_parser = raptor_new_parser(this->rdf_graph, getFileFormat().c_str());
    
    raptor_parser_set_namespace_handler(rdf_parser, this, this->namespaceHandler);

    raptor_iostream* ios = raptor_new_iostream_from_string(this->rdf_graph, (void *)sbol.c_str(), sbol.size());
    unsigned char *uri_string;
    raptor_uri *uri, *base_uri;
    base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)SBOL_URI "#");
    void *user_data = this;
    
    // Read the triple store. On the first pass through the triple store, new SBOLObjects are constructed by the parse_objects handler
    raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_objects);
    //base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)(getHomespace() + "#").c_str());  //This can be used to import URIs into a namespace

    raptor_parser_parse_iostream(rdf_parser, ios, base_uri);
    raptor_free_iostream(ios);
    
    // Read the triple store again. On the second pass through the triple store, property values are assigned to each SBOLObject's member properties by the parse_properties handler
    ios = raptor_new_iostream_from_string(this->rdf_graph, (void *)sbol.c_str(), sbol.size());
    raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_properties);
    raptor_parser_parse_iostream(rdf_parser, ios, base_uri);
    raptor_free_iostream(ios);
    
    raptor_free_uri(base_uri);
    raptor_free_parser(rdf_parser);
    
    // On the final pass, nested annotations not in the SBOL namespace are identified
    parse_annotation_objects();
    
    // A dummy parser which can be extended by SWIG to attach Python extension code
    parse_extension_objects();
    //@TODO fix validation on read
    //    this->validate();
    
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
		// Serializing this RDF triple makes the following statement:
		// "This instance of an SBOL object belongs to class X"
		raptor_statement *triple = raptor_new_statement(sbol_world);
		std::string subject = identity.get();
		std::string predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
		std::string object = type;

		triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
		triple->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
		triple->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());
		raptor_serializer_serialize_statement(sbol_serializer, triple);
		raptor_free_statement(triple);

        // Add missing namespace to the Document
        for (auto i_ns = namespaces.begin(); i_ns != namespaces.end(); ++i_ns)
            doc->namespaces[i_ns->first] = i_ns->second;
        
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

std::string Document::write(std::string filename)
{
	// Initialize raptor serializer
    if (filename != "" && filename[0] == '~') {
        if (filename[1] != '/'){
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Malformed output path. Potentially missing slash.");
        }
        char const* home = getenv("HOME");
        if (home || (home = getenv("USERPROFILE"))) {
            filename.replace(0, 1, home);
        }
    }

	FILE* fh = fopen(filename.c_str(), "wb");

	raptor_world* world = getWorld();
	raptor_serializer* sbol_serializer;
	if (getFileFormat().compare("rdfxml") == 0)
		sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
	else
		sbol_serializer = raptor_new_serializer(world, getFileFormat().c_str());

	char *sbol_buffer;
	size_t sbol_buffer_len;

	raptor_iostream* ios = raptor_new_iostream_to_string(world, (void **)&sbol_buffer, &sbol_buffer_len, NULL);
	raptor_uri *base_uri = NULL;
    
	generate(&world, &sbol_serializer, &sbol_buffer, &sbol_buffer_len, &ios, &base_uri);

    // Convert flat RDF/XML into nested SBOL
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
            throw SBOLError(SBOL_ERROR_SERIALIZATION, "Serialization failed");
        }
    }

	raptor_free_iostream(ios);
    raptor_free_uri(base_uri);

	// Validate SBOL
	std::string response = validate();

	fclose(fh);

    return response;
};

std::string Document::writeString()
{
    raptor_world* world = getWorld();
    raptor_serializer* sbol_serializer;
    if (getFileFormat().compare("rdfxml") == 0)
        sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
    else
        sbol_serializer = raptor_new_serializer(world, getFileFormat().c_str());
    
    char *sbol_buffer;
    size_t sbol_buffer_len;
    
    raptor_iostream* ios = raptor_new_iostream_to_string(world, (void **)&sbol_buffer, &sbol_buffer_len, NULL);
    raptor_uri *base_uri = NULL;
    
    generate(&world, &sbol_serializer, &sbol_buffer, &sbol_buffer_len, &ios, &base_uri);
    
    // Convert flat RDF/XML into nested SBOL
    std::string sbol_buffer_string = std::string((char*)sbol_buffer);
    const int size = (const int)sbol_buffer_len;

    if (sbol_buffer)
    {
        // Iterate through objects in document and nest them
        for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
        {
            sbol_buffer_string = obj_i->second->nest(sbol_buffer_string);
        }
    }
    else
    {
        throw SBOLError(SBOL_ERROR_SERIALIZATION, "Serialization failed");
    }
    
    raptor_free_iostream(ios);
    raptor_free_uri(base_uri);

    return sbol_buffer_string;
};


/**
* @author KC
* generates rdf/xml
*/
void Document::generate(raptor_world** world, raptor_serializer** sbol_serializer, char** sbol_buffer, size_t* sbol_buffer_len, raptor_iostream** ios, raptor_uri** base_uri)
{

	//char * sbol_buffer = "";

	// Set the default authority for URIs
	//    if (hasHomespace())
	//    {
	//        cout << "Writing in Homespace " << getHomespace() << endl;
	//        base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)(getHomespace() + "#").c_str());
	//    }

	int err = raptor_serializer_start_to_iostream(*sbol_serializer, *base_uri, *ios);
	if (err) cout << "Error starting iostream" << endl;
	err = raptor_serializer_start_to_string(*sbol_serializer, *base_uri, (void **)sbol_buffer, sbol_buffer_len);
	if (err) cout << "Error " << err << "starting string" << endl;

	// Add core SBOL namespaces to Document
	raptor_namespace_stack *sbol_namespaces = raptor_new_namespaces(*world, 0);
	//    raptor_uri *sbol_uri = raptor_new_uri(world, (const unsigned char *)SBOL_URI "#");
	//    raptor_uri *purl_uri = raptor_new_uri(world, (const unsigned char *)PURL_URI );
	//    raptor_uri *prov_uri = raptor_new_uri(world, (const unsigned char *)PROV_URI "#");
	//    
	//    const unsigned char *sbol_prefix = (const unsigned char *)"sbol";
	//    const unsigned char *purl_prefix = (const unsigned char *)"dcterms";
	//    const unsigned char *prov_prefix = (const unsigned char *)"prov";
	//    
	//    raptor_namespace *sbol_namespace = raptor_new_namespace_from_uri(sbol_namespaces, sbol_prefix, sbol_uri, 1);
	//    raptor_namespace *purl_namespace = raptor_new_namespace_from_uri(sbol_namespaces, purl_prefix, purl_uri, 1);
	//    raptor_namespace *prov_namespace = raptor_new_namespace_from_uri(sbol_namespaces, prov_prefix, prov_uri, 1);
	//    
	//    raptor_serializer_set_namespace_from_namespace(sbol_serializer, sbol_namespace);
	//    raptor_serializer_set_namespace_from_namespace(sbol_serializer, purl_namespace);
	//    raptor_serializer_set_namespace_from_namespace(sbol_serializer, prov_namespace);

	// Iterate through objects in document and serialize them
	for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
	{
		obj_i->second->serialize(*sbol_serializer);
	}

	// Add extension namespaces. This must come after the call to serialize in which extension namespaces are propagated up to the Document level.
	for (auto i_ns = this->namespaces.begin(); i_ns != this->namespaces.end(); ++i_ns)
	{
		std::string prefix = i_ns->first;
		std::string ns = i_ns->second;
		raptor_uri *ns_uri = raptor_new_uri(*world, (const unsigned char *)ns.c_str());
		raptor_namespace *extension_namespace = raptor_new_namespace_from_uri(sbol_namespaces, (const unsigned char *)prefix.c_str(), ns_uri, 1);
		raptor_serializer_set_namespace_from_namespace(*sbol_serializer, extension_namespace);
	}

	// Finalize RDF/XML serialization
	raptor_serializer_serialize_end(*sbol_serializer);
	raptor_free_serializer(*sbol_serializer);

	return;
}

void Document::close(std::string uri)
{
    if (uri == "")
    {
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
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, parseClassName(this->sbol_owner->type) + "::" + parseClassName(this->type) + "::create method of " + this->sbol_owner->identity.get() + " requires that this object belongs to a Document");
    Document& doc = *sbol_owner->doc;
    Identified& parent_obj = (Identified&)*sbol_owner;
    if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
    {
    
        Identified& new_obj = (Identified&)SBOL_DATA_MODEL_REGISTER[ reference_type_uri ]();  // Call constructor for the referenced object
        new_obj.identity.set(getHomespace() + "/" + parseClassName(reference_type_uri) + "/" + uri + "/" + parent_obj.version.get());
        new_obj.persistentIdentity.set(getHomespace() + "/" + parseClassName(reference_type_uri) + "/" + uri);
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

Identified& Identified::copy(Document* target_doc, string ns, string version)
{
    // Call constructor for the copy
    Identified& new_obj = (Identified&)SBOL_DATA_MODEL_REGISTER[ this->type ]();
    
    // Assign the new object to the target Document (null for non-TopLevel objects)
    if (target_doc)
        new_obj.doc = target_doc;

    new_obj.type = this->type;
    
    // Copy properties
    for (auto i_store = properties.begin(); i_store != properties.end(); ++i_store)
    {
        string store_uri = i_store->first;
        vector < string > property_store = i_store->second;
        vector < string > property_store_copy = property_store;   // Copy properties
        
        // Add the property namespace to the target document if not present
        string property_ns = parseNamespace(store_uri);
        for (auto i_document_ns : this->doc->namespaces)
        {
            string prefix = i_document_ns.first;
            string document_ns = i_document_ns.second;
            if (!document_ns.compare(property_ns))
                target_doc->namespaces[prefix] = property_ns;
        }
        
        // If caller specified a namespace argument, then replace namespace in URIs
        // Don't overwrite namespaces for the wasDerivedFrom field, which points back to the original object
        if (ns.compare("") != 0 && store_uri.compare(SBOL_WAS_DERIVED_FROM) != 0)
        {
            string old_ns = getHomespace();
            for (int i_property_val = 0; i_property_val < property_store_copy.size(); ++i_property_val)
            {
                string property_val = property_store_copy[i_property_val];
                size_t pos = 0;
                pos = property_val.find(old_ns, pos);
                if (pos != std::string::npos)
                {
                    property_val.erase(pos, old_ns.size());
                    property_val.insert(pos, ns);
                }
                property_store_copy[i_property_val] = property_val;
            }
        }
        new_obj.properties[store_uri] = property_store_copy;
    }
    
    // Set version
    new_obj.wasDerivedFrom.set(this->identity.get());
    if (version.compare("") == 0)
        new_obj.version.incrementMajor();
    else
        new_obj.version.set(version);
    
    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
    {
        string store_uri = i_store->first;
        vector < SBOLObject* >& object_store = i_store->second;
        for (auto i_obj = object_store.begin(); i_obj != object_store.end(); ++i_obj)
        {
            Identified& child_obj = (Identified&)**i_obj;
            
            // Recurse into child objects and copy.  This should be after all other object properties are set, to ensure proper generation of new URIs with updated namespace and version
            Identified& child_obj_copy = child_obj.copy(target_doc, ns, version);
            new_obj.owned_objects[store_uri].push_back((SBOLObject*)&child_obj_copy);  // Copy child object
        }
    }
    return new_obj;
};

Identified& Identified::simpleCopy(string uri)
{
    // Call constructor for the copy
    Identified& new_obj = (Identified&)SBOL_DATA_MODEL_REGISTER[ this->type ]();
 
    // Copy properties
    for (auto i_store = properties.begin(); i_store != properties.end(); ++i_store)
    {
        string store_uri = i_store->first;
        vector < string > property_store = i_store->second;
        vector < string > property_store_copy = property_store;
        for (int i_property_val = 0; i_property_val < property_store_copy.size(); ++i_property_val)
        {
            string property_val = property_store_copy[i_property_val];
            property_store_copy[i_property_val] = property_val;
        }
        new_obj.properties[store_uri] = property_store_copy;
    }
    
    // Initialize the object's URI, this code is same as Identified's constructor
    if(Config::getOption("sbol_compliant_uris").compare("True") == 0)
    {
        if (compliantTypesEnabled())
        {
            new_obj.identity.set(getHomespace() + "/" + getClassName(type) + "/" + uri + "/" + VERSION_STRING);
            new_obj.persistentIdentity.set(getHomespace() + "/" + uri);
        }
        else
        {
            new_obj.identity.set(getHomespace() + "/" + uri + "/" + VERSION_STRING);
            new_obj.persistentIdentity.set(getHomespace() + "/" + uri);
        }
    }
    else if (hasHomespace())
    {
        new_obj.identity.set(getHomespace() + "/" + uri);
        new_obj.persistentIdentity.set(getHomespace() + "/" + uri);
    }

    new_obj.type = this->type;
    
    // Record provenance of object
    new_obj.wasDerivedFrom.set(this->identity.get());
    
    return new_obj;
};








std::string Document::request_validation(std::string& sbol)
{
    /* Form validation options in JSON */
    Json::Value request;   // 'root' will contain the root value after parsing.

    vector<string> opts = {"language", "test_equality", "check_uri_compliance", "check_completeness", "check_best_practices", "fail_on_first_error", "provide_detailed_stack_trace", "subset_uri", "uri_prefix", "version", "insert_type", "main_file_name", "diff_file_name" };
    for (auto const& opt : opts)
    {
        if (Config::getOption(opt).compare("True") == 0)
            request["options"][opt] = true;
        else if (Config::getOption(opt).compare("False") == 0)
            request["options"][opt] = false;
        else
            request["options"][opt] = Config::getOption(opt);
    }
    if (Config::getOption("return_file").compare("True") == 0)
        request["return_file"] = true;
    else if (Config::getOption("return_file").compare("False") == 0)
        request["return_file"] = false;
    request["main_file"] = sbol;
    Json::StyledWriter writer;
    string json = writer.write( request );
    
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();

    Json::Value json_response;
    Json::Reader reader;
    bool parsed = reader.parse( response, json_response );     //parse process
    if ( parsed )
    {
        //response = json_response.get("result", response ).asString();
        //response = json_response.get("valid", response ).asString() << endl;
        //response = json_response.get("output_file", response ).asString() << endl;
        //response = json_response.get("valid", response ).asString();
        if (json_response.get("valid", response ).asString().compare("true") == 0)
            response = "Valid.";
        else
            response = "Invalid.";
        for (auto itr : json_response["errors"])
        {
            response += " " + itr.asString();
        }
    }
    return response;
};



std::string Document::query_repository(std::string command)
{
//    /* Form validation options in JSON */
//    Json::Value request;   // 'root' will contain the root value after parsing.
//    
//    vector<string> opts = {"language", "test_equality", "check_uri_compliance", "check_completeness", "check_best_practices", "fail_on_first_error", "provide_detailed_stack_trace", "subset_uri", "uri_prefix", "version", "insert_type", "main_file_name", "diff_file_name" };
//    for (auto const& opt : opts)
//    {
//        if (Config::getOption(opt).compare("True") == 0)
//            request["options"][opt] = true;
//        else if (Config::getOption(opt).compare("False") == 0)
//            request["options"][opt] = false;
//        else
//            request["options"][opt] = Config::getOption(opt);
//    }
//    if (Config::getOption("return_file").compare("True") == 0)
//        request["return_file"] = true;
//    else if (Config::getOption("return_file").compare("False") == 0)
//        request["return_file"] = false;
//    request["main_file"] = sbol;
//    Json::StyledWriter writer;
//    string json = writer.write( request );
    
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
//    headers = curl_slist_append(headers, "Accept: application/json");
//    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
//    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, "http://synbiohub.utah.edu/public/igem/BBa_F2620/1/sbol");
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the POST data */
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();

    cout << response << endl;
//    Json::Value json_response;
//    Json::Reader reader;
//    bool parsed = reader.parse( response, json_response );     //parse process
//    if ( parsed )
//    {
//        //response = json_response.get("result", response ).asString();
//        //response = json_response.get("valid", response ).asString() << endl;
//        //response = json_response.get("output_file", response ).asString() << endl;
//        //response = json_response.get("valid", response ).asString();
//        if (json_response.get("valid", response ).asString().compare("true") == 0)
//            response = "Valid.";
//        else
//            response = "Invalid.";
//        for (auto itr : json_response["errors"])
//        {
//            response += " " + itr.asString();
//        }
//    }
    return response;
};

std::string Document::search_metadata(std::string role, std::string type, std::string name, std::string collection)
{
    /* Form validation options in JSON */
    Json::Value request;   // 'root' will contain the root value after parsing.
    Json::Value criteria = Json::Value(Json::arrayValue);
    
    request["offset"] = 0;
    request["limit"] = 25;
    request["criteria"] = criteria;
    
    map<string, string> Q = { {"role", role}, {"type", type}, {"name", name}, {"collection", collection} };
    vector<string> option_keys = { "role", "type", "name", "collection" };
    for (auto const& key : option_keys)
    {
        Json::Value query = Json::Value(Json::objectValue);
        string val = Q[key];
        if (val.compare("") != 0)
        {
            query["key"] = key;
            query["value"] = val;
            criteria.append(query);
        }
    }
    request["criteria"] = criteria;
    
    Json::StyledWriter writer;
    string json = writer.write( request );
//    cout << json << endl;
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    //    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl)
    {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, "http://synbiohub.org/component/search/metadata");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    cout << response << endl;
    Json::Value json_response;
    Json::Reader reader;
    bool parsed = reader.parse( response, json_response );     //parse process
    vector<map<string,string>> responses = {};
    if ( parsed )
    {
        for (auto i_r = 0; i_r < json_response.size(); ++i_r)
        {
//            response = json_response[i_r].get("uri", response ).asString();
//            response = json_response[i_r].get("name", response ).asString() << endl;
//            response = json_response[i_r].get("description", response ).asString() << endl;
//            response = json_response[i_r].get("displayId", response ).asString();
//            response = json_response[i_r].get("version", response ).asString();
        }
    }
    return response;
};



