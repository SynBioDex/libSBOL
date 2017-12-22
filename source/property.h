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
	typedef std::string sbol_type;

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
		sbol_type type;
		SBOLObject *sbol_owner;  // back pointer to the SBOLObject to which this Property belongs
		ValidationRules validationRules;
#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        std::vector<std::pair<PyObject*, PyObject*>> pythonValidationRules;
#endif

        void initializeNamespace(std::string ns);  // Adds extension namespaces to the owner SBOLObject
	public:
        Property(sbol_type type_uri, void *property_owner, std::string initial_value, ValidationRules validation_rules = {});

		Property(sbol_type type_uri, void *property_owner, int initial_value, ValidationRules validation_rules = {});

        Property(sbol_type type_uri, void *property_owner, double initial_value, ValidationRules validation_rules = {});

		Property(sbol_type type_uri = UNDEFINED, void *property_owner = NULL, ValidationRules validation_rules = {}) :
			type(type_uri),
			sbol_owner((SBOLObject *)property_owner),
            validationRules(validation_rules)
		{
		}
		~Property();
		virtual sbol_type getTypeURI();
		virtual SBOLObject& getOwner();
//        virtual std::string get();                  ///< Basic getter for all SBOL literal properties.
        virtual std::vector<std::string> getAll();
        virtual void set(std::string new_value);    ///< Basic setter for SBOL TextProperty and URIProperty.
        virtual void set(int new_value);            ///< Basic setter for SBOL IntProperty, but can be used with TextProperty as well.
        virtual void set(double new_value);            ///< Basic setter for SBOL IntProperty, but can be used with TextProperty as well.
        void add(std::string new_value);            ///< Appends the new value to a list of values, for properties that allow it.
        virtual void remove(int index = 0);         ///< Remove a property value.
        virtual void clear();                       ///< Clear all property values.
		virtual void write();
        virtual bool find(std::string query);       ///< Check if a value in this property matches the query

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
        };
        
        iterator begin()
        {
            std::vector<std::string> *object_store = &this->sbol_owner->properties[this->type];
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
        
#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        void addValidationRule(PyObject* property_object, PyObject* validation_fx)
        {
            pythonValidationRules.push_back(std::make_pair(validation_fx, property_object));
        };
    
#endif
        
    };
    

    /// @param type_uri An RDF hash URI for this property, consisting of a namespace followed by an identifier. For example, Properties of SBOLObjects use URIs of the form http://sbols.org/v2#somePropertyName, where the identifier somePropertyName determines the appearance of XML nodes in an SBOL file.  Alternatively, annotations in a custom namespace can be provided using a similarly formed hash URI in another namespace.
    /// @param property_owner All Property objects must have a pointer back to its parent SBOLObject of which it is a member
    /// @param initial_value The initial value of the Property
    /// @param validation_rules A vector of externally defined ValidationRules. The vector contains pointers to functions which correspond to the validation rules listed in the appendix of the formal SBOL specification document.  ValidationRules are automatically checked every time a setter or adder method is called and when Documents are read and written.
    template <class LiteralType>
	Property<LiteralType>::Property(sbol_type type_uri, void *property_owner, std::string initial_value, ValidationRules validation_rules) : Property(type_uri, property_owner, validation_rules)
	{
        std::string trim_value = initial_value.substr(1, initial_value.length() - 2);
        validate(&trim_value);
		// Register Property in owner Object
		if (this->sbol_owner != NULL)
		{
			std::vector<std::string> property_store;
			property_store.push_back(initial_value);
//			this->sbol_owner->properties.insert({ type_uri, property_store });
            this->sbol_owner->properties.insert({ type, property_store });
        }
	}

	/* Constructor for int Property */
	template <class LiteralType>
	Property<LiteralType>::Property(sbol_type type_uri, void *property_owner, int initial_value, ValidationRules validation_rules) : Property(type_uri, property_owner, validation_rules)
	{
        validate(&initial_value);
		// Register Property in owner Object
		if (this->sbol_owner != NULL)
		{
			std::vector<std::string> property_store;
			property_store.push_back("\"" + std::to_string(initial_value) + "\"");
			this->sbol_owner->properties.insert({ type_uri, property_store });
		}
	}

    /* Constructor for FloatProperty */
    template <class LiteralType>
    Property<LiteralType>::Property(sbol_type type_uri, void *property_owner, double initial_value, ValidationRules validation_rules) : Property(type_uri, property_owner, validation_rules)
    {
        validate(&initial_value);
        // Register Property in owner Object
        if (this->sbol_owner != NULL)
        {
            std::vector<std::string> property_store;
            property_store.push_back("\"" + std::to_string(initial_value) + "\"");
            this->sbol_owner->properties.insert({ type_uri, property_store });
        }
    }
	//typedef std::map<sbol_type, PropertyBase> PropertyStore;

	//extern PropertyStore* global_property_buffer;

    template <class LiteralType>
    Property<LiteralType>::~Property()
    {
    };
    
    
    template <class LiteralType>
    sbol_type Property<LiteralType>::getTypeURI()
    {
        return type;
    }
    
    template <class LiteralType>
    SBOLObject& Property<LiteralType>::getOwner()
    {
        return *sbol_owner;
    }
    
//    /// @ingroup extension_layer
//    /// @return All properties are initially read from an SBOL file as a raw string containing the property value.
//    template <class LiteralType>
//    std::string Property<LiteralType>::get()
//    {
//        if (this->sbol_owner)
//        {
//            if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
//            {
//                // not found
//                throw;
//            }
//            else
//            {
//                // found
//                if (this->sbol_owner->properties[type].size() == 0)
//                    throw SBOLError(NOT_FOUND_ERROR, "Property has not been set");
//                else
//                {
//                    std::string value = this->sbol_owner->properties[type].front();
//                    value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
//                    return value;
//                }
//            }
//        }	else
//        {
//            throw;
//        }
//    };

    template <class LiteralType>
    std::vector<std::string> Property<LiteralType>::getAll()
    {
        if (this->sbol_owner)
        {
            if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
            {
                // not found
                throw std::runtime_error("This property is not defined in the parent object");
            }
            else
            {
                // found
                if (this->sbol_owner->properties[type].size() == 0)
                    return std::vector < std::string >(0);
//                    throw SBOLError(NOT_FOUND_ERROR, "Property has not been set");
                else
                {
                    std::vector<std::string> values;
                    std::vector<std::string>& value_store = this->sbol_owner->properties[type];
                    for (auto i_val = value_store.begin(); i_val != value_store.end(); ++i_val)
                    {
                        std::string value = *i_val;
                        value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                        values.push_back(value);
                    }
                    return values;
                }
            }
        }	else
        {
            throw std::runtime_error("This property is not associated with a parent object");
        }
    };
    
    
//    template <class LiteralType>
//    int Property<LiteralType>::get()
//    {
//        if (this->sbol_owner)
//        {
//            if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
//            {
//                // not found
//                throw;
//            }
//            else
//            {
//                // found
//                std::string value = this->sbol_owner->properties[type].front();
//                value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
//                return std::stoi(value);
//            }
//        }	else
//        {
//            throw;
//        }
//    };
    
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
        sbol_type predicate = type;
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
            values->insert(values->end(), targets->begin(), targets->end());
    };

    
}

#endif
