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
        virtual std::string get();                  ///< Basic getter for all SBOL literal properties.

        URIProperty(sbol_type type_uri = UNDEFINED, void *property_owner = NULL, std::string initial_value = "", ValidationRules validation_rules = {}) :
			Property(type_uri, property_owner, "<" + initial_value + ">", validation_rules)
		{
		}
        
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
                ref = ref.substr(1, ref.size() - 2);  // Removes flanking angle brackets from the field
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
                ref = ref.substr(1, ref.size() - 2);  // Removes flanking angle brackets from the field
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
        virtual std::string get();                  ///< Basic getter for all SBOL literal properties.

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
                ref = ref.substr(1, ref.size() - 2);  // Removes flanking quotations from the field
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
                ref = ref.substr(1, ref.size() - 2);  // Removes flanking quotations from the field
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
        
        int __len__()
        {
            return this->size();
        }
        #endif

        TextProperty(sbol_type type_uri, void *property_owner, std::string initial_value = "", ValidationRules validation_rules = {}) :
			Property(type_uri, property_owner, "\"" + initial_value + "\"", validation_rules)
        
		{
		}
	};

    /// @ingroup extension_layer
    /// IntProperty objects are used to contain integers.  They can be used as member objects inside custom SBOL Extension classes.
	class SBOL_DECLSPEC IntProperty : public Property<int>
	{
	public:
        virtual int get();                  ///< Basic getter for all SBOL literal properties.

        #if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        std::string __getitem__(const int nIndex)
        {
            return this->operator[](nIndex);
        }
        
        IntProperty* __iter__()
        {
            this->python_iter = IntProperty::iterator(this->begin());
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
                if (this->python_iter == this->end())
                {
                    PyErr_SetNone(PyExc_StopIteration);
                }
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

		IntProperty(sbol_type type_uri, void *property_owner, int initial_value = 0) :
			Property(type_uri, property_owner, initial_value)
		{
		}

	};


    
    /// @ingroup extension_layer
    /// @brief Contains a version number for an SBOL object.
    /// The VersionProperty follows Maven versioning semantics and includes a major, minor, and patch version number. Specifically, libSBOL currently only supports using '.' as a delimiter. Ex: v2.0.1.  If the user does not want to follow Maven versioning, they can specify an arbitrary version string using the set() method.
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
        VersionProperty(sbol_type type_uri, void *property_owner, std::string initial_value = "") :
            TextProperty(type_uri, property_owner, initial_value)
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

        /// Set this property with the current time
        std::string stampTime();

        DateTimeProperty(sbol_type type_uri, void *property_owner, std::string initial_value = "", ValidationRules validation_rules = { libsbol_rule_2 }) :
            TextProperty(type_uri, property_owner, initial_value, validation_rules)
        {
        }
    };

    
    
    
    /// A container property that contains child objects. Creates a composition out of two or more classes.  In the SBOL specification, compositional relationships are indicated in class diagrams by arrows with black diamonds. A compositional relationship means that deleting the parent object will delete the child objects, and adding the parent object to a Document will also add the child object.  Owned objects are stored in arbitrary order.
    /// @ingroup extension_layer
    /// @tparam SBOLClass The type of child SBOL object contained by this Property
	template <class SBOLClass>
	class OwnedObject : public Property<SBOLClass>
	{

	public:
        OwnedObject(sbol_type type_uri = UNDEFINED, SBOLObject *property_owner = NULL, std::string dummy = "");  // All sbol:::Properties (and therefore OwnedObjects which are derived from Properties) must match this signature in order to put them inside an sbol:List<> container.  In this case, the third argument is just a dummy variable
		OwnedObject(sbol_type type_uri, void *property_owner, SBOLObject& first_object);

        /// @tparam SBOLClass The type of SBOL object contained in this OwnedObject property
        /// @param sbol_obj A child object to add to this container property.
        /// Assigns a child object to this OwnedObject container property. This method always overwrites the first SBOLObject in the container. appends another object to those already contained in this OwnedObject property. In SBOLCompliant mode, the create method is preferred
        void set(SBOLClass& sbol_obj);
        
        /// @tparam SBOLClass The type of SBOL object contained in this OwnedObject property
        /// @param sbol_obj A child object to add to this container property.
        /// Adds a child object to the parent object. This method always appends another object to those already contained in this OwnedObject property. In SBOLCompliant mode, the create method is preferred
		void add(SBOLClass& sbol_obj);
        
        /// @tparam SBOLClass The type of SBOL object contained in this OwnedObject property
        /// @tparam SBOLSubClass A derived class of SBOLClass. Use this type specialization when adding multiple types of SBOLObjects to a container.
        /// @param sbol_obj A child object to add to this container property.
        /// Adds a child object to the parent object. This method always appends another object to those already contained in this OwnedObject property. In SBOLCompliant mode, the create method is preferred
        template < class SBOLSubClass > void add(SBOLSubClass& sbol_obj);

        /// Get the child object
        /// @tparam SBOLClass The type of the child object
        /// @param uri The URI of the child object
        /// @return A reference to the child object
        /// By default returns the first object in this OwnedObject container property
        SBOLClass& get(const std::string uri = "");
        
        /// Get the child object
        /// @tparam SBOLClass The type of the child object
        /// @tparam SBOLSubClass A derived class of SBOLClass. Use this type specialization when adding multiple types of SBOLObjects to a container.
        /// @param uri The specific URI for a child object if this OwnedObject property contains multiple objects,
        /// @return A reference to the child object
        /// Returns a child object from the OwnedObject property. If no URI is specified, the first object in this OwnedObject property is returned.
        template < class SBOLSubClass > SBOLSubClass& get(std::string uri = "");
        
        /// Get all the objects contained in the property
        /// @return A vector of pointers to the objects
        std::vector<SBOLClass*> getObjects();
        
        /// Remove an object from the list of objects and destroy it.
        /// @param uri The identity of the object to be destroyed. This can be a displayId of the object or a full URI may be provided.
        void remove(std::string uri);
        
        /// Remove an object from the list of objects and destroy it.
        /// @param index A numerical index for the object.
        void remove(int index = 0) override;

        /// Remove all children objects from the parent and destroy them.
        void clear() override;
        
        /// @tparam SBOLClass The type of SBOL object that will be created
        /// @param uri If SBOLCompliance is enabled, this should be the displayId for the new child object.  If not enabled, this should be a full raw URI.
        /// @return A reference to the child object
        /// Autoconstructs a child object and attaches it to the parent object. The new object will be constructed with default values specified in the constructor for this type of object. If SBOLCompliance is enabled, the child object's identity will be constructed using the supplied displayId argument.  Otherwise, the user should supply a full URI.
        /// @TODO check uniqueness of URI in Document
        SBOLClass& create(std::string uri);
        
        /// @tparam SBOLClass The type of SBOL object contained in this OwnedObject property
        /// @tparam SBOLSubClass A derived class of SBOLClass. Use this specialization for OwnedObject properties which contain multiple types of SBOLObjects.
        /// @param uri If SBOLCompliance is enabled, this should be the displayId for the new child object.  If not enabled, this should be a full raw URI.
        /// @return A reference to the child object
        /// Autoconstructs a child object and attaches it to the parent object. The new object will be constructed with default values specified in the constructor for this type of object. If SBOLCompliance is enabled, the child object's identity will be constructed using the supplied displayId argument.  Otherwise, the user should supply a full URI.
        /// @TODO check uniqueness of URI in Document
        template < class SBOLSubClass > SBOLSubClass& create(std::string uri);

		SBOLClass& operator[] (const int nIndex);       ///< Retrieve a child object by numerical index.
        SBOLClass& operator[] (std::string uri);  ///< Retrieve a child object by URI

        /// Provides iterator functionality for SBOL properties that contain multiple objects
        class iterator : public std::vector<SBOLObject*>::iterator
		{
        public:
            
            iterator(typename std::vector<SBOLObject*>::iterator i_object = std::vector<SBOLObject*>::iterator()) : std::vector<SBOLObject*>::iterator(i_object) 
			{
            }

            SBOLClass& operator*()
			{
                return (SBOLClass&) *std::vector<SBOLObject*>::iterator::operator *();
            }
        };
        
        iterator begin() 
		{
            std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
            return iterator(object_store->begin());
        };
        
        iterator end() 
		{
            std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
            return iterator(object_store->end());
        };
        
        int size()
        {
            std::size_t size = this->sbol_owner->owned_objects[this->type].size();
            return (int)size;
        }

        #if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        
        std::vector<SBOLObject*>::iterator python_iter;
        
        SBOLClass& __getitem__(const int nIndex)
        {
            return this->operator[](nIndex);
        }
        
        SBOLClass& __getitem__(const std::string uri)
        {
            return this->operator[](uri);
        }
        
        OwnedObject<SBOLClass>* __iter__()
        {
            this->python_iter = OwnedObject<SBOLClass>::iterator(this->begin());
            return this;
        }
        
        SBOLClass* next()
        {
            if (this->python_iter != this->end())
            {
                SBOLObject* obj = *this->python_iter;
                this->python_iter++;
                if (this->python_iter == this->end())
                {
                    PyErr_SetNone(PyExc_StopIteration);
                }
                return (SBOLClass*)obj;
            }
            throw SBOLError(END_OF_LIST, "");
            return NULL;
        }
        
        SBOLClass* __next__()
        {
            if (this->python_iter != this->end())
            {
                
                SBOLObject* obj = *this->python_iter;
                this->python_iter++;
                
                return (SBOLClass*)obj;
            }
            
            throw SBOLError(END_OF_LIST, "");;
            return NULL;
        }
        
        int __len__()
        {
            return this->size();
        }

        #endif
	};

	template <class SBOLClass >
    OwnedObject< SBOLClass >::OwnedObject(sbol_type type_uri, SBOLObject *property_owner, std::string dummy) :
		Property<SBOLClass>(type_uri, property_owner)
		{
			// Register Property in owner Object
			if (this->sbol_owner != NULL)
			{
				std::vector<sbol::SBOLObject*> object_store;
				this->sbol_owner->owned_objects.insert({ type_uri, object_store });
			}
		};

	template <class SBOLClass>
	OwnedObject< SBOLClass >::OwnedObject(sbol_type type_uri, void *property_owner, SBOLObject& first_object)
	{

    };

    /// @param sbol_obj The child object
    /// Sets the first object in the container
    template < class SBOLClass>
    void OwnedObject<SBOLClass>::set(SBOLClass& sbol_obj)
    {
        /// @TODO This could cause a memory leak if the overwritten object is not freed!
        sbol_obj.parent = this->sbol_owner;
        this->sbol_owner->owned_objects[this->type][0] = ((SBOLObject *)&sbol_obj);
    };

    template <class SBOLClass>
    template <class SBOLSubClass>
    void OwnedObject< SBOLClass >::add(SBOLSubClass& sbol_obj)
    {
        if (!dynamic_cast<SBOLClass*>(&sbol_obj))
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Object of type " + parseClassName(sbol_obj.type) + " is invalid for " + parsePropertyName(this->type) + " property");
        // This should use dynamic_cast instead of implicit casting.  Failure of dynamic_cast should validate if sbol_obj is a valid subclass
        sbol_obj.parent = this->sbol_owner;
        this->sbol_owner->owned_objects[this->type].push_back((SBOLObject *)&sbol_obj);
    };

    
	template <class SBOLClass>
	SBOLClass& OwnedObject<SBOLClass>::operator[] (const int nIndex)
	{
		std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
		return (SBOLClass&)*object_store->at(nIndex);
	};
    
    


    /// Provides interface for an SBOL container Property that is allowed to have more than one object or value
    /// @tparam PropertyType The type of SBOL Property, eg, Text, Int, OwnedObject, etc
    /// @ingroup extension_layer
    template <class PropertyType>
	class List : public PropertyType 
	{

	public:
        List(sbol_type type_uri, SBOLObject *property_owner, std::string initial_value = "");
//        List(sbol_type type_uri, sbol_type reference_type_uri, SBOLObject *property_owner, std::string initial_value = "");

		//std::string get(int index);
		//SBOLClass& get(std::string object_id);
//		void remove(int index);

		//template <class SBOLClass>
		//SBOLClass& get(std::string object_id);

		//std::vector<PropertyType> copy();
	};
    
//    template <class ReferencedObject>
//    List<ReferencedObject>::List(sbol_type type_uri, sbol_type reference_type_uri, SBOLObject *property_owner, std::string initial_value) :
//        ReferencedObject(type_uri, reference_type_uri, property_owner, initial_value)
//    {
//    };

    template <class PropertyType>
    List<PropertyType>::List(sbol_type type_uri, SBOLObject *property_owner, std::string initial_value) :
    PropertyType(type_uri, property_owner, initial_value)
    {
    };
    
    
	//template <class PropertyType>
	//template <class SBOLClass>
	//SBOLClass& List<PropertyType>::get(std::string object_id)
	//{
	//	vector<SBOLObject*> object_store = sbol_owner->owned_objects[type];
	//	cout << object_store.size() << endl;
	//	return (SBOLClass &)object_store.front();

	//};

	//template <class PropertyType>
	//std::string List<PropertyType>::get(int index)
	//{
	//	if (sbol_owner)
	//	{
	//		if (sbol_owner->properties.find(type) == sbol_owner->properties.end())
	//		{
	//			// TODO: trigger exception
	//			// not found
	//			return "";
	//		}
	//		else
	//		{
	//			// found
	//			std::string current_value = sbol_owner->properties[type].at(index);
	//			current_value = current_value.substr(1, current_value.length() - 2);
	//			return current_value;
	//		}
	//	}
	//	else
	//	{
	//		return "";
	//	}
	//};


//	template < class PropertyType >
//	std::vector<PropertyType> List<PropertyType>::copy()
//	{
//		std::vector<PropertyType> vector_copy;
//		for (auto o = this->sbol_owner->owned_objects[this->type].begin(); o != this->sbol_owner->owned_objects[this->type].end(); o++)
//		{
//			vector_copy.push_back(**o);
//		}
//		return vector_copy;
//	};

//	template <class SBOLClass>
//	void OwnedObject<SBOLClass>::remove(int index)
//	{
//		if (this->sbol_owner)
//		{
//            if (this->sbol_owner->properties.find(this->type) != this->sbol_owner->properties.end())
//            {
//                if (index >= this->sbol_owner->properties[this->type].size())
//                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Index out of range");
//                this->sbol_owner->properties[this->type].erase( this->sbol_owner->properties[this->type].begin() + index);
//            }
//            else if (this->sbol_owner->owned_objects.find(this->type) != this->sbol_owner->owned_objects.end())
//            {
//                if (index >= this->sbol_owner->owned_objects[this->type].size())
//                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Index out of range");
//                this->sbol_owner->owned_objects[this->type].erase( this->sbol_owner->owned_objects[this->type].begin() + index);
//            }
//		}
//	};
    
}

#endif