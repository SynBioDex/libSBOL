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

#ifdef HAVE_LIBRASQAL
#include "RasqalDataGraph.hh"
#include "RasqalQueryResults.hh"
#endif

#include <json/json.h>
#include <curl/curl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

#include <stdio.h>
#include <ctype.h>
#include <algorithm>

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
#include "Python.h"
#endif


using namespace sbol;
using namespace std;


void Document::dress_document()
{
	// Infer resource namespaces in order to enable retrieval of SBOL-compliant OwnedObjects by displayId
	for (auto & o : SBOLObjects)
	{
		Identified* obj = dynamic_cast<Identified*>(o.second);
		// Check if compliant URI
		if (obj != NULL && obj->persistentIdentity.size() && obj->displayId.size() && obj->version.size())
		{
			string uri = obj->identity.get();
			string sbol_compliant_pattern = "/" + obj->displayId.get() + "/" + obj->version.get();
			string sbol_typed_pattern = "/" + parseClassName(obj->type) + sbol_compliant_pattern;
        	size_t found = uri.find(sbol_typed_pattern);
			if (found != std::string::npos)
			{
				string ns = uri.substr(0, found);
				resource_namespaces.insert(ns);
				continue;
			}
        	found = uri.find(sbol_compliant_pattern);
			if (found != std::string::npos)
			{
				string ns = uri.substr(0, found);
				resource_namespaces.insert(ns);
			}			
		}
	}

    // Look in Implementation store for objects with sys-bio:type and move them to Build store
    vector<string> build_ids;
	for (auto & i : owned_objects[SBOL_IMPLEMENTATION])
		if (i->properties.find(SYSBIO_URI "#type") != i->properties.end() && i->properties[SYSBIO_URI "#type"].front() == "<" SYSBIO_BUILD ">")
			build_ids.push_back(i->identity.get());
    for (auto & id : build_ids)
    {
    	Implementation& i = this->implementations.remove(id);
        Build& b = i. template cast<Build>();
        this->add<Build>(b);
        i.close();
    }

//    // Look in Collection store for objects with sys-bio:type and move them to Test store
//    vector<string> test_ids;
//    for (auto & c : owned_objects[SBOL_COLLECTION])
//        if (c->properties.find(SYSBIO_URI "#type") != c->properties.end() && c->properties[SYSBIO_URI "#type"].front() == "<" SYSBIO_TEST ">")
//            test_ids.push_back(c->identity.get());
//    for (auto & id : test_ids)
//    {
//        Collection& c = this->collections.remove(id);
//        Test& t = c. template cast<Test>();
//        this->add<Test>(t);
//        c.close();
//    }

    // Look in Collection store for objects with sys-bio:type and move them to SampleRoster store
    vector<string> roster_ids;
	for (auto & c : owned_objects[SBOL_COLLECTION])
        if (c->properties.find(SYSBIO_URI "#type") != c->properties.end() && c->properties[SYSBIO_URI "#type"].front() == "<" SYSBIO_URI "#SampleRoster>")
			roster_ids.push_back(c->identity.get());
    for (auto & id : roster_ids)
    {
    	Collection& c = this->collections.remove(id);
        SampleRoster& sr = c. template cast<SampleRoster>();
        this->add<SampleRoster>(sr);
        c.close();
    }

    auto &mySequences = owned_objects[sequences.getTypeURI()];

    std::map<std::string, Sequence*> sequenceCacheMap;
    for(auto &sbolObj : mySequences) {
        sequenceCacheMap[sbolObj->identity.get()] = (Sequence *)sbolObj;
    }

    // Populate hidden properties. This is hardcoded for now, but in the future it should be generalized for all hidden properties.
    for (auto & cd : this->componentDefinitions)
    {
        if (cd.sequence.size() == 0 && cd.sequences.size() == 1)
        {
            auto uri = cd.sequences.get();

            auto findResult = sequenceCacheMap.find(uri);
            if(findResult != sequenceCacheMap.end())
            {
                cd.sequence.set_notoplevelcheck(*findResult->second);
            }
        }
    }

    for (auto & a : this->activities)
    {
    	if (a.associations.size() == 1)
    	{
    		Association& asc = a.associations.get();
    		if (a.agent.size() == 0 && asc.agent.size() && this->agents.find(asc.agent.get()))
    			a.agent.set(this->agents.get(asc.agent.get()));
    		if (a.plan.size() == 0 && asc.plan.size() && this->plans.find(asc.plan.get()))
    			a.plan.set(this->plans.get(asc.plan.get()));
    	}
    }
    for (auto & d : this->designs)
    {
    	if (d.structure.size() == 0 && d._structure.size() && this->componentDefinitions.find(d._structure.get()))
    		d.structure.set(this->componentDefinitions.get(d._structure.get()));
    	if (d.function.size() == 0 && d._function.size() && this->moduleDefinitions.find(d._function.get()))
    		d.function.set(this->moduleDefinitions.get(d._function.get()));
    }
    for (auto & b : this->builds)
    {
    	if (b.structure.size() == 0 && b._structure.size() && this->componentDefinitions.find(b._structure.get()))
    		b.structure.set(this->componentDefinitions.get(b._structure.get()));
    	if (b.behavior.size() == 0 && b._behavior.size() && this->moduleDefinitions.find(b._behavior.get()))
    		b.behavior.set(this->moduleDefinitions.get(b._behavior.get()));
    }
    for (auto & a : this->analyses)
    {
    	if (a.consensusSequence.size() == 0 && a._consensusSequence.size() && this->sequences.find(a._consensusSequence.get()))
    		a.consensusSequence.set(this->sequences.get(a._consensusSequence.get()));
    	if (a.fittedModel.size() == 0 && a._fittedModel.size() && this->models.find(a._fittedModel.get()))
    		a.fittedModel.set(this->models.get(a._fittedModel.get()));
    }

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
    make_pair(SBOL_IDENTIFIED, (SBOLObject&(*)()) &create<Identified>),
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
    make_pair(SBOL_GENERIC_LOCATION, (SBOLObject&(*)()) &create<GenericLocation>),
    make_pair(PROVO_PLAN, (SBOLObject&(*)()) &create<Plan>),
    make_pair(PROVO_ACTIVITY, (SBOLObject&(*)()) &create<Activity>),
    make_pair(PROVO_AGENT, (SBOLObject&(*)()) &create<Agent> ),
    make_pair(PROVO_USAGE, (SBOLObject&(*)()) &create<Usage> ),
    make_pair(PROVO_ASSOCIATION, (SBOLObject&(*)()) &create<Association> ),
    make_pair(SBOL_ATTACHMENT, (SBOLObject&(*)()) &create<Attachment>),
    make_pair(SBOL_COMBINATORIAL_DERIVATION, (SBOLObject&(*)()) &create<CombinatorialDerivation> ),
    make_pair(SBOL_IMPLEMENTATION, (SBOLObject&(*)()) &create<Implementation> ),
    make_pair(SYSBIO_DESIGN, (SBOLObject&(*)()) &create<Design> ),
    make_pair(SYSBIO_ANALYSIS, (SBOLObject&(*)()) &create<Analysis> ),
    make_pair(SYSBIO_SAMPLE_ROSTER, (SBOLObject&(*)()) &create<SampleRoster> ),
    make_pair(SBOL_EXPERIMENT, (SBOLObject&(*)()) &create<Experiment> ),
    make_pair(SBOL_EXPERIMENTAL_DATA, (SBOLObject&(*)()) &create<Test> )

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
	// string original = s;
	string::size_type n = 0;
	string replace_token = "\\\"";
	string replacement = "\"";
	while ( ( n = s.find( replace_token, n ) ) != std::string::npos )
	{
    	s.replace( n, replace_token.size(), replacement );
    	n += replacement.size();
	}
	n = 0;
	replace_token = "\\\\";
	replacement = "\\";
	while ( ( n = s.find( replace_token, n ) ) != std::string::npos )
	{
    	s.replace( n, replace_token.size(), replacement );
    	n += replacement.size();
	}
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

        if (std::find(hidden_properties.begin(), hidden_properties.end(), property_name) != hidden_properties.end())
            continue;

		if (object_store.size() > 0)
		{
			for (auto o = object_store.begin(); o != object_store.end(); ++o)
			{
				SBOLObject* obj = *o;
//                if (Config::getOption("verbose") == "True")
//                    std::cout << rdfxml_string << std::endl;
                rdfxml_string = obj->nest(rdfxml_string);  // Recurse, start nesting with leaf objects
                string id = obj->identity.get();
				string cut_text = cut_sbol_resource(rdfxml_string, id);
//                if (Config::getOption("verbose") == "True")
//                {
//                    std::cout << rdfxml_string << std::endl;
//                    getchar();
//                }
                try
                {
                    replace_reference_to_resource(rdfxml_string, doc->makeQName(property_name), id, cut_text);
                }
                catch(...)
                {
                    throw SBOLError(SBOL_ERROR_SERIALIZATION, "Error serializing " + parseClassName(property_name) + " property of " + this->identity.get());
                }
            }
		}
	}
	return rdfxml_string;
};

void Document::count_triples(void* user_data, raptor_statement* triple)
{
	int& c = *(int *)user_data;
	c = c + 1;
};

std::string Document::string_from_raptor_term(raptor_term *term, bool addWrapper) {
    std::string result;

    switch(term->type) {
    case RAPTOR_TERM_TYPE_URI:
        result = std::string((const char *)raptor_uri_as_string(term->value.uri));

        if(addWrapper)
        {
            result = std::string("<") + result + std::string(">");
        }
        break;

    case RAPTOR_TERM_TYPE_LITERAL:
        result = std::string((const char *)term->value.literal.string);

        if(addWrapper)
        {
            result = std::string("\"") + result + std::string("\"");
        }
        break;

    default:
        break;
    }

    return result;
}

void Document::parse_objects(void* user_data, raptor_statement* triple)
{
    Document *doc = (Document *)user_data;

    string predicate = string_from_raptor_term(triple->predicate);

    // Triples that have a predicate matching the following uri signal
    // to the parser that a new SBOL object should be constructred
    if (predicate.compare("http://www.w3.org/1999/02/22-rdf-syntax-ns#type") == 0)
    {
        string subject = string_from_raptor_term(triple->subject);
        string object = string_from_raptor_term(triple->object);

        doc->parse_objects_inner(subject, object);
    }
}

void Document::parse_objects_inner(const std::string &subject,
                                   const std::string &object)
{
    bool foundSubject = (objectCache.find(subject) != objectCache.end());

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)

    typedef struct {
        PyObject_HEAD
        void *ptr; // This is the pointer to the actual C++ instance
        void *ty;  // swig_type_info originally, but shouldn't matter
        int own;
        PyObject *next;
    } SwigPyObject;

    // Instantiate Python extension objects

    if ( !foundSubject        && (PythonObjects.count(subject) == 0) && (Config::PYTHON_DATA_MODEL_REGISTER.count(object) == 1))
    {
        PyObject* constructor = Config::PYTHON_DATA_MODEL_REGISTER[object];

        PyObject* py_obj = PyObject_CallFunction(constructor, NULL);
        SwigPyObject* swig_py_object = (SwigPyObject*)PyObject_GetAttr(py_obj, PyUnicode_FromString("this"));
        SBOLObject* new_obj = (SBOLObject *)swig_py_object->ptr;

        // Wipe default property values passed from default
        // constructor. New property values will be added as properties
        // are parsed from the input file
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
        SBOLObjects[new_obj->identity.get()] = new_obj;
        new_obj->doc = this;  //  Set's the objects back-pointer to the parent Document

        PythonObjects[subject] = py_obj;
        //Py_DECREF(py_obj); // Clean up
    }
#endif
    // Checks if the object has already been created and whether a
    // constructor for this type of object exists
    if ( !foundSubject && (SBOLObjects.count(subject) == 0) &&
         (SBOL_DATA_MODEL_REGISTER.count(object) == 1))
    {
        SBOLObject& new_obj = SBOL_DATA_MODEL_REGISTER[ object ]();  // Call constructor for the appropriate SBOLObject

        // Wipe default property values passed from default
        // constructor. New property values will be added as properties
        // are parsed from the input file
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

        // All created objects are placed in the document's object
        // store.  However, only toplevel objects will be left
        // permanently.  Owned objects are kept in the object store as a
        // temporary convenience and will be removed later by the
        // parse_properties handler.
        SBOLObjects[new_obj.identity.get()] = &new_obj;
        objectCache[subject] = &new_obj;
        new_obj.doc = doc;     // Set the object's back-pointer to the parent Document
        new_obj.parent = doc;  // For now, set the parent point to the Document.  This may get overwritten later for child objects

        // If the new object is TopLevel, add to the Document's property store
        TopLevel* check_top_level = dynamic_cast<TopLevel*>(&new_obj);
        if (check_top_level)
        {
            // Adds objects to the Document's property store, eg,
            // componentDefinitions, moduleDefinitions, etc
            owned_objects[new_obj.type].push_back(&new_obj);
        }
    }
    // Generic TopLevels
    else if ( !foundSubject && (doc->SBOLObjects.count(subject) == 0) &&
              (SBOL_DATA_MODEL_REGISTER.count(object) == 0))
    {
        SBOLObject& new_obj = *new SBOLObject();  // Call constructor for the appropriate SBOLObject
        new_obj.identity.set(subject);
        new_obj.type = object;
        // All created objects are placed in the document's object
        // store.  However, only toplevel objects will be left
        // permanently.  Owned objects are kept in the object
        // store as a temporary convenience and will be removed
        // later by the parse_properties handler.
        SBOLObjects[new_obj.identity.get()] = &new_obj;
        new_obj.doc = doc;  //  Set's the objects back-pointer to the parent Document
        objectCache[subject] = &new_obj;
    }
}

void Document::parse_properties(void* user_data, raptor_statement* triple)
{
    Document *doc = (Document *)user_data;

    string property_uri = string_from_raptor_term(triple->predicate);

    if (property_uri.compare("http://www.w3.org/1999/02/22-rdf-syntax-ns#type") != 0)
    {
        string subject = string_from_raptor_term(triple->subject);
        string object = string_from_raptor_term(triple->object, true);

        doc->parse_properties_inner(subject, property_uri, object);
    }
};

void Document::parse_properties_inner(const std::string &subject,
                                      const std::string &predicate,
                                      const std::string &object)
{
	string id = subject;
	string property_uri = predicate;
	string property_value = convert_ntriples_encoding_to_ascii(object);

    std::size_t found = property_uri.find_last_of('#');
    if (found == std::string::npos)
    {
        found = property_uri.find_last_of('/');
    }
	if (found != std::string::npos)
	{
		string property_ns = property_uri.substr(0, found);
		string property_name = property_uri.substr(found + 1);

        // Checks if the object to which this property belongs already exists
        if (SBOLObjects.find(id) != SBOLObjects.end())
        {
            SBOLObject *sbol_obj = SBOLObjects[id];

            // Decide if this triple corresponds to a simple property,
            // a list property, an owned property or a referenced
            // property
            if (sbol_obj->properties.find(property_uri) != sbol_obj->properties.end())
            {
                // TODO: double-check this, is there a memory-leak here?`

                if (sbol_obj->properties[property_uri][0].compare("<>") == 0 ||
                    sbol_obj->properties[property_uri][0].compare("\"\"") == 0 )
                    sbol_obj->properties[property_uri].clear();  // Clear an empty property
                sbol_obj->properties[property_uri].push_back(property_value);
            }
            else if (sbol_obj->owned_objects.find(property_uri) != sbol_obj->owned_objects.end())
            {
                // Strip off the angle brackets from the URI value.
                // Note that a Document's object_store and
                // correspondingly, an SBOLObject's property_store
                // uses stripped URIs as keys, while libSBOL uses as a
                // convention angle brackets or quotes for Literal
                // values
                string owned_obj_id = property_value.substr(1, property_value.length() - 2);

                // Form a composite SBOL data structure.  The owned
                // object is added to its parent TopLevel object.  The
                // owned object is then removed from its temporary
                // location in the Document's object store and is now
                // associated only with it's parent TopLevel object.
                auto owned_obj_lookup = SBOLObjects.find(owned_obj_id);
                if(owned_obj_lookup != SBOLObjects.end())
                {
                    SBOLObject *owned_obj = owned_obj_lookup->second;
                    sbol_obj->owned_objects[property_uri].push_back(owned_obj);
                    owned_obj->parent = sbol_obj;
                    SBOLObjects.erase(owned_obj_id);
                }
#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
                if (PythonObjects.find(owned_obj_id) != PythonObjects.end())
                {
                    PyObject *owned_obj = PythonObjects[owned_obj_id];
                    sbol_obj->PythonObjects[owned_obj_id] = owned_obj;
                    PythonObjects.erase(owned_obj_id);
                }
#endif
            }
            // Extension data
            else
            {
                sbol_obj->properties[property_uri].push_back(property_value);
            }
        }
    }
}
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
            TopLevel* tl = new TopLevel(obj->type);
            for (auto &i_p : obj->properties)
                tl->properties[i_p.first] = i_p.second;
            for (auto &i_p : obj->owned_objects)
                tl->owned_objects[i_p.first] = i_p.second;
            tl->doc = this;  //  Set's the objects back-pointer to the parent Document
            SBOLObjects[tl->identity.get()] = tl;
        }
//        // Since this object is not generic TopLevel, it must be a nested annotation. Find the parent object that references it
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

            // Does this reference belong to the appropriate member property?
            matches.erase( std::remove_if (matches.begin(), matches.end(), [property_uri] (SBOLObject* o) {
                    if (o->properties.find(property_uri) == o->properties.end())
                        return true;
                    else
                        return false;
                }), matches.end());

            if (matches.size() > 1)
                throw SBOLError(SBOL_ERROR_SERIALIZATION, "Invalid custom annotation object in SBOL document");
            else if (matches.size() == 1)
            {
                // Nested generic annotations
                SBOLObject* match = matches.front();
                match->owned_objects[property_uri].push_back(obj);
                obj->parent = match;

                // Remove obj from match's property list
                auto identity = obj->identity.get();
                auto &propList = match->properties[property_uri];

                // Loop through properties with type property_uri
                for(auto it=propList.begin(); it != propList.end(); ++it)
                {
                    if(it->compare(1, it->size()-2, identity) == 0)
                    {
                        // Erase reference to obj
                        propList.erase(it);

                        if(propList.size() == 0)
                        {
                            // If there are no more properties of type
                            // property_uri, remove the property
                            // reference vector
                            match->properties.erase(property_uri);
                        }
                        break;
                    }
                }
                SBOLObjects.erase(identity);  // Remove nested object from TopLevel store
            }
        }
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
    throw SBOLError(SBOL_ERROR_SERIALIZATION, "An error occurred while parsing or serializing. The file may not contain valid SBOL");
}

/**
* @author KC
*/
std::string Document::validate()
{
	raptor_world* world = getWorld();
	raptor_serializer* sbol_serializer;
	if (Config::getOption("serialization_format") == "sbol" || Config::getOption("serialization_format") == "rdfxml")
		sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
	else
		sbol_serializer = raptor_new_serializer(world, Config::getOption("serialization_format").c_str());

	char* sbol_buffer;
	size_t sbol_buffer_len;

	raptor_iostream* ios = raptor_new_iostream_to_string(world, (void **)&sbol_buffer, &sbol_buffer_len, NULL);
	raptor_uri *base_uri = NULL;

	generate(&world, &sbol_serializer, &sbol_buffer, &sbol_buffer_len, &ios, &base_uri);

	std::string sbol_buffer_string = std::string((char*)sbol_buffer);

	std::string response = "";
	if (Config::getOption("validate").compare("True") == 0)
		response = request_validation(sbol_buffer_string);
    else
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot validate Document via the online validation tool. To enable validation, use Config::setOption(\"validate\").");

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

void Document::cacheObjects() {
    objectCache.clear();

    for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
    {
        SBOLObject &obj = *i_obj->second;
        obj.cacheObjects(objectCache);
    }
}

void Document::serialize_rdfxml(std::ostream &os) {
    // RDF/XML Header
    os << "<?xml version=\"1.0\" ?>" << std::endl;

    bool firstNS = true;
    os << "<rdf:RDF ";

    // Add default namespace if there is one
    if(default_namespace.size() > 0)
    {
        os << "xmlns=\"" << default_namespace << "\"";
        firstNS = false;
    }

    // Add namespaces
    for(auto nsPair : namespaces) {
        if(firstNS) {
            firstNS = false;
        } else {
            os << " ";
        }

        os << "xmlns:" << nsPair.first << "=\""
           << nsPair.second << "\"";
    }
    os << ">" << std::endl;

    // Add top level SBOL objects
    for(auto objPair : SBOLObjects)
    {
        SBOLObject &obj = *objPair.second;
        bool topLevel = false;
        SBOLObject *parent = obj.parent;
        auto typeURI = obj.getTypeURI();

        // If an object has a parent and is not a hidden property it is
        // not a top-level object
        // if((parent != NULL) &&
        //    (std::find(parent->hidden_properties.begin(),
        //               parent->hidden_properties.end(),
        //               typeURI) == hidden_properties.end()))
        // {
        //     continue;
        // }

        if(dynamic_cast<TopLevel*>(&obj) == NULL)
        {
        	continue;
        }


        std::string identity = obj.identity.get();
        std::string rdfType = referenceNamespace(typeURI);

        os << "  <" << rdfType << " rdf:about=\""
           << identity << "\">" << std::endl;

        // Add object properties
        obj.serialize_rdfxml(os, 2);

        os << "  </" << rdfType << ">" << std::endl;
    }

    os << "</rdf:RDF>" << std::endl;
}


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
    else
    {
        doc->default_namespace = ns;
    }
}

void Document::clear()
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
//    properties.clear();  // This may cause problems later because the Document object will lose all properties of an SBOLObject
//    properties[SBOL_IDENTITY].push_back("<>");  // Re-initialize the identity property. The SBOLObject::compare method needs to get the Document's identity
//    owned_objects.clear();
    for (auto & p : properties)
    {
        if (p.first == SBOL_VERSION)
            continue;
        else if (p.first == SBOL_PERSISTENT_IDENTITY)
            continue;
        else if (p.first == SBOL_DISPLAY_ID)
            continue;
        else if (p.first == SBOL_WAS_DERIVED_FROM)
            continue;
        else if (p.first == PROVO_WAS_GENERATED_BY)
            continue;
        else if (p.first == SBOL_NAME)
            continue;
        else if (p.first == SBOL_DESCRIPTION)
            continue;

        std::string reinitialized_property;
        if (p.second.front()[0] == '<')
            reinitialized_property = "<>";
        else
            reinitialized_property = "\"\"";
        p.second.clear();
        p.second.push_back(reinitialized_property);
    }
    for (auto & o : owned_objects)
    {
        o.second.clear();
    }
    namespaces.clear();

    // Create new RDF graph
    this->rdf_graph = raptor_new_world();
}

void Document::read(std::string filename)
{
	clear();
    this->append(filename);
};

void Document::append(std::string filename)
{
    int t_start;  // For timing
    int t_end;
    if (Config::getOption("verbose") == "True")
		t_start = getTime();

    cacheObjects();

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
	raptor_parser* rdf_parser;
	if (Config::getOption("serialization_format") == "sbol")
    	rdf_parser = raptor_new_parser(this->rdf_graph, "rdfxml");
	else
    	rdf_parser = raptor_new_parser(this->rdf_graph, Config::getOption("serialization_format").c_str());

    raptor_parser_set_namespace_handler(rdf_parser, this, this->namespaceHandler);
	raptor_iostream* ios = raptor_new_iostream_from_file_handle(this->rdf_graph, fh);
	unsigned char *uri_string;
	raptor_uri *uri, *base_uri;
    base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)" ");
    void *user_data = this;

#ifdef HAVE_LIBRASQAL
    RasqalDataGraph graph(filename, base_uri);

    // Find all the SBOL objects
    std::string topQuery =
        "PREFIX : <http://example.org/ns#> "
        "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> "
        "PREFIX sbol: <http://sbols.org/v2#> "
        "SELECT ?s ?o "
        "{ ?s a ?o }";

    RasqalQueryResults topLevelResults = graph.query(topQuery);

    for(auto &amap: topLevelResults.bindingResults()) {
        std::string subject((const char *)rasqal_literal_as_string(amap.at("s")));
        std::string object((const char *)rasqal_literal_as_string(amap.at("o")));

        parse_objects_inner(subject, object);
    }

    // Find everything in the triple store
    std::string allQuery =
        "PREFIX : <http://example.org/ns#> "
        "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> "
        "PREFIX sbol: <http://sbols.org/v2#> "
        "SELECT ?s ?p ?o "
        "{ ?s ?p ?o }";

    RasqalQueryResults allResults = graph.query(allQuery);

    // Find the graph base uri.  This is the location of the sbol
    // file, and begins with the "file://" scheme.  Any URI in the
    // file without a scheme will appear relative to this URI, after
    // the file is parsed.  Therefore, if the any URI property value
    // begins with the graph base uri, the base part of the URI is
    // removed.
    auto graphBaseURI = graph.dataGraph()->uri;
    std::string graphBaseURIStr =
        reinterpret_cast<char*>(raptor_uri_as_string(graphBaseURI));

    // Remove the file name from the path
    std::string::size_type pos = graphBaseURIStr.rfind("/");
    if(pos != std::string::npos)
    {
        ++pos;
    }

    std::string rdf_type = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
    for(auto &amap: allResults.bindingResults()) {
        std::string predicate((const char *)rasqal_literal_as_string(amap.at("p")));

        // Look for properties
        if(predicate != rdf_type)
        {
            std::string subject((const char *)rasqal_literal_as_string(amap.at("s")));
            auto objectLiteral = amap.at("o");
            auto lval = rasqal_literal_as_string(objectLiteral);
            auto ltype = rasqal_literal_get_rdf_term_type(objectLiteral);

            if((ltype == RASQAL_LITERAL_URI) && (pos != std::string::npos))
            {
                if(strncmp((const char *)lval, graphBaseURIStr.c_str(), pos) == 0)
                {
                    // This was a URI without a scheme.  Remove URI base
                    lval += pos;
                }
            }

            // If the literal value is a URI, wrap it in < and >,
            // otherwise wrap it in quotes
            std::string padStart = (ltype == RASQAL_LITERAL_URI) ? "<" : "\"";
            std::string padEnd = (ltype == RASQAL_LITERAL_URI) ? ">" : "\"";
            std::string object = padStart + (const char *)lval + padEnd;

            parse_properties_inner(subject, predicate, object);
        }
    }

    // Use raptor to parse the namespaces.  The callback is set to NULL.
    raptor_parser_set_statement_handler(rdf_parser, user_data, NULL);

#else
    // Read the triple store. On the first pass through the triple store, new SBOLObjects are constructed by the parse_objects handler
	raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_objects);
	//base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)(getHomespace() + "#").c_str());  //This can be used to import URIs into a namespace
    raptor_parser_parse_iostream(rdf_parser, ios, base_uri);
    raptor_free_iostream(ios);
    // Read the triple store again. On the second pass through the triple store, property values are assigned to each SBOLObject's member properties by the parse_properties handler
	rewind(fh);
	ios = raptor_new_iostream_from_file_handle(this->rdf_graph, fh);
	raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_properties);

#endif
	raptor_parser_parse_iostream(rdf_parser, ios, base_uri);
    raptor_free_iostream(ios);

    raptor_free_uri(base_uri);
	raptor_free_parser(rdf_parser);

    // On the final pass, nested annotations not in the SBOL namespace are identified
    parse_annotation_objects();

    // Process libSBOL objects not part of the SBOL core standard
    dress_document();
    fclose(fh);

    if (Config::getOption("verbose") == "True")
    {
		t_end = getTime();
		cout << "Parsing took " << t_end - t_start << " seconds" << endl;
    }
}

void Document::readString(std::string& sbol)
{
    raptor_world_set_log_handler(this->rdf_graph, NULL, raptor_error_handler); // Intercept raptor errors

    raptor_parser* rdf_parser;
    if (Config::getOption("serialization_format") == "sbol")
    	rdf_parser = raptor_new_parser(this->rdf_graph, "rdfxml");
    else
    	rdf_parser = raptor_new_parser(this->rdf_graph, Config::getOption("serialization_format").c_str());

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

    // Process libSBOL objects not part of the SBOL core standard
    dress_document();
}

int Document::countTriples()
{
    raptor_world_set_log_handler(this->rdf_graph, NULL, raptor_error_handler); // Intercept raptor errors

	char *sbol_buffer;
	size_t sbol_buffer_len;
	raptor_serializer* sbol_serializer;
	if (Config::getOption("serialization_format") == "rdfxml" || Config::getOption("serialization_format") == "sbol" )
		sbol_serializer = raptor_new_serializer(rdf_graph, "rdfxml-abbrev");
	else
		sbol_serializer = raptor_new_serializer(rdf_graph, Config::getOption("serialization_format").c_str());
	raptor_iostream* ios = raptor_new_iostream_to_string(this->rdf_graph, (void **)&sbol_buffer, &sbol_buffer_len, NULL);
	raptor_uri *base_uri = NULL;
    generate(&rdf_graph, &sbol_serializer, &sbol_buffer, &sbol_buffer_len, &ios, &base_uri);

    raptor_parser* rdf_parser;
	if (Config::getOption("serialization_format") == "rdfxml" || Config::getOption("serialization_format") == "sbol" )
    	raptor_new_parser(this->rdf_graph, "rdfxml");
	else
    	raptor_new_parser(this->rdf_graph, Config::getOption("serialization_format").c_str());
    raptor_parser_set_namespace_handler(rdf_parser, this, this->namespaceHandler);
    ios = raptor_new_iostream_from_string(this->rdf_graph, (void *)sbol_buffer, sbol_buffer_len);

    base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)SBOL_URI "#");

    int c = 0;
    void *user_data = &c;

    // Read the triple store. On the first pass through the triple store, new SBOLObjects are constructed by the parse_objects handler
    raptor_parser_set_statement_handler(rdf_parser, user_data, this->count_triples);
    //base_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)(getHomespace() + "#").c_str());  //This can be used to import URIs into a namespace

    raptor_parser_parse_iostream(rdf_parser, ios, base_uri);
    raptor_free_iostream(ios);


    raptor_free_uri(base_uri);
    raptor_free_parser(rdf_parser);
 	return c;
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

        for (auto i_ns = namespaces.begin(); i_ns != namespaces.end(); ++i_ns)
        {
            doc->namespaces[i_ns->first] = i_ns->second;
        }
		for (auto it = properties.begin(); it != properties.end(); ++it)
		{
            std::string new_predicate = it->first;  // The triple's predicate identifies an SBOL property
            if (std::find(hidden_properties.begin(), hidden_properties.end(), new_predicate) != hidden_properties.end())
                continue;

			// This RDF triple makes the following statement:
			// "This SBOL object has a property called X and its value is Y"
			raptor_statement *triple2 = raptor_new_statement(sbol_world);

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

            if (std::find(hidden_properties.begin(), hidden_properties.end(), property_name) != hidden_properties.end())
                continue;

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
    this->parent = &doc;
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
	int t_start;  // For timing
	int t_end;
	if (Config::getOption("verbose") == "True")
		t_start = getTime();

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
    
    std::string response = "";
    if (Config::getOption("serialization_format") == "sbol")
    {
        try {
            std::ofstream outFile(filename);
            serialize_rdfxml(outFile);
        } catch(std::exception &e) {
            throw SBOLError(SBOL_ERROR_SERIALIZATION, e.what());
        }
    }
    else
    {
        raptor_world* world = getWorld();
        raptor_serializer* sbol_serializer;
        
        if((Config::getOption("serialization_format") == "rdfxml") ||
           (Config::getOption("serialization_format") == "sbol_raptor"))
        {
            sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
        }
        else
        {
            sbol_serializer = raptor_new_serializer(world, Config::getOption("serialization_format").c_str());
        }
        
        FILE* fh = fopen(filename.c_str(), "wb");
        
        char *sbol_buffer;
        size_t sbol_buffer_len;
        
        raptor_iostream* ios = raptor_new_iostream_to_string(world, (void **)&sbol_buffer, &sbol_buffer_len, NULL);
        raptor_uri *base_uri = NULL;
        
        generate(&world, &sbol_serializer, &sbol_buffer, &sbol_buffer_len, &ios, &base_uri);

        // Convert flat RDF/XML into nested SBOL
        response = "Validation of " + Config::getOption("serialization_format") + " serialization cannot be performed.";
        std::string sbol_buffer_string = std::string((char*)sbol_buffer);
        if (Config::getOption("serialization_format") == "sbol_raptor")
        {
            const int size = (const int)sbol_buffer_len;
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
        else
        {
            fputs(sbol_buffer_string.c_str(), fh);
        }
        if (Config::getOption("verbose") == "True")
        {
            t_end = getTime();
            cout << "Serialization took " << t_end - t_start << " seconds" << endl;
            t_start = t_end;
        }

        raptor_free_iostream(ios);
        raptor_free_uri(base_uri);
        fclose(fh);
    }

	// Validate SBOL using online validator
    if (Config::getOption("validate") == "True" && (Config::getOption("serialization_format") == "sbol" || Config::getOption("serialization_format") == "rdfxml"))
	    response = validate();
	else
	   response = "Validation disabled. To enable use of the online validation tool, use Config::setOption(\"validate\", true)";

	if (Config::getOption("verbose") == "True")
	{
		t_end = getTime();
		cout << "Validation request took " << t_end - t_start << " seconds" << endl;
	}

    return response;
};

std::string Document::writeString()
{
    raptor_world* world = getWorld();
    raptor_serializer* sbol_serializer;
    if (Config::getOption("serialization_format") == "rdfxml" || Config::getOption("serialization_format") == "sbol")
        sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
    else
        sbol_serializer = raptor_new_serializer(world, Config::getOption("serialization_format").c_str());

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
    	if (Config::getOption("serialization_format") == "sbol")
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
	string new_obj_type;
	if (SBOL_DATA_MODEL_REGISTER.find(this->type) != SBOL_DATA_MODEL_REGISTER.end())
		new_obj_type = this->type;
	else
		new_obj_type = SBOL_IDENTIFIED;
    Identified& new_obj = (Identified&)SBOL_DATA_MODEL_REGISTER[ new_obj_type ]();

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
        if (doc)
        {
	        string property_ns = parseNamespace(store_uri);
	        for (auto i_document_ns : this->doc->namespaces)
	        {
	            string prefix = i_document_ns.first;
	            string document_ns = i_document_ns.second;
	            if (!document_ns.compare(property_ns))
	                target_doc->namespaces[prefix] = property_ns;
	        }
	    }

        // If caller specified a namespace argument, then replace namespace in URIs
        // Don't overwrite namespaces for the wasDerivedFrom field, which points back to the original object
        if (ns.compare("") != 0 && store_uri.compare(SBOL_WAS_DERIVED_FROM) != 0)
        {
            string old_ns = ns;
            for (int i_property_val = 0; i_property_val < property_store_copy.size(); ++i_property_val)
            {
                string property_val = property_store_copy[i_property_val];
                if (property_val[0] == '<')
                {
                    string uri = property_val.substr(1, property_val.length() - 2);  // Removes flanking < and > from uri
                    size_t pos = 0;
                    pos = property_val.find(old_ns, pos);
                    if (pos != std::string::npos)
                    {
                        // Copy object reference to new namespace and insert type
                        string replace_target;
                    	string replacement;
                    	string class_name;
                        if (store_uri == SBOL_PERSISTENT_IDENTITY)
                        {
                        	class_name = parseClassName(new_obj.getTypeURI());
                        	replace_target = old_ns + "/" + class_name;
                        	pos = property_val.find(replace_target, 0);
                            if (pos == std::string::npos)
                            {
                        		replace_target = old_ns;
                        		pos = property_val.find(replace_target, 0);
                            }
                        }
                        else
                       	{
                            SBOLObject* referenced_obj = doc->find(uri);  // Distinguish between a referenced object versus an ontology URI
                        	if (referenced_obj)
                        	{
                        		class_name = parseClassName(referenced_obj->getTypeURI());
	                        	replace_target = old_ns + "/" + class_name;
	                        	pos = property_val.find(replace_target, 0);
	                            if (pos == std::string::npos)
	                            {
	                        		replace_target = old_ns;
	                        		pos = property_val.find(replace_target, 0);
	                            }
                        	}
                        }
                        // Construct replacement token
                        if (Config::getOption("sbol_compliant_uris") == "True" && Config::getOption("sbol_typed_uris") == "True")
                        {
                            replacement = getHomespace() + "/" + class_name;
                        }
                        else
                        {
                        	replacement = getHomespace();
                        }
                    	property_val.erase(pos, replace_target.size());
	                    property_val.insert(pos, replacement);
                    	property_store_copy[i_property_val] = property_val;
                    }
                }
            }
        }
        new_obj.properties[store_uri] = property_store_copy;
    }

    // Set version

    if (version != "")
    	new_obj.version.set(version);
    else if (version == "" && ns == "")
    {
        if (this->version.size() > 0)
            if (this->doc != NULL && this->doc == target_doc)  // In order to create a copy of the object in this Document, it's version must be incremented
                new_obj.version.incrementMajor();
            else
            {
                new_obj.version.set(this->version.get());  // Copy this object's version if the user doesn't specify a new one
            }
    }
    else if (version == "" && ns != "")
    {
        if (this->version.size() > 0)
            {
                new_obj.version.set(this->version.get());  // Copy this object's version if the user doesn't specify a new one
            }
    }

    string id;
	if (Config::getOption("sbol_compliant_uris") == "True" && this->version.size() > 0)
    	id = new_obj.persistentIdentity.get() + "/" + new_obj.version.get();
    else
    	id = new_obj.persistentIdentity.get();
    new_obj.identity.set(id);

    // Copy wasDerivedFrom
    if (this->identity.get() != new_obj.identity.get())
	    new_obj.wasDerivedFrom.set(this->identity.get());  // When generating a new object from an old, point back to the copied object
    else if (this->wasDerivedFrom.size() > 0)
    	new_obj.wasDerivedFrom.set(this->wasDerivedFrom.get()); // When cloning an object, don't overwrite the wasDerivedFrom

    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
    {
        string store_uri = i_store->first;
        if (target_doc && std::find(hidden_properties.begin(), hidden_properties.end(), store_uri) != hidden_properties.end() )
        	continue;

        vector < SBOLObject* >& object_store = i_store->second;
        for (auto i_obj = object_store.begin(); i_obj != object_store.end(); ++i_obj)
        {
            Identified& child_obj = (Identified&)**i_obj;

            // Recurse into child objects and copy.  This should be after all other object properties are set, to ensure proper generation of new URIs with updated namespace and version
            Identified& child_obj_copy = child_obj.copy(target_doc, ns, version);
            new_obj.owned_objects[store_uri].push_back((SBOLObject*)&child_obj_copy);  // Copy child object
            child_obj_copy.parent = &new_obj;
            child_obj_copy.update_uri();
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
        if (Config::getOption("sbol_typed_uris").compare("True") == 0)
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
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Cannot validate online. HTTP post request failed with: " + string(curl_easy_strerror(res)));

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

std::string Document::request_comparison(Document& diff_file)
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
    request["options"]["language"] = "SBOL2";
    request["options"]["test_equality"] = true;
    request["options"]["main_file_name"] = "Document1.xml";
    request["options"]["diff_file_name"] = "Document2.xml";

    request["return_file"] = false;
    request["main_file"] = this->writeString();
    request["diff_file"] = diff_file.writeString();

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
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Cannot compare documents with online validator. HTTP get request failed with: " + string(curl_easy_strerror(res)));

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


Document& Document::copy(std::string ns, Document* doc, std::string version)
{
    if (!doc)
        doc = new Document();
    /// @TODO Need to copy Python extension objects
    for (auto & id_and_obj_pair : SBOLObjects)
    {
        TopLevel& tl = *(TopLevel*)id_and_obj_pair.second;
        TopLevel* tl_copy;
        try
        {
	        if (version == "" && tl.version.size() == 1)
	        	tl_copy = &tl.copy<TopLevel>(doc, ns, tl.version.get());
	        else if (version == "" && tl.version.size() == 0)
	        	tl_copy = &tl.copy<TopLevel>(doc, ns);
	        else
	        	tl_copy = &tl.copy<TopLevel>(doc, ns, VERSION_STRING);
	    }
	    catch(SBOLError &e)
	    {
	    	if (e.error_code() == SBOL_ERROR_URI_NOT_UNIQUE)
	    	{
	    		continue;
	    	}
			else
				throw SBOLError(e.error_code(), e.what());
	    }
    }
    doc->dress_document();
    return *doc;
};

void TopLevel::initialize(std::string uri)
{
    if  (Config::getOption("sbol_compliant_uris") == "True")
    {
        displayId.set(uri);
        if (Config::getOption("sbol_typed_uris") == "True")
        {
            identity.set(getHomespace() + "/" + getClassName(this->type) + "/" + displayId.get() + "/" + version.get());
            persistentIdentity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get());
        }
        else
        {
            identity.set(getHomespace() + "/" + displayId.get() + "/" + version.get());
            persistentIdentity.set(getHomespace() + "/" + displayId.get());
        }
    }
    else
    {
        identity.set(uri);
        version.set(VERSION_STRING);
    }
}

void ReferencedObject::set(SBOLObject& obj)
{
    if (obj.type != reference_type_uri)
        throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Cannot set " + this->type + " property. The referenced object is not the correct type.");

    TopLevel* tl = dynamic_cast<TopLevel*>(&obj);
    if (this->sbol_owner->doc)
    {
        if (tl && !this->sbol_owner->doc->find(tl->identity.get()))
        {
            this->sbol_owner->doc->add<TopLevel>(*tl);
        }
    }
    set(obj.identity.get());
};

void ReferencedObject::add(SBOLObject& obj)
{
    if (obj.type != reference_type_uri)
        throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Cannot set " + this->type + " property. The referenced object is not the correct type.");

    TopLevel* tl = dynamic_cast<TopLevel*>(&obj);
    if (this->sbol_owner->doc)
    {
        if (tl && !this->sbol_owner->doc->find(tl->identity.get()))
            this->sbol_owner->doc->add<TopLevel>(*tl);
    }
    add(obj.identity.get());
};

void SBOLObject::update_uri()
{
    if (!this->parent)
        throw;
    TopLevel* check_top_level = dynamic_cast<TopLevel*>(this);
    if (check_top_level)
        return;
    Identified* check_identified = dynamic_cast<Identified*>(this);
    if (!check_identified)
        return;
    Identified& sbol_obj = *(Identified*)this;

    if (!sbol_obj.parent)
        return;
    SBOLObject& parent = *sbol_obj.parent;
    if (Config::getOption("sbol_compliant_uris") == "True" && !dynamic_cast<TopLevel*>(&sbol_obj))
    {
        // Form compliant URI for child object
        std::string obj_id;
        std::string persistent_id;
        std::string version;
        persistent_id = parent.properties[SBOL_PERSISTENT_IDENTITY].front();
        persistent_id = persistent_id.substr(1, persistent_id.length() - 2);  // Removes flanking < and > from the uri
        persistent_id =  persistent_id + "/" + sbol_obj.displayId.get();
        if (parent.properties[SBOL_VERSION].size())
        {
            version = parent.properties[SBOL_VERSION].front();
            version = version.substr(1, version.length() - 2);  // Removes flanking " from the literal
        }
        else
            version = VERSION_STRING;
        obj_id = persistent_id + "/" + version;

        // Reset SBOLCompliant properties
        sbol_obj.identity.set(obj_id);
        sbol_obj.persistentIdentity.set(persistent_id);

        // Check for uniqueness of URI in local object properties
        vector<SBOLObject*> matches = this->parent->find_property_value(SBOL_IDENTITY, obj_id);
        if (matches.size() > 1)
            throw SBOLError(SBOL_ERROR_URI_NOT_UNIQUE, "Cannot update SBOL-compliant URI. The URI " + sbol_obj.identity.get() + " is not unique");


        for (auto & property : sbol_obj.owned_objects)
        {
            std::string property_name = property.first;
            if (std::find(hidden_properties.begin(), hidden_properties.end(), property_name) == hidden_properties.end())
                for (auto & nested_obj : property.second)
                    nested_obj->update_uri();
        }
    }
    // Check for uniqueness of URI in Document
    if (parent.doc)
    {
        vector<SBOLObject*> matches = parent.doc->find_property_value(SBOL_IDENTITY, sbol_obj.identity.get());
        if (matches.size() > 1)
            throw SBOLError(SBOL_ERROR_URI_NOT_UNIQUE, "Cannot update SBOL-compliant URI. An object with URI " + sbol_obj.identity.get() + " is already in the Document");
    }

};
