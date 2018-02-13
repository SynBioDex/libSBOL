/**
 * @file    properties.h
 * @brief   Property template classes (eg, TextProperty, URIProperty, IntProperty)
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

#ifndef PROPERTIES_INCLUDED
#define PROPERTIES_INCLUDED

#include "property.h"

#include <raptor2.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <regex>

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
#include "Python.h"
#undef tolower    // This macro is defined in pyport.h and causes a symbol conflict with another macro in regex standard library on OS X

#endif

namespace sbol
{
    class SBOLObject;
    
    /// @ingroup extension_layer
    /// A URIProperty may contain a restricted type of string that conforms to the specification for a Uniform Resource Identifier (URI), typically consisting of a namespace authority followed by an identifier.  A URIProperty often contains a reference to an SBOL object or may contain an ontology term.
    class SBOL_DECLSPEC URIProperty : public Property<std::string>
	{
	public:
        /// Initialize the property with a value that is passed through a constructor for the parent SBOLObject. Validation rules are checked upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        URIProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, std::string initial_value);
        
        /// Initialize a Property without a value. No validation rules are run upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        URIProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules);

        URIProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, char const* initial_value) : URIProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({}), std::string(initial_value)) {};
//
        URIProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound) : URIProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({})) {};
        
        virtual std::string get();                  ///< Get first URI.

        virtual std::vector<std::string> getAll();

        #if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)

        std::string __getitem__(const int nIndex)
        {
            return this->operator[](nIndex);
        }
        
        URIProperty* __iter__()
        {
            this->python_iter = URIProperty::iterator(this->begin());
            return this;
        }
        
        // Built-in iterator function for Python 2
        std::string next()
        {
            if (size() == 0)
                throw SBOLError(END_OF_LIST, "");
            if (this->python_iter != this->end())
            {
                std::string ref = *this->python_iter;
                this->python_iter++;
                if (this->python_iter == this->end())
                {
                    PyErr_SetNone(PyExc_StopIteration);
                }
                return ref;
            }
            throw SBOLError(END_OF_LIST, "");
            return NULL;
        }
        
        // Built-in iterator function for Python 3
        std::string __next__()
        {
            if (size() == 0)
                throw SBOLError(END_OF_LIST, "");
            if (this->python_iter != this->end())
            {
                std::string ref = *this->python_iter;
                this->python_iter++;

                return ref;
            }
            throw SBOLError(END_OF_LIST, "");
            return NULL;
        }
      
        int __len__()
        {
            return this->size();
        }
        #endif

	};

    /// @ingroup extension_layer
    /// TextProperty objects are used to contain string literals.  They can be used as member objects inside custom SBOL Extension classes.
	class SBOL_DECLSPEC TextProperty : public Property<std::string>
	{
	public:
        /// Initialize the TextProperty with a value. Validation rules are checked upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        TextProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, std::string initial_value);
        
        /// Initialize a TextProperty without a value. No validation rules are run upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        TextProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules);

        TextProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, char const* initial_value) : TextProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({}), std::string(initial_value)) {};

        TextProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound) : TextProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({})) {};
        
        virtual std::string get();                  ///< Basic getter for all SBOL literal properties.

        virtual std::vector<std::string> getAll();

        #if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        std::string __getitem__(const int nIndex)
        {
            return this->operator[](nIndex);
        }
        
        TextProperty* __iter__()
        {
            this->python_iter = TextProperty::iterator(this->begin());
            return this;
        }
        
        // Built-in iterator function for Python 2
        std::string next()
        {
            if (size() == 0)
                throw SBOLError(END_OF_LIST, "");
            if (this->python_iter != this->end())
            {
                std::string ref = *this->python_iter;
                this->python_iter++;
                if (this->python_iter == this->end())
                {
                    PyErr_SetNone(PyExc_StopIteration);
                }
                return ref;
            }
            throw SBOLError(END_OF_LIST, "");
            return NULL;
        }
        
        // Built-in iterator function for Python 3
        std::string __next__()
        {
            if (size() == 0)
                throw SBOLError(END_OF_LIST, "");
            if (this->python_iter != this->end())
            {
                std::string ref = *this->python_iter;
                this->python_iter++;
                
                return ref;
            }
            throw SBOLError(END_OF_LIST, "");
            return NULL;
        }
        
        int __len__()
        {
            return this->size();
        }
        #endif

	};

    /// @ingroup extension_layer
    /// IntProperty objects are used to contain integers.  They can be used as member objects inside custom SBOL Extension classes.
	class SBOL_DECLSPEC IntProperty : public Property<int>
	{
	public:
        /// Initialize the IntProperty with a value. Validation rules are checked upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        IntProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, int initial_value) :
            Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules, initial_value)
            {
            }

        /// Initialize an IntProperty without a value. No validation rules are run upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        IntProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules) :
            Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules)
        {
        }
        
        IntProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, int initial_value) : IntProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({}), initial_value) {};

        IntProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound) : IntProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({})) {};
        
        virtual int get();                  ///< Get the integer value

        virtual std::vector<int> getAll();

        #if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        int __getitem__(const int nIndex)
        {
            return stoi(this->operator[](nIndex));
        }
        
        IntProperty* __iter__()
        {
            this->python_iter = IntProperty::iterator(this->begin());
            return this;
        }
        
        // Built-in iterator function for Python 2
        int next()
        {
            if (size() == 0)
                throw SBOLError(END_OF_LIST, "");
            if (this->python_iter != this->end())
            {
                std::string ref = *this->python_iter;
                this->python_iter++;
                if (this->python_iter == this->end())
                {
                    PyErr_SetNone(PyExc_StopIteration);
                }
                return stoi(ref);
            }
            throw SBOLError(END_OF_LIST, "");
        }
        
        // Built-in iterator function for Python 3
        int __next__()
        {
            if (size() == 0)
                throw SBOLError(END_OF_LIST, "");
            if (this->python_iter != this->end())
            {
                std::string ref = *this->python_iter;
                this->python_iter++;
                
                return stoi(ref);
            }
            throw SBOLError(END_OF_LIST, "");
        }
        
        int __len__()
        {
            return this->size();
        }
        #endif
	};

    /// @ingroup extension_layer
    /// FloatProperty objects are used to contain floats.  They can be used as member objects inside custom SBOL Extension classes.
    class SBOL_DECLSPEC FloatProperty : public Property<double>
    {
    public:
        /// Initialize the IntProperty with a value. Validation rules are checked upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        FloatProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, double initial_value) :
            Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules, initial_value)
        {
        };

        /// Initialize a FloatProperty without a value. No validation rules are run upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        FloatProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules) :
            Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules)
        {
        };

        FloatProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, double initial_value) : FloatProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({}), initial_value) {};
        
        FloatProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound) : FloatProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({})) {};
        
        virtual double get();                  ///< Get the float value.

        virtual std::vector<double> getAll();

        
#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        double __getitem__(const int nIndex)
        {
            return stod(this->operator[](nIndex));
        }
        
        FloatProperty* __iter__()
        {
            this->python_iter = FloatProperty::iterator(this->begin());
            return this;
        }
        
        // Built-in iterator function for Python 2
        double next()
        {
            if (size() == 0)
                throw SBOLError(END_OF_LIST, "");
            if (this->python_iter != this->end())
            {
                std::string ref = *this->python_iter;
                this->python_iter++;
                if (this->python_iter == this->end())
                {
                    PyErr_SetNone(PyExc_StopIteration);
                }
                return stod(ref);
            }
            throw SBOLError(END_OF_LIST, "");
        }
        
        // Built-in iterator function for Python 3
        double __next__()
        {
            if (size() == 0)
                throw SBOLError(END_OF_LIST, "");
            if (this->python_iter != this->end())
            {
                std::string ref = *this->python_iter;
                this->python_iter++;
                if (this->python_iter == this->end())
                {
                    PyErr_SetNone(PyExc_StopIteration);
                }
                return stod(ref);
            }
            throw SBOLError(END_OF_LIST, "");
        }
        
        int __len__()
        {
            return this->size();
        }
#endif
    };

    
    /// @ingroup extension_layer
    /// @brief Contains a version number for an SBOL object.
    /// The VersionProperty follows Maven versioning semantics and includes a major, minor, and patch version number.
    class SBOL_DECLSPEC VersionProperty : public TextProperty
    {
    private:
        std::vector<std::string> split(const char c);
    public:
        /// @cond
        std::pair< std::vector<std::string>, std::vector<std::string> > split();
        /// @endcond
        
        void incrementMajor(); ///< Increment major version
        void incrementMinor(); ///< Increment minor version
        void incrementPatch(); ///< Increment patch version
        void decrementMinor(); ///< Decrement major version
        void decrementMajor(); ///< Decrement major version
        void decrementPatch(); ///< Decrement major version
        int major(); ///< Get major version
        int minor(); ///< Get minor version
        int patch(); ///< Get patch version
        
        /// Initialize the VersionProperty with a version string. If a version is specified, it will be checked to confirm it follows Maven versioning semantics.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        VersionProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, std::string initial_value) :
            TextProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({}), initial_value)
            {
                std::string v = this->get();
                // @TODO move this error checking to validation rules to be run on VersionProperty::set() and VersionProperty()::VersionProperty()
                // sbol-10207 The version property of an Identified object is OPTIONAL and MAY contain a String that MUST be composed of only alphanumeric characters, underscores, hyphens, or periods and MUST begin with a digit. 20 Reference: Section 7.4 on page 16 21
                // sbol-10208 The version property of an Identified object SHOULD follow the conventions of semantic 22 versioning as implemented by Maven.
                if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
                {
                    std::regex v_rgx("[0-9]+[a-zA-Z0-9_\\\\.-]*");
                    if (!std::regex_match(v.begin(), v.end(), v_rgx))
                        throw SBOLError(SBOL_ERROR_NONCOMPLIANT_VERSION, "SBOL-compliant versions require a major, minor, and patch number in accordance with Maven versioning schemes. Use toggleSBOLCompliance() to relax these versioning requirements.");
                }
                
            }
    };
    
    
    /// @brief Contains a DateTime string following XML Schema
    class SBOL_DECLSPEC DateTimeProperty : public TextProperty
    {        
    public:
        /// Initialize the DateTime. Conformance to XML DateTime schema is validated upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        DateTimeProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, std::string initial_value) :
            TextProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({ libsbol_rule_2 }), initial_value)
        {
        }

        DateTimeProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound) :
            TextProperty(property_owner, type_uri, lower_bound, upper_bound, ValidationRules({ libsbol_rule_2 }))
        {
        }
        
        
        /// Set this property with the current time
        std::string stampTime();
    };

}

#endif