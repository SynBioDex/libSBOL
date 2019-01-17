/**
 * @file    object.h
 * @brief   SBOLObject class (a low-level, abstract class)
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

#ifndef OBJECT_INCLUDED
#define OBJECT_INCLUDED

#include "validation.h"
#include "properties.h"

#include <raptor2.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
#include "Python.h"
#endif

namespace sbol
{
    
    
    /* All SBOLObjects have a pointer back to their Document.  This requires forward declaration of SBOL Document class here */
    class Document;
    
    /// An SBOLObject converts a C++ class data structure into an RDF triple store and contains methods for serializing and parsing RDF triples
    class SBOL_DECLSPEC SBOLObject
    {
        friend class Document;

        template < class LiteralType >
        friend class Property;
        
        template < class SBOLClass >
        friend class AliasedProperty;
    
    protected:
        /// @cond
        std::unordered_map<std::string, std::string> namespaces;
        std::string default_namespace;
        void serialize(raptor_serializer* sbol_serializer, raptor_world *sbol_world = NULL);  // Convert an SBOL object into RDF triples
        std::string nest(std::string& rdfxml_buffer);  // Pretty-writer that converts flat RDF/XML into nested RDF/XML (ie, SBOL)
        std::string makeQName(std::string uri);
        std::vector<rdf_type> hidden_properties;  // Hidden properties will not be serialized
        
        /// @endcond

        /// Register an extension class and its namespace, so custom data can be embedded into and read from SBOL files
        /// @tparam ExtensionClass The new class
        /// @param ns The extension namespace, eg, http://myhome.org/my_extension#. It's important that the namespace ends in a forward-slash or hash
        /// @param ns_prefix A shorthand symbol for the full namespace as it will appear in the output file, eg, my_extension
        template < class ExtensionClass > void register_extension_class(std::string ns, std::string ns_prefix, std::string class_name);
        
    public:
        
        /// @cond
        Document *doc = NULL;
        rdf_type type;
        SBOLObject* parent = NULL;
        
        std::map<sbol::rdf_type, std::vector< std::string > > properties;
        std::map<sbol::rdf_type, std::vector< sbol::SBOLObject* > > owned_objects;
        /// @endcond
        
        /// The identity property is REQUIRED by all Identified objects and has a data type of URI. A given Identified object’s identity URI MUST be globally unique among all other identity URIs. The identity of a compliant SBOL object MUST begin with a URI prefix that maps to a domain over which the user has control. Namely, the user can guarantee uniqueness of identities within this domain.  For other best practices regarding URIs see Section 11.2 of the [SBOL specification doucment](http://sbolstandard.org/wp-content/uploads/2015/08/SBOLv2.0.1.pdf).
        URIProperty identity;

        // Open-world constructor
        SBOLObject(std::string uri = "example") : SBOLObject(UNDEFINED, uri) {};
        
        virtual ~SBOLObject();
    
        /// @return The uniform resource identifier that describes the RDF-type of this SBOL Object
        virtual rdf_type getTypeURI();
        
        /// @return Parses a local class name from the RDF-type of this SBOL Object
        std::string getClassName(std::string type);

        /// Search this object recursively to see if an object or any child object with URI already exists.
        /// @param uri The URI to search for.
        /// @return A pointer to theobject with this URI if it exists, NULL otherwise
        SBOLObject* find(std::string uri);

        void cacheObjects(std::map<std::string, sbol::SBOLObject*> &objectCache);

        /// Search this object recursively to see if it contains a member property with the given RDF type.
        /// @param uri The RDF type of the property to search for.
        /// @return A pointer to the object that contains a member property with the specified RDF type, NULL otherwise
        SBOLObject* find_property(std::string uri);
        
        
        /// Search this object recursively to see if it contains a member property with the given RDF type and indicated property value.
        /// @param uri The RDF type of the property to search for.
        /// @param value The property value to match
        /// @return A vector containing all objects found that contain a member property with the specified RDF type
        std::vector<SBOLObject*> find_property_value(std::string uri, std::string value, std::vector<SBOLObject*> matches = {});

        /// Search this object recursively to see if it contains a member property with the given RDF type and indicated property value.
        /// @param uri A URI, either an ontology term or an object reference, to search for
        /// @return A vector containing all objects found that contain the URI in a property value
        std::vector<SBOLObject*> find_reference(std::string uri);
        
        /// Compare two SBOL objects or Documents. The behavior is currently undefined for objects with custom annotations or extension classes.
        /// @param comparand A pointer to the object being compared to this one.
        /// @return 1 if the objects are identical, 0 if they are different
        int compare(SBOLObject* comparand);
        
        /// Get the value of a custom annotation property by its URI
        /// @param property_uri The URI for the property
        /// @return The value of the property or SBOL_ERROR_NOT_FOUND
        std::string getPropertyValue(std::string property_uri);
        
        /// Get all values of a custom annotation property by its URI
        /// @param property_uri The URI for the property
        /// @return A vector of property values or SBOL_ERROR_NOT_FOUND
        std::vector < std::string > getPropertyValues(std::string property_uri);
        
        /// Gets URIs for all properties contained by this object. This includes SBOL core properties as well as custom annotations. Use this to find custom extension data in an SBOL file.
        /// @return A vector of URIs that identify the properties contained in this object
        std::vector < std::string > getProperties();
        
        /// Set and overwrite the value for a user-defined annotation property.
        /// @val Either a literal or URI value
        void setPropertyValue(std::string property_uri, std::string val);

        /// Append a value to a user-defined annotation property.
        /// @val Either a literal or URI value
        void addPropertyValue(std::string property_uri, std::string val);

        /// Set the value for a user-defined annotation property. Synonymous with setPropertyValue
        /// @val If the value is a URI, it should be surrounded by angle brackets, else it will be interpreted as a literal value
        void setAnnotation(std::string property_uri, std::string val);
   
        /// Get the value of a custom annotation property by its URI. Synonymous with getPropertyValue
        /// @param property_uri The URI for the property
        /// @return The value of the property or SBOL_ERROR_NOT_FOUND
        std::string getAnnotation(std::string property_uri);
        
        void apply(void (*callback_fn)(SBOLObject *, void *), void * user_data);
        
        void update_uri();
        
#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        std::unordered_map<std::string, PyObject* > PythonObjects;

        void register_extension_class(PyObject* python_class, std::string extension_name);
        
        PyObject* cast(PyObject* python_class);
#endif

        void serialize_rdfxml(std::ostream &os, size_t indentLevel);

        template < class SBOLClass > SBOLClass& cast();

        /// Use this method to destroy an SBOL object that is not contained by a parent Document.  If the object does have a parent Document, instead use doc.close() with the object's URI identity as an argument.
        /// @TODO Recurse through child objects and delete them.
        virtual void close();
        
        /// @cond        
        virtual std::string __str__();
        /// @endcond
        
    protected:
        // Open-world constructor
        SBOLObject(rdf_type type, std::string uri) :
            type(type),
            namespaces({}),
            identity(this, SBOL_IDENTITY, '0', '1', ValidationRules({ sbol_rule_10202 }), uri)
        {
            if (hasHomespace())
                identity.set(getHomespace() + "/" + uri);
        };

    };

    template <class SBOLClass>
    SBOLClass& SBOLObject::cast()
    {
        SBOLClass& new_obj = *new SBOLClass();

        // Set identity
        new_obj.identity.set(this->identity.get());
        
        // Copy properties
        for (auto it = this->properties.begin(); it != this->properties.end(); it++)
        {
            new_obj.properties[it->first] = this->properties[it->first];
        }
        for (auto it = this->owned_objects.begin(); it != this->owned_objects.end(); it++)
        {
            new_obj.owned_objects[it->first] = this->owned_objects[it->first];
        }
        for (auto it = this->namespaces.begin(); it != this->namespaces.end(); it++)
        {
            new_obj.namespaces[it->first] = this->namespaces[it->first];
        }
        for (auto it = this->hidden_properties.begin(); it != this->hidden_properties.end(); it++)
        {
            new_obj.hidden_properties.push_back(*it);
        }
        // new_obj->parent = this->parent;
        // new_obj->doc = this->doc;
        return new_obj;
    }

    /// @ingroup extension_layer
    /// @brief A reference to another SBOL object
    /// Contains a Uniform Resource Identifier (URI) that refers to an an associated object.  The object it points to may be another resource in this Document or an external reference, for example to an object in an external repository or database.  In the SBOL specification, association by reference is indicated in class diagrams by arrows with open (white) diamonds.
    class SBOL_DECLSPEC ReferencedObject : public URIProperty
    {
    protected:
        /// The RDF type of objects referenced by this property.
        rdf_type reference_type_uri;
    public:
        ReferencedObject(void *property_owner, rdf_type type_uri, rdf_type reference_type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, std::string initial_value);

        ReferencedObject(void *property_owner, rdf_type type_uri, rdf_type reference_type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules);

        ReferencedObject(void *property_owner, rdf_type type_uri, rdf_type reference_type_uri, char lower_bound, char upper_bound, char const * initial_value) : ReferencedObject(property_owner, type_uri, reference_type_uri, lower_bound, upper_bound, ValidationRules({}), initial_value) {};

        ReferencedObject(void *property_owner, rdf_type type_uri, rdf_type reference_type_uri, char lower_bound, char upper_bound) : ReferencedObject(property_owner, type_uri, reference_type_uri, lower_bound, upper_bound, ValidationRules({})) {};

        /// Creates a new SBOL object corresponding to the RDF type specified in the Property definition
        /// @param uri A Uniform Resource Identifier (URI) for the new object, or a displayId if operating in SBOL-compliant mode (library default)
        /// @return The full URI of the created object
        std::string create(std::string uri);

        /// Set the property with a URI reference to an object
        /// @param The full URI of the referenced object, e.g., my_obj.identity.get()
        void set(std::string uri);

        /// Set the property with a URI reference to an object, overwriting the first value in the property store
        /// @param The referenced object
        void set(SBOLObject& obj);

        /// Append a URI reference of an object to the property store
        /// @param uri The full URI of the referenced object, e.g., my_obj.identity.get()
        void add(std::string uri);

        /// Append a URI reference of an object to the property store
        /// @param The referenced object
        void add(SBOLObject& obj);

        //void set(SBOLClass& sbol_obj);
        //SBOLClass& get(std::string object_id);
        std::string operator[] (const int nIndex);
        void addReference(const std::string uri);
        void setReference(const std::string uri);

        
//        /// Provides iterator functionality for SBOL properties that contain multiple references
//        class iterator : public std::vector<std::string>::iterator
//        {
//        public:
//            iterator( std::vector<std::string>::iterator i_str = std::vector<std::string>::iterator()) : std::vector<std::string>::iterator(i_str)
//            {
//            }
//            
//            std::string operator*()
//            {
//                std::string val = std::vector<std::string>::iterator::operator*();
//                val = val.substr(1, val.size() - 2);  // Trim bracketing "" or <> off of literal values
//                return val;
//            }
//        };
//        
//        iterator begin()
//        {
//            std::vector<std::string> *object_store = &this->sbol_owner->properties[this->type];
//            return iterator(object_store->begin());
//        };
//        
//        iterator end()
//        {
//            std::vector<std::string> *object_store = &this->sbol_owner->properties[this->type];
//            return iterator(object_store->end());
//        };
//        
//        int size()
//        {
//            std::size_t size = this->sbol_owner->properties[this->type].size();
//            std::string current_value = this->sbol_owner->properties[this->type][0];
//            if (size == 1)
//            {
//                if (current_value.compare("<>") == 0 || current_value.compare("\"\"") == 0)  // Empty fields retain <> or "" to distinguish between URIs and literals
//                    return 0;
//            }
//            return (int)size;
//        };
//        
//        std::vector<std::string>::iterator python_iter;
        
#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        std::string __getitem__(const int nIndex)
        {
            return this->operator[](nIndex);
        }
        
        ReferencedObject* __iter__()
        {
            this->python_iter = ReferencedObject::iterator(this->begin());
            return this;
        }
        
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

    };
    
    
    bool operator !=(const SBOLObject &a, const SBOLObject &b);
    
    
    
    /// A container property that contains child objects. Creates a composition out of two or more classes.  In the SBOL specification, compositional relationships are indicated in class diagrams by arrows with black diamonds. A compositional relationship means that deleting the parent object will delete the child objects, and adding the parent object to a Document will also add the child object.  Owned objects are stored in arbitrary order.
    /// @ingroup extension_layer
    /// @tparam SBOLClass The type of child SBOL object contained by this Property
	template <class SBOLClass>
	class OwnedObject : public Property<SBOLClass>
	{
	public:
        /// Initialize a container and put the first object in it. Validation rules are checked upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        OwnedObject(void *property_owner, rdf_type sbol_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, SBOLObject& first_object);

        /// Initialize a container property. No validation rules are run upon initialization.
        /// @param type_uri An RDF type for the property which determines how the property is serialized in SBOL files
        /// @param lower_bound A char flag (typically '0' or '1') indicating the minimum number of values allowed for this property
        /// @param upper_bound A char flag (typically '1' or '*') indicating the maximum number of values allowed for this property
        /// @param validation_rules A vector of pointers to the validation functions
        OwnedObject(void *property_owner, rdf_type sbol_uri, char lower_bound, char upper_bound, ValidationRules validation_rules);

        OwnedObject(void *property_owner, rdf_type sbol_uri, char lower_bound, char upper_bound, SBOLObject& first_object) : OwnedObject(property_owner, sbol_uri, lower_bound, upper_bound, ValidationRules({}), first_object) {};

        OwnedObject(void *property_owner, rdf_type sbol_uri, char lower_bound, char upper_bound) : OwnedObject(property_owner, sbol_uri, lower_bound, upper_bound, ValidationRules({})) {};
        
        /// @tparam SBOLClass The type of SBOL object contained in this OwnedObject property
        /// @param sbol_obj A child object to add to this container property.
        /// Assigns a child object to this OwnedObject container property. This method always overwrites the first SBOLObject in the container. appends another object to those already contained in this OwnedObject property. In SBOLCompliant mode, the create method is preferred
        void set(SBOLClass& sbol_obj);

        void set_notoplevelcheck(SBOLClass& sbol_obj);

        /// @tparam SBOLClass The type of SBOL object contained in this OwnedObject property
        /// @param sbol_obj A child object to add to this container property.
        /// Adds a child object to the parent object. This method always appends another object to those already contained in this OwnedObject property. In SBOLCompliant mode, the create method is preferred
		void add(SBOLClass& sbol_obj);
        
        /// @tparam SBOLClass The type of SBOL object contained in this OwnedObject property
        /// @tparam SBOLSubClass A derived class of SBOLClass. Use this type specialization when adding multiple types of SBOLObjects to a container.
        /// @param sbol_obj A child object to add to this container property.
        /// Adds a child object to the parent object. This method always appends another object to those already contained in this OwnedObject property. In SBOLCompliant mode, the create method is preferred
//        template < class SBOLSubClass > void add(SBOLSubClass& sbol_obj);

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
        std::vector<SBOLClass*> getAll();

        /// Remove an object from the list of objects.
        /// @param uri This can be a displayId of the object or a full URI may be provided.
        SBOLClass& remove(std::string uri);

        /// Remove an object from the list of objects and destroy it.
        /// @param index A numerical index for the object.
        void remove(int index = 0) override;

        /// Remove all children objects from the parent and destroy them.
        void clear() override;
        
        /// Autoconstructs a child object and attaches it to the parent object. The new object will be constructed with default values specified in the constructor for this type of object. If SBOLCompliance is enabled, the child object's identity will be constructed using the supplied displayId argument.  Otherwise, the user should supply a full URI.
        /// @tparam SBOLClass The type of SBOL object that will be created
        /// @param uri If SBOLCompliance is enabled, this should be the displayId for the new child object.  If not enabled, this should be a full raw URI.
        /// @return A reference to the child object
        /// @TODO check uniqueness of URI in Document
        SBOLClass& create(std::string uri);

        /// Autoconstructs a child object and attaches it to the parent object. Additionally, it sets the definition property of the child object, for example, in the case of creating Components, FunctionalComponents, and Modules. The new object will be constructed with default values specified in the constructor for this type of object. If SBOLCompliance is enabled, the child object's identity will be constructed using the supplied displayId argument.  Otherwise, the user should supply a full URI.
        /// @tparam SBOLClass The type of SBOL object that will be created
        /// @param definition_object The returned object will reference the definition_object in its definition property.
        /// @return A reference to the child object
        /// @TODO check uniqueness of URI in Document
        SBOLClass& define(SBOLObject& definition_object);
        
        /// @tparam SBOLClass The type of SBOL object contained in this OwnedObject property
        /// @tparam SBOLSubClass A derived class of SBOLClass. Use this specialization for OwnedObject properties which contain multiple types of SBOLObjects.
        /// @param uri If SBOLCompliance is enabled, this should be the displayId for the new child object.  If not enabled, this should be a full raw URI.
        /// @return A reference to the child object
        /// Autoconstructs a child object and attaches it to the parent object. The new object will be constructed with default values specified in the constructor for this type of object. If SBOLCompliance is enabled, the child object's identity will be constructed using the supplied displayId argument.  Otherwise, the user should supply a full URI.
        /// @TODO check uniqueness of URI in Document
        template < class SBOLSubClass > SBOLSubClass& create(std::string uri);

        /// @param uri The full uniform resource identifier of the object to search for in this property
        /// @return A boolean indicating whether found or not
        bool find(std::string uri) override;

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
        
//        SBOLClass& __getitem__(const int nIndex)
//        {
//            return this->operator[](nIndex);
//        }
//        
//        SBOLClass& __getitem__(const std::string uri)
//        {
//            return this->operator[](uri);
//        }
        
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
    OwnedObject< SBOLClass >::OwnedObject(void *property_owner, rdf_type sbol_uri, char lower_bound, char upper_bound, ValidationRules validation_rules) :
        Property < SBOLClass > (property_owner, sbol_uri, lower_bound, upper_bound, validation_rules)
    {
        // Register Property in owner Object
        if (this->sbol_owner != NULL)
        {
            // Clear property store created by base constructor and re-initialize in the owned_objects property store
            this->sbol_owner->properties.erase(sbol_uri);
            std::vector<sbol::SBOLObject*> object_store;
            this->sbol_owner->owned_objects.insert({ sbol_uri, object_store });
        }
    };

    template <class SBOLClass>
    OwnedObject< SBOLClass >::OwnedObject(void *property_owner, rdf_type sbol_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, SBOLObject& first_object) : OwnedObject < SBOLClass > (property_owner, sbol_uri, lower_bound, upper_bound, validation_rules)
    {
        this->sbol_owner->owned_objects[sbol_uri].push_back(&first_object);
    };


//    template <class SBOLClass>
//    template <class SBOLSubClass>
//    void OwnedObject< SBOLClass >::add(SBOLSubClass& sbol_obj)
//    {
//        std::cout << "Calling subclass adder" << std::endl;
//        SBOLClass* cast_obj = dynamic_cast<SBOLClass*>(&sbol_obj);
//        if (!cast_obj)
//            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Object of type " + parseClassName(sbol_obj.type) + " is invalid for " + parsePropertyName(this->type) + " property");
//        else
//            this->add(*cast_obj);
//    };

    template <class SBOLClass>
    bool OwnedObject< SBOLClass >::find(std::string uri)
    {
        for (auto & obj : this->sbol_owner->owned_objects[this->type])
        {
            if (obj->identity.get() == uri)
                return true;
        }
        if (Config::getOption("sbol_compliant_uris") == "True")
            if (this->sbol_owner->properties.find(SBOL_DISPLAY_ID) != this->sbol_owner->properties.end())
                for (auto & obj : this->sbol_owner->owned_objects[this->type])
                {
                    if (obj->properties[SBOL_DISPLAY_ID].front() == "\"" + uri + "\"")
                        return true;
                }           
        return false;
    };


    template <class SBOLClass>
    SBOLClass& OwnedObject<SBOLClass>::operator[] (const int nIndex)
    {
        if (nIndex >= this->size())
            throw SBOLError(SBOL_ERROR_NOT_FOUND, "Index out of range");
        std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
        return (SBOLClass&)*object_store->at(nIndex);
    };
}

#endif /* OBJECT_INCLUDED */
