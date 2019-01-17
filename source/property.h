/**
 * @file    property.h
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

#ifndef PROPERTY_INCLUDED
#define PROPERTY_INCLUDED

#include "constants.h"
#include "config.h"
#include "validation.h"

#include <raptor2.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
#include "Python.h"
#include <utility>
#undef tolower    // This macro is defined in pyport.h and causes a symbol conflict with another macro in regex standard library on OS X

#endif

/// @defgroup extension_layer Extension Interface
/// The extension layer converts the SBOL data model, as described in the [formal specification document](http://sbolstandard.org), into Resource Description Framework (RDF) and a standard RDF/XML file format.  The extension interface also makes it possible to add custom application data to SBOL files, a feature intended to support workflow and collaboration between synthetic biologists at different stages of design, manufacturing, and testing of synthetic DNA constructs.
/// All member properties of SBOL classes are themselves defined using Property classes

namespace sbol
{
    /// @brief This string type is assigned URI strings (see constants.h for default values).  This URI controls the tags of RDF/XML nodes
	typedef std::string rdf_type;

	// All SBOLProperties have a pointer back to the object which the property belongs to.  This requires forward declaration of the SBOLObject class
	class SBOLObject;

    /// Member properties of all SBOL objects are defined using a Property object.  The Property class provides a generic interface for accessing SBOL objects.  At a low level, the Property class converts SBOL data structures into RDF triples.
    /// @tparam The SBOL specification currently supports string, URI, and integer literal values.
    /// @ingroup extension_layer
	template <class LiteralType>
	class SBOL_DECLSPEC Property
	{
    friend class SBOLObject;
        
	protected:
		rdf_type type;
		SBOLObject *sbol_owner;  // back pointer to the SBOLObject to which this Property belongs
        char lowerBound;
        char upperBound;
        ValidationRules validationRules;

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        std::vector<std::pair<PyObject*, PyObject*>> pythonValidationRules;
#endif
	
    public:
        /// @param type_uri An RDF hash URI for this property, consisting of a namespace followed by an identifier. For example, Properties of SBOLObjects use URIs of the form http://sbols.org/v2#somePropertyName, where the identifier somePropertyName determines the appearance of XML nodes in an SBOL file.  Alternatively, annotations in a custom namespace can be provided using a similarly formed hash URI in another namespace.
        /// @param property_owner All Property objects must have a pointer back to its parent SBOLObject of which it is a member
        /// @param initial_value The initial value of the Property
        /// @param validation_rules A vector of externally defined ValidationRules. The vector contains pointers to functions which correspond to the validation rules listed in the appendix of the formal SBOL specification document.  ValidationRules are automatically checked every time a setter or adder method is called and when Documents are read and written.
        Property(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, std::string initial_value);

		Property(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, int initial_value);

        Property(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, double initial_value);

        Property(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules);
        
		~Property();
		virtual rdf_type getTypeURI();
		virtual SBOLObject& getOwner();
//        virtual std::string get();                  ///< Basic getter for all SBOL literal properties.
        virtual void set(std::string new_value);    ///< Basic setter for SBOL TextProperty and URIProperty.
        virtual void set(int new_value);            ///< Basic setter for SBOL IntProperty, but can be used with TextProperty as well.
        virtual void set(size_t new_value) { set((int)new_value); };
        virtual void set(double new_value);            ///< Basic setter for SBOL IntProperty, but can be used with TextProperty as well.
        void add(std::string new_value);            ///< Appends the new value to a list of values, for properties that allow it.
        virtual void remove(int index = 0);         ///< Remove a property value.
        virtual void clear();                       ///< Clear all property values.
		virtual void write();
        virtual bool find(std::string query);       ///< Check if a value in this property matches the query

        char getLowerBound() { return lowerBound; }
        char getUpperBound() { return upperBound; }
        
        void validate(void * arg = NULL);
        std::string operator[] (const int nIndex);  ///< Retrieve the indexed value in a list container

        void copy(Property<LiteralType>& target_property);  ///< Copy property values to a target object's property fields


        /// Provides iterator functionality for SBOL properties that contain multiple values
        class iterator : public std::vector<std::string>::iterator
        {
        public:
            
            iterator(typename std::vector<std::string>::iterator i_str = std::vector<std::string>::iterator()) : std::vector<std::string>::iterator(i_str)
            {
            }
            
            std::string operator*()
            {
                std::string val = std::vector<std::string>::iterator::operator*();
                val = val.substr(1, val.size() - 2);  // Trim bracketing "" or <> off of literal values
                return val;
            }
        };
        
        iterator begin()
        {
            std::vector<std::string> *object_store = &this->sbol_owner->properties[this->type];
            if (!size())
                return iterator(object_store->end());  // If this Property has "" or <> in the object store, consider it empty
            return iterator(object_store->begin());
        };
        
        iterator end()
        {
            std::vector<std::string> *object_store = &this->sbol_owner->properties[this->type];
            return iterator(object_store->end());
        };
        
        int size()
        {
            std::size_t size = this->sbol_owner->properties[this->type].size();
            std::string current_value = this->sbol_owner->properties[this->type][0];
            if (size == 1)
            {
                if (current_value.compare("<>") == 0 || current_value.compare("\"\"") == 0)  // Empty fields retain <> or "" to distinguish between URIs and literals
                    return 0;
            }
            return (int)size;
        };
        
        std::vector<std::string>::iterator python_iter;
        
        void addValidationRule(ValidationRule rule)
        {
            validationRules.push_back(rule);
        };
        
#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        void addValidationRule(PyObject* property_object, PyObject* validation_fx)
        {
            pythonValidationRules.push_back(std::make_pair(validation_fx, property_object));
        };
        
        bool __contains__(std::string value)
        {
            if (this->find(value))
                return true;
            else
                return false;
        }    
#endif

    protected:
        bool isHidden()
        {
            if (std::find(this->sbol_owner->hidden_properties.begin(), this->sbol_owner->hidden_properties.end(), this->type) != this->sbol_owner->hidden_properties.end())
                return true;
            else
                return false;
        }
    };
    
    template <class LiteralType>
    Property<LiteralType>::Property(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules) :
        type(type_uri),
        sbol_owner((SBOLObject *)property_owner),
        lowerBound(lower_bound),
        upperBound(upper_bound),
        validationRules(validation_rules)
    {
        // Register Property in owner Object
        if (this->sbol_owner != NULL)
        {
            std::vector<std::string> property_store;
            property_store.push_back("\"\"");
            this->sbol_owner->properties.insert({ type_uri, property_store });
        }
    }

    template <class LiteralType>
	Property<LiteralType>::Property(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, std::string initial_value) : Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules)
	{
        std::string trim_value = initial_value.substr(1, initial_value.length() - 2);
        validate(&trim_value);
        this->sbol_owner->properties[type_uri][0] = initial_value;
	}

	/* Constructor for int Property */
	template <class LiteralType>
	Property<LiteralType>::Property(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, int initial_value) : Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules)
	{
        validate(&initial_value);
		this->sbol_owner->properties[type_uri][0] = "\"" + std::to_string(initial_value) + "\"";
	}

    /* Constructor for FloatProperty */
    template <class LiteralType>
    Property<LiteralType>::Property(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, double initial_value) : Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules)
    {
        validate(&initial_value);
        this->sbol_owner->properties[type_uri][0] = "\"" + std::to_string(initial_value) + "\"";

    }

    template <class LiteralType>
    Property<LiteralType>::~Property()
    {
    };
    
    
    template <class LiteralType>
    rdf_type Property<LiteralType>::getTypeURI()
    {
        return type;
    }
    
    template <class LiteralType>
    SBOLObject& Property<LiteralType>::getOwner()
    {
        return *sbol_owner;
    }
    

    
    /// @param new_value A new string value for the Property.
    template <class LiteralType>
    void Property<LiteralType>::set(std::string new_value)
    {
        if (sbol_owner)
        {
            //sbol_owner->properties[type].push_back( new_value );
            std::string current_value = this->sbol_owner->properties[this->type][0];
            if (current_value[0] == '<')  //  this property is a uri
            {
                this->sbol_owner->properties[this->type][0] = "<" + new_value + ">";
            }
            else if (current_value[0] == '"') // this property is a literal
            {
                this->sbol_owner->properties[this->type][0] = "\"" + new_value + "\"";
            }
            
        }
        validate((void *)&new_value);
    };

    /// @param new_value A new integer value for the property, which is converted to a raw string during serialization.
    template <class LiteralType>
    void Property<LiteralType>::set(int new_value)
    {
        if (new_value)
        {
            // TODO:  need to convert new_value to string
            this->sbol_owner->properties[type][0] = "\"" + std::to_string(new_value) + "\"";
        }
        validate((void *)&new_value);  //  Call validation rules associated with this Property
    };
    
    /// @param new_value A new integer value for the property, which is converted to a raw string during serialization.
    template <class LiteralType>
    void Property<LiteralType>::set(double new_value)
    {
        if (new_value)
        {
            // TODO:  need to convert new_value to string
            this->sbol_owner->properties[type][0] = "\"" + std::to_string(new_value) + "\"";
        }
        validate((void *)&new_value);  //  Call validation rules associated with this Property
    };
    
    
    /// @param nIndex A numerical index
    template <class LiteralType>
    std::string Property<LiteralType>::operator[] (const int nIndex)
    {
        std::vector<std::string> *value_store = &this->sbol_owner->properties[this->type];
        return value_store->at(nIndex);
    };
    
    template <class LiteralType>
    void Property<LiteralType>::clear()
    {
        std::string current_value = this->sbol_owner->properties[this->type][0];
        this->sbol_owner->properties[type].clear();
        if (current_value[0] == '<')  //  this property is a uri
        {
            this->sbol_owner->properties[this->type].push_back("<>");
        }
        else if (current_value[0] == '"') // this property is a literal
        {
            this->sbol_owner->properties[this->type].push_back("\"\"");
        }
    }
    
    template <class LiteralType>
    bool Property<LiteralType>::find(std::string query)
    {
        std::vector<std::string>& value_store = this->sbol_owner->properties[this->type];
        for (auto & val : value_store)
        {
            if (query == val.substr(1, val.length() - 2))
                return true;
        }
        return false;
    }
    
    template <class LiteralType>
    void Property<LiteralType>::write()
    {
        std::string subject = (*this->sbol_owner).identity.get();
        rdf_type predicate = type;
        std::string object = this->sbol_owner->properties[type].front();
        
        std::cout << "Subject:  " << subject << std::endl;
        std::cout << "Predicate: " << predicate << std::endl;
        std::cout << "Object: "  << object << std::endl;
    };
    
    template <class LiteralType>
    void Property<LiteralType>::validate(void * arg)
    {
        // Validate the argument, if one is specified. The setters do this
        if (arg)
        {
            // Validate the argument, if one is specified. The setters do this
            for (ValidationRules::iterator i_rule = validationRules.begin(); i_rule != validationRules.end(); ++i_rule)
            {
                ValidationRule& validate_fx = *i_rule;
                validate_fx(sbol_owner, arg);
            }
            
#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
            for (auto & rule : pythonValidationRules)
            {
                PyObject* validate_fx = rule.first;
                PyObject* property_to_validate = rule.second;
                PyObject* py_tuple = PyTuple_New(1);
                PyTuple_SetItem(py_tuple, 0, property_to_validate);
                PyObject_CallObject(validate_fx, py_tuple);
                if (PyErr_Occurred() != NULL)
                {
                    PyErr_Clear();
                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Validation failed.");
                }
            }
#endif
        }
//        // If no argument is specified, validate the property values already in the store.  The constructor does this, for example, to validate the initial value.
//        else
//        {
//            std::string val = this->get();
//            for (ValidationRules::iterator i_rule = validationRules.begin(); i_rule != validationRules.end(); ++i_rule)
//            {
//                ValidationRule& validate_fx = *i_rule;
//                validate_fx(sbol_owner, &val);
//            }
//        }
    };
    
    /// @param new_value A new string which will be added to a list of values.
    template <class LiteralType>
    void Property<LiteralType>::add(std::string new_value)
    {
        if (sbol_owner)
        {
            std::string current_value = this->sbol_owner->properties[this->type][0];
            if (current_value[0] == '<')  //  this property is a uri
            {
                if (current_value[1] == '>')
                    this->sbol_owner->properties[this->type][0] = "<" + new_value + ">";
                else
                    this->sbol_owner->properties[this->type].push_back("<" + new_value + ">");
            }
            else if (current_value[0] == '"') // this property is a literal
            {
                if (current_value[1] == '"')
                    this->sbol_owner->properties[this->type][0] = "\"" + new_value + "\"";
                else
                    this->sbol_owner->properties[this->type].push_back("\"" + new_value + "\"");
            }
            validate((void *)&new_value);  //  Call validation rules associated with this Property
        }
    };
    
    template <class LiteralType>
    void Property<LiteralType>::remove(int index)
    {
        if (this->sbol_owner)
        {
            if (this->sbol_owner->properties.find(this->type) != this->sbol_owner->properties.end())
            {
                if (index >= this->sbol_owner->properties[this->type].size())
                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Index out of range");
                if (this->sbol_owner->properties[this->type].size() == 1)
                    this->clear();  // If this is the only value in the property, then clearing it will properly re-initialize the property
                else
                    this->sbol_owner->properties[this->type].erase( this->sbol_owner->properties[this->type].begin() + index);
            }
        }
    };

    template <class LiteralType>
    void Property<LiteralType>::copy(Property<LiteralType>& target_property)
    {
            if (target_property.sbol_owner->properties.find(type) == target_property.sbol_owner->properties.end())
            {
                // not found
                throw std::runtime_error("Cannot copy properties. The target object does not have a property of type " + type);
            }
            std::vector< std::string >* values = &this->sbol_owner->properties[type];
            std::vector< std::string >* targets = &target_property.sbol_owner->properties[type];
            if (size() == 0)
                values->clear();  // Remove "<>" or "" which indicates an empty SBOL property
            values->insert(values->end(), targets->begin(), targets->end());
    };

    
}

#endif
