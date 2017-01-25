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
	};

    /// @ingroup extension_layer
    /// TextProperty objects are used to contain string literals.  They can be used as member objects inside custom SBOL Extension classes.
	class SBOL_DECLSPEC TextProperty : public Property<std::string>
	{
	public:
        virtual std::string get();                  ///< Basic getter for all SBOL literal properties.

		TextProperty(sbol_type type_uri, void *property_owner, std::string initial_value = "") :
			Property(type_uri, property_owner, "\"" + initial_value + "\"")
		{
		}
	};

    /// @ingroup extension_layer
    /// IntProperty objects are used to contain integers.  They can be used as member objects inside custom SBOL Extension classes.
	class SBOL_DECLSPEC IntProperty : public Property<int>
	{
	public:
        virtual int get();                  ///< Basic getter for all SBOL literal properties.

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
        std::pair< std::vector<std::string>, std::vector<std::string> > split();
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
                if (isSBOLCompliant())
                {
                    std::regex v_rgx("[0-9]+[a-zA-Z0-9_\\\\.-]*");
                    if (!std::regex_match(v.begin(), v.end(), v_rgx))
                        throw SBOLError(SBOL_ERROR_NONCOMPLIANT_VERSION, "SBOL-compliant versions require a major, minor, and patch number in accordance with Maven versioning schemes. Use toggleSBOLCompliance() to relax these versioning requirements.");
                }
                
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

        void set(SBOLClass& sbol_obj);                  ///< Attach a child SBOL object to a parent SBOL object
        
        /// Get the child object
        /// @tparam SBOLClass The type of the child object
        /// @param object_id The URI of the child object
        /// @return A reference to the child object
        SBOLClass& get(const std::string object_id);
        
		void add(SBOLClass& sbol_obj);                  ///< Push another child object to the list, if the property allows multiple values
        template < class SBOLSubClass > void add(SBOLSubClass& sbol_obj);  ///< Push an object of derived class to the list, eg, add a Range to a list of Locations
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
        
        /// Autoconstruct a child object with default values and add it to a parent SBOL object. The object will be intialized with default values as defined in the constructor call. After creating the object, default values can be changed using set.
        /// @param uri The identity of the new object. If operating in SBOL-compliant mode, this should simply be a displayId for the new object. The full URI will be generated automatically. If operating in open-world mode, this should be a full URI including namespace.
        SBOLClass& create(std::string uri);
        template < class SBOLSubClass > SBOLSubClass& create(std::string uri);

        void create(std::string uri_prefix, std::string display_id, std::string version);
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

		std::vector<SBOLObject*>::iterator python_iter;
	};
    
    /// @TODO Deprecate this
    template <class SBOLClass>
    void OwnedObject<SBOLClass>::create(std::string uri_prefix, std::string display_id, std::string version)
    {
        // Construct an SBOLObject with emplacement
        void* mem = malloc(sizeof(SBOLClass));
        SBOLClass* owned_obj = new (mem)SBOLClass;
        
        std::string sbol_class_name = owned_obj->getClassName(owned_obj->type);
        std::string compliant_uri = getCompliantURI(uri_prefix, sbol_class_name,  display_id, "1.0.0");
        
        owned_obj->identity.set(compliant_uri);
        owned_obj->displayId.set(display_id);
        owned_obj->version.set(version);
        add(*owned_obj);
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

    
    /// @param nIndex A numerical index
    /// @return A reference to the child object
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