/**
 * @file    validation.cpp
 * @brief   Validation rules
 * @author  Bryan Bartley
 * @email   bartleyba@sbolstandard.org
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBOL.  Please visit http://sbolstandard.org for more
 * information about SBOL, and the latest version of libSBOL.
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

#include "sbol.h"
#include <iostream>

#include <regex>

using namespace sbol;
using namespace std;

/* An SBOL document MUST declare the use of the following XML namespace: http://sbols.org/v2#. */
void sbol::sbolRule10101(void *sbol_obj, void *arg)
{
    Document* doc = (Document *)sbol_obj;
    vector<string> namespaces = doc->getNamespaces();
    int FOUND_NS = 0;
    for (vector<string>::iterator i_ns = namespaces.begin(); i_ns != namespaces.end(); ++i_ns)
    {
        string ns = *i_ns;
        if(ns.compare(SBOL_URI "#") == 0) FOUND_NS = 1;
    }
    if (!FOUND_NS) SBOLError(SBOL_ERROR_MISSING_NAMESPACE, "Missing namespace " SBOL_URI "#");
}

/* An SBOL document MUST declare the use of the following XML namespace: http://www.w3.org/1999/02/22-rdf-syntax-ns#.*/
void sbol::sbolRule10102(void *sbol_obj, void *arg)
{
    Document* doc = (Document *)sbol_obj;
    vector<string> namespaces = doc->getNamespaces();
    int FOUND_NS = 0;
    for (vector<string>::iterator i_ns = namespaces.begin(); i_ns != namespaces.end(); ++i_ns)
    {
        string ns = *i_ns;
        if(ns.compare(RDF_URI) == 0) FOUND_NS = 1;
    }
    if (!FOUND_NS) SBOLError(SBOL_ERROR_MISSING_NAMESPACE, "Missing namespace " RDF_URI);
}

/* The identity property of an Identified object MUST be globally unique. */
void sbol::sbol_rule_10202(void *sbol_obj, void *arg)
{
	Identified *identified_obj = (Identified *)sbol_obj;
	string new_id;

	if (arg != NULL)
	{
		new_id = *static_cast<std::string*>(arg);
	}
	if (identified_obj->doc)
	{
		if (identified_obj->doc->SBOLObjects.find(new_id) != identified_obj->doc->SBOLObjects.end())  // If the new identity is already in the document throw an error
		{
			throw SBOLError(DUPLICATE_URI_ERROR, "Duplicate URI");
		}
	}
};

/*	The definition property MUST NOT refer to the same ComponentDefinition as the one that contains the
ComponentInstance.Furthermore, ComponentInstance objects MUST NOT form a cyclical chain of references
via their definition properties and the ComponentDefinition objects that contain them.For example, consider
the ComponentInstance objects A and B and the ComponentDefinition objects X and Y.The reference chain "X
contains A, A is defined by Y, Y contains B, and B is defined by X" is cyclical. */


// Print a test message
void sbol::libsbol_rule_1(void *sbol_obj, void *arg)
{
	cout << "Testing internal validation rules" << endl;
};

// Validate XSD date-time format
void sbol::libsbol_rule_2(void *sbol_obj, void *arg)
{
		const char *c_date_time = (const char *)arg;
		string date_time = string(c_date_time);
        if (date_time.compare("") != 0)
        {
            bool DATETIME_MATCH_1 = false;
            bool DATETIME_MATCH_2 = false;
            bool DATETIME_MATCH_3 = false;
            std::regex date_time_1("([0-9]{4})-([0-9]{2})-([0-9]{2})([A-Z])?");
            std::regex date_time_2("([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})([.][0-9]+)?[A-Z]?");
            std::regex date_time_3("([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})([.][0-9]+)?[A-Z]?([\\+|-]([0-9]{2}):([0-9]{2}))?");
            if (std::regex_match(date_time.begin(), date_time.end(), date_time_1))
                DATETIME_MATCH_1 = true;
            if (std::regex_match(date_time.begin(), date_time.end(), date_time_2))
                DATETIME_MATCH_2 = true;
            if (std::regex_match(date_time.begin(), date_time.end(), date_time_3))
                DATETIME_MATCH_3 = true;
            if (!(DATETIME_MATCH_1 || DATETIME_MATCH_2 || DATETIME_MATCH_3))
                throw SBOLError(SBOL_ERROR_NONCOMPLIANT_VERSION, "Invalid datetime format. Datetimes are based on XML Schema dateTime datatype. For example 2016-03-16T20:12:00Z");
        }
};

// Validate Design.structure and Design.function are compatible
void sbol::libsbol_rule_3(void *sbol_obj, void *arg)
{
    ComponentDefinition& structure = (ComponentDefinition&)*arg;
    std::cout << "Validating " << structure.identity.get() << std::endl;

    Design& design = (Design&)(*structure.parent);
    if (design.function.size() > 0)
    {
        std::cout << "Function is defined" << std::endl;
        ModuleDefinition& fx = design.function.get();
        bool STRUCTURE_FUNCTION_CORRELATED = false;
        for (auto & fc : fx.functionalComponents)
        {
            if (fc.definition.get().compare(structure.identity.get()))
                STRUCTURE_FUNCTION_CORRELATED = true;
                break;
        }
        if (!STRUCTURE_FUNCTION_CORRELATED)
            FunctionalComponent& correlation = fx.functionalComponents.create(fx.displayId.get());
    }
    else
        std::cout << "Function is not defined" << std::endl;

};

void sbol::libsbol_rule_4(void *sbol_obj, void *arg)
{
    ModuleDefinition& fx = (ModuleDefinition&)*arg;
    std::cout << "Validating " << fx.identity.get() << std::endl;

    Design& design = (Design&)(*fx.parent);
    if (design.structure.size() > 0)
    {
        std::cout << "Function is defined" << std::endl;
        ComponentDefinition& structure = design.structure.get();
        bool STRUCTURE_FUNCTION_CORRELATED = false;
        for (auto & fc : fx.functionalComponents)
        {
            if (fc.definition.get().compare(structure.identity.get()))
                STRUCTURE_FUNCTION_CORRELATED = true;
            break;
        }
        if (!STRUCTURE_FUNCTION_CORRELATED)
            FunctionalComponent& correlation = fx.functionalComponents.create(fx.displayId.get());
    }
    else
        std::cout << "Structure is not defined" << std::endl;

};
