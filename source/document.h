/**
 * @file    document.h
 * @brief   Document class, serialization method, and some low-level accessor methods
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

#ifndef DOCUMENT_INCLUDED
#define DOCUMENT_INCLUDED

//#include <libxml/xmlexports.h>
#include "componentdefinition.h"
#include "sequenceannotation.h"
#include "sequence.h"
#include "component.h"
#include "moduledefinition.h"
#include "module.h"
#include "model.h"
#include "collection.h"
#include "provo.h"
#include "attachment.h"
#include "combinatorialderivation.h"
#include "implementation.h"

#include <raptor2.h>
#include <unordered_map>
#include <istream>
#include <algorithm>

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
#include "Python.h"
#undef tolower
#endif

namespace sbol {

    /* <!--- Methods for SBOL extension classes ---> */
    
    /// @cond
    // This is the global SBOL register for classes.  It maps an SBOL RDF type (eg, "http://sbolstandard.org/v2#Sequence" to a constructor
    extern std::unordered_map<std::string, sbol::SBOLObject&(*)()> SBOL_DATA_MODEL_REGISTER;
    /// @endcond

    
    /// Read and write SBOL using a Document class.  The Document is a container for Components, Modules, and all other SBOLObjects
    class SBOL_DECLSPEC Document : public Identified
    {
        friend class SBOLObject;
        
	private:
        std::string home; ///< The authoritative namespace for the Document. Setting the home namespace is like signing a piece of paper.
        int SBOLCompliant; ///< Flag indicating whether to autoconstruct URI's consistent with SBOL's versioning scheme
        ValidationRules validationRules;  ///< A list of validation functions to run on the Document prior to serialization
        raptor_world *rdf_graph;  ///< RDF triple store that holds SBOL objects and properties
        
	public:
        /// Construct a Document.  The Document is a container for Components, Modules, and all other SBOLObjects
		Document() :
            Identified(SBOL_DOCUMENT, ""),
            home(""),
            SBOLCompliant(0),
			rdf_graph(raptor_new_world()),
            validationRules({ }),
            componentDefinitions(SBOL_COMPONENT_DEFINITION, this),
            moduleDefinitions(SBOL_MODULE_DEFINITION, this),
            models(SBOL_MODEL, this),
            sequences(SBOL_SEQUENCE, this),
            sequenceAnnotations(SBOL_SEQUENCE_ANNOTATION, this),
            collections(SBOL_COLLECTION, this),
            activities(PROVO_ACTIVITY, this),
            plans(PROVO_PLAN, this),
            agents(PROVO_AGENT, this),
            attachments(SBOL_ATTACHMENT, this),
            combinatorialderivations(SBOL_COMBINATORIAL_DERIVATION, this),
            implementations(SBOL_IMPLEMENTATION, this),
            citations(PURL_URI "bibliographicCitation", this),
            keywords(PURL_URI "elements/1.1/subject", this)
			{
                namespaces["sbol"] = SBOL_URI "#";
                namespaces["dcterms"] = PURL_URI;
                namespaces["prov"] = PROV_URI "#";
			};
        
        Document(std::string filename) :
            Document()
        {
            read(filename);
        }
        
        ~Document() override;
        
        /// @cond
        /// The Document's register of objects
		std::unordered_map<std::string, sbol::SBOLObject*> SBOLObjects;

//#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
//        // Register of Python objects, for use when building Python bindings
//        std::unordered_map<std::string, PyObject*> PythonObjects;
//#endif
        
        TopLevel& getTopLevel(std::string);
        raptor_world* getWorld();
        /// @endcond

        List<OwnedObject<ComponentDefinition>> componentDefinitions;
        List<OwnedObject<ModuleDefinition>> moduleDefinitions;
        List<OwnedObject<Model>> models;
        List<OwnedObject<Sequence>> sequences;
        List<OwnedObject<SequenceAnnotation>> sequenceAnnotations;
        List<OwnedObject<Collection>> collections;
        List<OwnedObject<Activity>> activities;
        List<OwnedObject<Plan>> plans;
        List<OwnedObject<Agent>> agents;
        List<OwnedObject<Attachment>> attachments;
        List<OwnedObject<CombinatorialDerivation>> combinatorialderivations;
        List<OwnedObject<Implementation>> implementations;

        URIProperty citations;
        URIProperty keywords;
        

        /// Register an object in the Document
        /// @param sbol_obj The SBOL object you want to serialize
        /// @tparam SBOLClass The type of SBOL object
		template < class SBOLClass > void add(SBOLClass& sbol_obj);
        
        /// Register an object in the Document
        /// @param sbol_objects A list of pointers to the SBOL objects you want to serialize
        /// @tparam SBOLClass The type of SBOL object
        template < class SBOLClass > void add(std::vector < SBOLClass* > sbol_objects);
        
        /// Retrieve an object from the Document
        /// @param uri The identity of the SBOL object you want to retrieve
        /// @tparam SBOLClass The type of SBOL object
        template < class SBOLClass > SBOLClass& get(std::string uri);
        
        /// Retrieve a vector of objects from the Document
        /// @tparam SBOLClass The type of SBOL objects
        template < class SBOLClass > std::vector<SBOLClass*> getAll();

        /// Serialize all objects in this Document to an RDF/XML file
        /// @param filename The full name of the file you want to write (including file extension)
        /// @return A string with the validation results, or empty string if validation is disabled
        std::string write(std::string filename);

        /// Read an RDF/XML file and attach the SBOL objects to this Document. Existing contents of the Document will be wiped.
        /// @param filename The full name of the file you want to read (including file extension)
        void read(std::string filename);

        /// Convert text in SBOL into data objects
        /// @param sbol A string formatted in SBOL
        void readString(std::string& sbol);
        
        /// Convert data objects in this Document into textual SBOL
        std::string writeString();
        
        /// Read an RDF/XML file and attach the SBOL objects to this Document. New objects will be added to the existing contents of the Document
        /// @param filename The full name of the file you want to read (including file extension)
        void append(std::string filename);
        
        /// Submit this Document to the online validator.
        /// @return The validation results
        std::string request_validation(std::string& sbol);

        std::string query_repository(std::string command);

        std::string search_metadata(std::string role, std::string type, std::string name, std::string collection);
        
		/// Generates rdf/xml
        void generate(raptor_world** world, raptor_serializer** sbol_serializer, char** sbol_buffer, size_t* sbol_buffer_len, raptor_iostream** ios, raptor_uri** base_uri);

        /// Run validation on this Document.
        /// @return The validation results
        std::string validate();
        
        Document& copy(std::string ns, Document* doc = NULL);
        
        /// Get the total number of objects in the Document, including SBOL core object and custom annotation objects
        int size()
        {
            std::size_t size = this->SBOLObjects.size();
            return (int)size;
        }
        
        int __len__()
        {
            return this->size();
        }
        
        /// Provides iterator functionality for SBOL properties that contain multiple objects
        class iterator : public std::vector<SBOLObject*>::iterator
        {
        public:
            
            iterator(typename std::vector<SBOLObject*>::iterator i_object = std::vector<SBOLObject*>::iterator()) : std::vector<SBOLObject*>::iterator(i_object)
            {
            }
            
            SBOLObject& operator*()
            {
                return (SBOLObject&) *std::vector<SBOLObject*>::iterator::operator *();
            }
        };
        
        iterator begin()
        {
            std::vector<SBOLObject*> object_store;
            for (auto & entry : SBOLObjects)
                object_store.push_back(entry.second);
            return iterator(object_store.begin());
        };
        
        iterator end()
        {
            std::vector<SBOLObject*> object_store;
            for (auto & entry : SBOLObjects)
                object_store.push_back(entry.second);
            return iterator(object_store.end());
        };
        
        std::vector<SBOLObject*>::iterator python_iter;
        
        /// Search recursively for an SBOLObject in this Document that matches the uri
        /// @param uri The identity of the object to search for
        /// @return A pointer to the SBOLObject, or NULL if an object with this identity doesn't exist
        SBOLObject* find(std::string uri);
        
        /// @cond
        // Handler-functions for the Raptor library's RDF parsers
        static void parse_objects(void* user_data, raptor_statement* triple);
		static void parse_properties(void* user_data, raptor_statement* triple);
        static void namespaceHandler(void *user_data, raptor_namespace *nspace);
        void addNamespace(std::string ns, std::string prefix, raptor_serializer* sbol_serializer);
        void parse_annotation_objects();
        void parse_extension_objects();

        SBOLObject* find_property(std::string uri);
        std::vector<SBOLObject*> find_reference(std::string uri);
        /// @endcond
        
        /// @return A vector of namespaces
        /// Get namespaces contained in this Document
        std::vector<std::string> getNamespaces();
        
        /// Add a new namespace to this Document
        /// @param ns The namespace, eg. http://sbols.org/v2#
        /// @param prefix The namespace prefix, eg. sbol
        void addNamespace(std::string ns, std::string prefix);
        
//		std::vector<SBOLObject*> flatten();

        /// Delete all objects in this Document and destroy the Document
        void close(std::string uri = "");

        void addComponentDefinition(ComponentDefinition& sbol_obj)
        {
            add<ComponentDefinition>(sbol_obj);
        }
        
        void addModuleDefinition(ModuleDefinition& sbol_obj)
        {
            add<ModuleDefinition>(sbol_obj);
        }
        
        void addSequence(Sequence& sbol_obj)
        {
            add<Sequence>(sbol_obj);
        }
        
        void addModel(Model& sbol_obj)
        {
            add<Model>(sbol_obj);
        }
        

        
//        /// Iterates over SBOL objects in a Document
//        class iterator : public std::unordered_map<std::string, sbol::SBOLObject*>::iterator
//        {
//        public:
//            
//            iterator(typename std::unordered_map<std::string, sbol::SBOLObject*>::iterator i_obj = std::unordered_map<std::string, sbol::SBOLObject*>::iterator()) : std::unordered_map<std::string, sbol::SBOLObject*>::iterator(i_obj)
//            {
//            }
//        };
//        
//        iterator begin()
//        {
//            std::unordered_map<std::string, sbol::SBOLObject*> *object_store = &this->SBOLObjects;
//            return iterator(object_store->begin());
//        };
//        
//        iterator end()
//        {
//            std::unordered_map<std::string, sbol::SBOLObject*> *object_store = &this->SBOLObjects;
//            return iterator(object_store->end());
//        };
//        
//        int size()
//        {
//            std::size_t size = this->SBOLObjects.size();
//            return (int)size;
//        };
//        
//        std::vector<sbol::SBOLObject>::iterator python_iter;
        
	};

	template <class SBOLClass > void Document::add(SBOLClass& sbol_obj)
	{
		// Check if the uri is already assigned and delete the object, otherwise it will cause a memory leak!!!
		//if (SBOLObjects[whatever]!=SBOLObjects.end()) {delete SBOLObjects[whatever]'}
        if (this->SBOLObjects.find(sbol_obj.identity.get()) != this->SBOLObjects.end())
            throw SBOLError(DUPLICATE_URI_ERROR, "Cannot create " + sbol_obj.identity.get() + ". An object with this identity is already contained in the Document");
        else
        {
            // If TopLevel add the Document
            TopLevel* check_top_level = dynamic_cast<TopLevel*>(&sbol_obj);
            if (check_top_level)
            {
                SBOLObjects[sbol_obj.identity.get()] = (SBOLObject*)&sbol_obj;
                sbol_obj.parent = this;  // Set back-pointer to parent object
                this->owned_objects[sbol_obj.getTypeURI()].push_back((SBOLClass*)&sbol_obj);  // Add the object to the Document's property store, eg, componentDefinitions, moduleDefinitions, etc.
            }
            sbol_obj.doc = this;
            
            // Recurse into child objects and set their back-pointer to this Document
            for (auto i_store = sbol_obj.owned_objects.begin(); i_store != sbol_obj.owned_objects.end(); ++i_store)
            {
                std::vector<SBOLObject*>& object_store = i_store->second;
                for (auto i_obj = object_store.begin(); i_obj != object_store.end(); ++i_obj)
                {
                    this->add<SBOLObject>(**i_obj);
                }
            }
        }
	};

    template < class SBOLClass > void Document::add(std::vector < SBOLClass* > sbol_objects)
    {
        for (auto i_obj = sbol_objects.begin(); i_obj != sbol_objects.end(); ++i_obj)
        {
            SBOLClass& obj = **i_obj;
            add < SBOLClass > (obj);
        }
    };
    
	template <class SBOLClass > SBOLClass& Document::get(std::string uri)
	{
        // Search the Document's object store for the uri
        if (SBOLObjects.find(uri) != SBOLObjects.end())
            return (SBOLClass &)*(SBOLObjects[uri]);
        
        // In SBOLCompliant mode, the user may retrieve an object by persistentIdentity as well
        if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
        {
            std::vector < std::string > ids;  // Contains all URIs contaning the persistentIdentity
            
            // Search the Document's object map for  property's object store for all URIs prefixed with the persistentIdentity
            for (auto i_obj = SBOLObjects.begin(); i_obj != SBOLObjects.end(); ++i_obj)
            {
                std::string obj_id = i_obj->first;
                SBOLObject* obj = i_obj->second;
                std::string persistent_id = "";

                if (obj->properties.find(SBOL_PERSISTENT_IDENTITY) != obj->properties.end())
                {
                    persistent_id = obj->properties[SBOL_PERSISTENT_IDENTITY][0];
                    persistent_id = persistent_id.substr(1, persistent_id.size() - 2);  // Removes flanking " from the version field
                }
                if (uri.compare(persistent_id) == 0)
                    ids.push_back(obj_id);
            }
            
            // Get the latest version
            std::sort(ids.begin(), ids.end());
            if (ids.size() > 0)
            {
                uri = ids.back();
                return (SBOLClass &)*(SBOLObjects[uri]);
            }
        }
        throw SBOLError(NOT_FOUND_ERROR, "Object " + uri + " not found");
	};
    
    
    // This is a wrapper function for constructors.  This allows us to construct an SBOL object using a function pointer (direct pointers to constructors are not supported by C++)
    template < class SBOLClass >
    sbol::SBOLObject& create()
    {
        // Construct an SBOLObject with emplacement
        void* mem = malloc(sizeof(SBOLClass));
        SBOLClass* a = new (mem) SBOLClass;
        return (sbol::SBOLObject&)*a;
    };
    
//    /// @TODO Deprecate this
//    template <class SBOLClass>
//    void register_extension(std::string ns_prefix, std::string uri)
//    {
//        SBOL_DATA_MODEL_REGISTER.insert(make_pair(uri, (SBOLObject&(*)())&create<SBOLClass>));
//        // TODO: register ns_prefix in SBOLObject
//    };
    
    /* <!--- Handler functions used by Raptor for parsing ---> */

    /// @cond
    void raptor_error_handler(void *user_data, raptor_log_message* message);
    /// @endcond
    
    /* <!--- Utility methods for processing raw XML ---> */

    /// @cond
    std::string convert_ntriples_encoding_to_ascii(std::string s);     // Convert ntriple encoding down to ascii, removing escape codes. See https://www.w3.org/TR/2004/REC-rdf-testcases-20040210/#ntrip_strings
	std::string cut_sbol_resource(std::string& xml_string, const std::string resource_id);
    void replace_reference_to_resource(std::string& xml_string, const std::string property_name, const std::string resource_id, std::string& replacement_text);
	void seek_element(std::istringstream& xml_buffer, std::string uri);
    void seek_property_element(std::istringstream& xml_buffer, std::string property_name);
	void seek_next_element(std::istringstream& xml_buffer);
	void seek_new_line(std::istringstream& xml_buffer);
	void seek_end_of_line(std::istringstream& xml_buffer);
	void seek_end_of_element(std::istringstream& xml_buffer);
	void seek_end_of_node(std::istringstream& xml_buffer, std::string uri);
    void seek_resource(std::istringstream& xml_buffer, std::string qname, std::string resource_uri);
	bool is_open_node(std::istringstream& xml_buffer);
	void indent(std::string& text, int indentation); 
	std::string get_qname(std::istringstream& xml_buffer);
	std::string get_local_part(std::string qname);
	std::string get_prefix(std::string qname);
	std::vector<std::string> parse_element(std::istringstream& xml_buffer);
    /// @endcond

    /* <!--- Accessor functions for SBOL properties ---> */

    template < class SBOLClass >
    std::vector<SBOLClass*> OwnedObject<SBOLClass>::getObjects()
    {
        std::vector<SBOLClass*> vector_copy;
        for (auto o = this->sbol_owner->owned_objects[this->type].begin(); o != this->sbol_owner->owned_objects[this->type].end(); o++)
        {
            vector_copy.push_back((SBOLClass*)*o);
        }
        return vector_copy;
    };
    
    template <class SBOLClass>
    SBOLClass& OwnedObject<SBOLClass>::create(std::string uri)
    {
        // This is a roundabout way of checking if SBOLClass is TopLevel in the Document
        int CHECK_TOP_LEVEL;
        Document* parent_doc = dynamic_cast<Document*>(this->sbol_owner);
        if (parent_doc)
            CHECK_TOP_LEVEL = 1;
        else
        {
            CHECK_TOP_LEVEL = 0;
            parent_doc = this->sbol_owner->doc;
        }
        SBOLObject* parent_obj = this->sbol_owner;

        if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
        {
            SBOLClass* child_obj = new SBOLClass();

            // Form compliant URI for child object
            std::string persistent_id;
            std::string version;
            if (!CHECK_TOP_LEVEL && parent_obj->properties.find(SBOL_PERSISTENT_IDENTITY) != parent_obj->properties.end())
            {
                persistent_id = parent_obj->properties[SBOL_PERSISTENT_IDENTITY].front();
                persistent_id = persistent_id.substr(1, persistent_id.length() - 2);  // Removes flanking < and > from the uri
            }
            else
            {
                // If object is TopLevel, intialize the URI
                persistent_id = getHomespace();
                if (Config::getOption("sbol_typed_uris").compare("True") == 0)
                    persistent_id += "/" + parseClassName(child_obj->getTypeURI());
            }
            if (parent_obj->properties.find(SBOL_VERSION) != parent_obj->properties.end())
            {
                version = parent_obj->properties[SBOL_VERSION].front();
                version = version.substr(1, version.length() - 2);  // Removes flanking " from the uri
            }
            else
            {
                version = VERSION_STRING;
            }
            std::string child_persistent_id =  persistent_id + "/" + uri;
            std::string child_id = child_persistent_id + "/" + version;
            
            // Check for uniqueness of URI in the Document
            if (parent_doc && parent_doc->find(child_id))
                throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + child_id + " is already in the Document");

            // Construct a new child object
//            SBOLClass* child_obj = new SBOLClass(uri);
            
                                                      
            // Initialize SBOLCompliant properties
            child_obj->identity.set(child_id);
            child_obj->persistentIdentity.set(child_persistent_id);
            child_obj->displayId.set(uri);
            child_obj->version.set(version);

            // Add the new object to this OwnedObject property
            // this->add(*child_obj);   Can't use this because the add method is prohibited in SBOLCompliant mode!!!
            child_obj->parent = parent_obj;  // Set back-pointer to parent object
            std::vector< sbol::SBOLObject* >& object_store = this->sbol_owner->owned_objects[this->type];
            object_store.push_back((SBOLObject*)child_obj);

            // The following effectively adds the child object to the Document by setting its back-pointer.  However, the Document itself only maintains a register of TopLevel objects, otherwise the returned object will not be registered
            if (parent_doc)
                child_obj->doc = parent_doc;
            if (CHECK_TOP_LEVEL)
                parent_doc->SBOLObjects[child_id] = (SBOLObject*)child_obj;
            
            this->validate(child_obj);
            return *child_obj;
        }
        else
        {
            if (parent_doc && parent_doc->find(uri))
                throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + uri + " is already in the Document");
            
            // Construct a new child object
            SBOLClass* child_obj = new SBOLClass(uri);
            Identified* parent_obj = (Identified*)this->sbol_owner;
            child_obj->parent = parent_obj;  // Set back-pointer to parent object
            
            child_obj->identity.set(uri);
            child_obj->persistentIdentity.set(uri);
            
            this->add(*child_obj);
            if (parent_obj->doc)
                child_obj->doc = parent_obj->doc;
            
            this->validate(child_obj);
            return *child_obj;
        }
    };

    template < class SBOLClass>
    template < class SBOLSubClass >
    SBOLSubClass& OwnedObject<SBOLClass>::create(std::string uri)
    {
        // This is a roundabout way of checking if SBOLClass is TopLevel in the Document
        int CHECK_TOP_LEVEL;
        Document* parent_doc = dynamic_cast<Document*>(this->sbol_owner);
        if (parent_doc)
            CHECK_TOP_LEVEL = 1;
        else
        {
            CHECK_TOP_LEVEL = 0;
            parent_doc = this->sbol_owner->doc;
        }
        SBOLObject* parent_obj = this->sbol_owner;
        
        if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
        {
            // Form compliant URI for child object
            std::string persistent_id;
            std::string version;
            if (parent_obj->properties.find(SBOL_PERSISTENT_IDENTITY) != parent_obj->properties.end())
            {
                persistent_id = parent_obj->properties[SBOL_PERSISTENT_IDENTITY].front();
                persistent_id = persistent_id.substr(1, persistent_id.length() - 2);  // Removes flanking < and > from the uri
            }
            else
            {
                persistent_id = getHomespace();
            }
            if (parent_obj->properties.find(SBOL_VERSION) != parent_obj->properties.end())
            {
                version = parent_obj->properties[SBOL_VERSION].front();
                version = version.substr(1, version.length() - 2);  // Removes flanking " from the uri
            }
            else
            {
                version = VERSION_STRING;
            }
            std::string child_persistent_id =  persistent_id + "/" + uri;
            std::string child_id = child_persistent_id + "/" + version;
            
            // Check for uniqueness of URI in the Document
            if (parent_doc && parent_doc->find(child_id))
                throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + child_id + " is already in the Document");
            
            // Construct a new child object
            SBOLSubClass* child_obj = new SBOLSubClass(child_id);
            
            // Initialize SBOLCompliant properties
            child_obj->identity.set(child_id);
            child_obj->persistentIdentity.set(child_persistent_id);
            child_obj->displayId.set(uri);
            child_obj->version.set(version);
            
            // Add the new object to this OwnedObject property
            // this->add(*child_obj);   Can't use this because the add method is prohibited in SBOLCompliant mode!!!
            child_obj->parent = parent_obj;  // Set back-pointer to parent object
            std::vector< sbol::SBOLObject* >& object_store = this->sbol_owner->owned_objects[this->type];
            object_store.push_back(child_obj);
            
            // The following effectively adds the child object to the Document by setting its back-pointer.  However, the Document itself only maintains a register of TopLevel objects, otherwise the returned object will not be registered
            if (parent_doc)
                child_obj->doc = parent_doc;
            if (CHECK_TOP_LEVEL)
                parent_doc->SBOLObjects[child_id] = (SBOLObject*)child_obj;

            this->validate(child_obj);
            return *child_obj;
        }
        else
        {
            if (parent_doc && parent_doc->find(uri))
                throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + uri + " is already in the Document");
            
            // Construct an SBOLObject with emplacement
            SBOLSubClass* child_obj = new SBOLSubClass(uri);
            Identified* parent_obj = (Identified*)this->sbol_owner;
            
            child_obj->identity.set(uri);
            child_obj->persistentIdentity.set(uri);
            
            this->add(*child_obj);
            if (parent_obj->doc)
                child_obj->doc = parent_obj->doc;
            
            this->validate(child_obj);
            return *child_obj;
        }
    };
    
    template <class SBOLClass>
    void OwnedObject<SBOLClass>::add(SBOLClass& sbol_obj)
    {
        if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "Cannot add " + sbol_obj.identity.get() + " to " + this->sbol_owner->identity.get() + ". The " + parseClassName(this->sbol_owner->type) + "::" + parseClassName(this->type) + "::add method is prohibited while operating in SBOL-compliant mode and is only available when operating in open-world mode. Use the " + parseClassName(this->sbol_owner->type) + "::" + parseClassName(this->type) + "::create method instead or use toggleSBOLCompliance to enter open-world mode");
        if (this->sbol_owner)
        {
            if (this->sbol_owner->type.compare(SBOL_DOCUMENT) == 0)
            {
                Document& doc = (Document &)*this->sbol_owner;
                doc.add<SBOLClass>(sbol_obj);
            }
            else
            {
                std::vector< sbol::SBOLObject* >& object_store = this->sbol_owner->owned_objects[this->type];
                if (std::find(object_store.begin(), object_store.end(), &sbol_obj) != object_store.end())
                    throw SBOLError(DUPLICATE_URI_ERROR, "The object " + sbol_obj.identity.get() + " is already contained by the property");
                else
                {
                    sbol_obj.parent = this->sbol_owner;  // Set back-pointer to parent object
                    object_store.push_back((SBOLObject *)&sbol_obj);
                    if (this->sbol_owner->doc)
                    {
                        sbol_obj.doc = this->sbol_owner->doc;
                    }
                }
            }
        }
    };
    

    template <class SBOLClass>
    SBOLClass& OwnedObject<SBOLClass>::get(const std::string uri)
    {
        // By default, get the first object in the object store...
        if (uri.compare("") == 0)
        {
            // This should use dynamic_cast instead of implicit casting
            SBOLObject* obj = this->sbol_owner->owned_objects[this->type][0];
            return (SBOLClass&)*obj;
        }
        // ...else search the object store for an object matching the id
        else
        {
            SBOLClass& obj = this->operator[](uri);
            return obj;
        }
//        std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
//        for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
//        {
//            SBOLObject* obj = *i_obj;
//            if (object_id.compare(obj->identity.get()) == 0)
//            {
//                return (SBOLClass&)*obj;
//            }
//        }
//        throw SBOLError(NOT_FOUND_ERROR, "Object " + object_id + " not found");
    };
    
    template <class SBOLClass>
    template <class SBOLSubClass>
    SBOLSubClass& OwnedObject< SBOLClass >::get(std::string uri)
    {
        if (uri.compare("") == 0)
        {
            // This should use dynamic_cast instead of implicit casting
            SBOLObject* obj = this->sbol_owner->owned_objects[this->type][0];
            return (SBOLSubClass&)*obj;
        }
        else
        {
            SBOLClass* obj = &this->operator[](uri);
            return (SBOLSubClass&)*obj;
        }
    };
    
    template <class SBOLClass>
    SBOLClass& OwnedObject<SBOLClass>::operator[] (std::string uri)
    {
        // Search this property's object store for the uri
        std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
        for (auto i_obj = object_store->begin(); i_obj != object_store->end(); ++i_obj)
        {
            SBOLObject* obj = *i_obj;
            if (uri == obj->identity.get())
            {
                return (SBOLClass&)*obj;
            }
        }
        // In SBOLCompliant mode, the user may retrieve an object by displayId as well
        if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
        {
            // Form compliant URI for child object
            SBOLObject* parent_obj = this->sbol_owner;
            std::string persistentIdentity;
            std::string version;
            
            SBOLClass dummy_obj = SBOLClass();  // This is unfortunately a necessary hack in order to infer what the compliant URI should be
            TopLevel* check_top_level = dynamic_cast<TopLevel*>(&dummy_obj);
            if (!check_top_level)
            {
                // Check to see if the parent object has a persistent identity
                if (parent_obj->properties.find(SBOL_PERSISTENT_IDENTITY) != parent_obj->properties.end())
                {
                    persistentIdentity = parent_obj->properties[SBOL_PERSISTENT_IDENTITY].front();
                    persistentIdentity = persistentIdentity.substr(1, persistentIdentity.length() - 2);  // Removes flanking < and > from the uri
                }
                if (parent_obj->properties.find(SBOL_VERSION) != parent_obj->properties.end())
                {
                    version = parent_obj->properties[SBOL_VERSION].front();
                    version = version.substr(1, version.length() - 2);  // Removes flanking " from the uri
                }
                else
                {
                    version = VERSION_STRING;
                }
                std::string compliant_uri = persistentIdentity + "/" + uri + "/" + version;
                for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
                {
                    SBOLObject* obj = *i_obj;
                    if (compliant_uri.compare(obj->identity.get()) == 0)
                    {
                        return (SBOLClass&)*obj;
                    }
                }
                throw SBOLError(NOT_FOUND_ERROR, "Object " + compliant_uri + " not found");
            }
            // The parent object is TopLevel
            else if (Config::getOption("sbol_typed_uris").compare("True") == 0)
            {

                persistentIdentity = getHomespace() + "/" + parseClassName(dummy_obj.getTypeURI());

            }
            else
            {
                persistentIdentity = getHomespace();
            }

            // Find latest version if they are using a different semantic versioning scheme
            // This needs some work
            std::vector< SBOLClass* > persistent_id_matches;
            for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
            {
                SBOLObject* obj = *i_obj;
                size_t found;
                found = obj->identity.get().find(persistentIdentity + "/" + uri);
                if (found != std::string::npos)
                {
                    persistent_id_matches.push_back((SBOLClass*)obj);
                }
                sort(persistent_id_matches.begin(), persistent_id_matches.end(), [](SBOLClass* a, SBOLClass* b) {
                    return (a->version.get() < b->version.get());
                });
            }
            if (persistent_id_matches.size() > 0)
                return (SBOLClass&)*persistent_id_matches.back();
            throw SBOLError(NOT_FOUND_ERROR, "Object " + persistentIdentity + "/" + uri + " not found");
        }
        throw SBOLError(NOT_FOUND_ERROR, "Object " + uri + " not found");
    };

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
    
    class OwnedPythonObject : public OwnedObject<PyObject>
    {
    private:
        PyObject* constructor_for_owned_object;
        
        PyObject* getSwigProxy(SBOLObject* sbol_obj)
        {
            typedef struct {
                PyObject_HEAD
                void *ptr; // This is the pointer to the actual C++ instance
                void *ty;  // swig_type_info originally, but shouldn't matter
                int own;
                PyObject *next;
            } SwigPyObject;
            
            for (auto & i_py_obj : this->sbol_owner->PythonObjects)
            {
                PyObject* py_obj = i_py_obj.second;
                // Instantiate Python extension objects
                SwigPyObject* swig_py_object = (SwigPyObject*)PyObject_GetAttr(py_obj,  PyUnicode_FromString("this"));
                if (swig_py_object->ptr == sbol_obj)
                    return py_obj;
            }
            return NULL;
        };
        
        SBOLObject* getSwigClient(PyObject* py_obj)
        {
            if (py_obj == NULL)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid PyObject passed to getSwigClient");

            typedef struct {
                PyObject_HEAD
                void *ptr; // This is the pointer to the actual C++ instance
                void *ty;  // swig_type_info originally, but shouldn't matter
                int own;
                PyObject *next;
            } SwigPyObject;
            
            // Instantiate Python extension objects
            SBOLObject* sbol_obj = NULL;
            try
            {
                SwigPyObject* swig_py_object = (SwigPyObject*)PyObject_GetAttr(py_obj,  PyUnicode_FromString("this"));
                sbol_obj = (SBOLObject *)swig_py_object->ptr;
            } catch (...)
            {
            }
            if (sbol_obj == NULL)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Attempted to access SWIG client object but none was found. Is the object subclassed from an SBOL core class?");
            return sbol_obj;
        };
        
    public:
        OwnedPythonObject(PyObject* constructor, sbol_type type_uri = UNDEFINED, SBOLObject *property_owner = NULL) :
            OwnedObject<PyObject>(type_uri, property_owner),
            constructor_for_owned_object(constructor)
        {
            // Register Property in owner Object
            if (this->sbol_owner != NULL)
            {
                std::vector<sbol::SBOLObject*> object_store;
                this->sbol_owner->owned_objects.insert({ type_uri, object_store });
            }
            else
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "The third argument to an OwnedPythonObject constructor must be a pointer to the property's parent object, ie, self.this");
        };
        
        void set(PyObject* py_obj)
        {
            /// @TODO This could cause a memory leak if the overwritten object is not freed!
            SBOLObject* sbol_obj = getSwigClient(py_obj);
            sbol_obj->parent = this->sbol_owner;
            this->sbol_owner->owned_objects[this->type][0] = sbol_obj;
            this->sbol_owner->PythonObjects[sbol_obj->identity.get()] = py_obj;
        };
        
        void add(PyObject* py_obj)
        {
            SBOLObject* sbol_obj = getSwigClient(py_obj);

//            if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
//                throw SBOLError(SBOL_ERROR_COMPLIANCE, "Cannot add " + sbol_obj->identity.get() + " to " + this->sbol_owner->identity.get() + ". The " + parseClassName(this->sbol_owner->type) + "::" + parseClassName(this->type) + "::add method is prohibited while operating in SBOL-compliant mode and is only available when operating in open-world mode. Use the " + parseClassName(this->sbol_owner->type) + "::" + parseClassName(this->type) + "::create method instead or use toggleSBOLCompliance to enter open-world mode");
            if (this->sbol_owner)
            {
                if (this->sbol_owner->type.compare(SBOL_DOCUMENT) == 0)
                {
                    Document& doc = (Document &)*this->sbol_owner;
                    doc.SBOLObjects[sbol_obj->identity.get()] = sbol_obj;
                }
                else
                {
                    std::vector< sbol::SBOLObject* >& object_store = this->sbol_owner->owned_objects[this->type];
                    if (std::find(object_store.begin(), object_store.end(), sbol_obj) != object_store.end())
                        throw SBOLError(DUPLICATE_URI_ERROR, "The object " + sbol_obj->identity.get() + " is already contained by the property");
                    else
                    {
                        sbol_obj->parent = this->sbol_owner;  // Set back-pointer to parent object
                        object_store.push_back(sbol_obj);
                        if (this->sbol_owner->doc)
                        {
                            sbol_obj->doc = this->sbol_owner->doc;
                        }
                    }
                }
                this->sbol_owner->PythonObjects[sbol_obj->identity.get()] = py_obj;
            }
        };
        
        PyObject* get(const std::string uri)
        {
            // By default, get the first object in the object store...
            if (uri.compare("") == 0)
            {
                // Check if this property is empty
                if (this->sbol_owner->owned_objects[this->type].size() == 0)
                    return NULL;

                SBOLObject* obj = this->sbol_owner->owned_objects[this->type][0];
                return getSwigProxy(obj);
            }
            // ...else search the object store for an object matching the id
            else
            {
                return this->operator[](uri);
                
            }
        };
        
        PyObject* operator[] (std::string uri)
        {
            // Search this property's object store for the uri
            std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
            for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
            {
                SBOLObject* obj = *i_obj;
                if (uri.compare(obj->identity.get()) == 0)
                {
                    return getSwigProxy(obj);
                }
            }
            // In SBOLCompliant mode, the user may retrieve an object by displayId as well
            if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
            {
                // Form compliant URI for child object
                SBOLObject* parent_obj = this->sbol_owner;
                std::string persistentIdentity;
                std::string version;
                
                //if (!check_top_level)
                // If not a TopLevel object...
                if (parent_obj->type.compare(SBOL_DOCUMENT) != 0)
                {
                    persistentIdentity = parent_obj->properties[SBOL_PERSISTENT_IDENTITY].front();
                    persistentIdentity = persistentIdentity.substr(1, persistentIdentity.length() - 2);  // Removes flanking < and > from the uri
                }
                // If the parent object doesn't have a persistent identity then it is TopLevel
                else if (Config::getOption("sbol_typed_uris").compare("True") == 0)
                {
                    
                    persistentIdentity = getHomespace() + "/" + parseClassName(this->sbol_owner->type);
                    
                }
                else
                {
                    persistentIdentity = getHomespace();
                }
                if (parent_obj->properties.find(SBOL_VERSION) != parent_obj->properties.end())
                {
                    version = parent_obj->properties[SBOL_VERSION].front();
                    version = version.substr(1, version.length() - 2);  // Removes flanking " from the uri
                }
                else
                {
                    version = VERSION_STRING;
                }
                std::string compliant_uri = persistentIdentity + "/" + uri + "/" + version;
                // Search this property's object store for the uri
                for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
                {
                    SBOLObject* obj = *i_obj;
                    if (compliant_uri.compare(obj->identity.get()) == 0)
                    {
                        return getSwigProxy(obj);
                    }
                }
                throw SBOLError(NOT_FOUND_ERROR, "Object " + compliant_uri + " not found");
                
            }
            throw SBOLError(NOT_FOUND_ERROR, "Object " + uri + " not found");
        };
        
        PyObject* create(std::string uri)
        {
            // This is a roundabout way of checking if SBOLClass is TopLevel in the Document
            int CHECK_TOP_LEVEL;
            Document* parent_doc = dynamic_cast<Document*>(this->sbol_owner);
            if (parent_doc)
                CHECK_TOP_LEVEL = 1;
            else
            {
                CHECK_TOP_LEVEL = 0;
                parent_doc = this->sbol_owner->doc;
            }
            SBOLObject* parent_obj = this->sbol_owner;
            
            if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
            {
                PyObject* py_obj = PyObject_CallFunction(this->constructor_for_owned_object, (char *)"s", uri.c_str());
                Identified* child_obj = (Identified *)getSwigClient(py_obj);
                
                // Form compliant URI for child object
                std::string persistent_id;
                std::string version;
                if (!CHECK_TOP_LEVEL && parent_obj->properties.find(SBOL_PERSISTENT_IDENTITY) != parent_obj->properties.end())
                {
                    persistent_id = parent_obj->properties[SBOL_PERSISTENT_IDENTITY].front();
                    persistent_id = persistent_id.substr(1, persistent_id.length() - 2);  // Removes flanking < and > from the uri
                }
                else
                {
                    // If object is TopLevel, intialize the URI
                    persistent_id = getHomespace();
                    if (Config::getOption("sbol_typed_uris").compare("True") == 0)
                        persistent_id += "/" + parseClassName(child_obj->getTypeURI());
                }
                if (parent_obj->properties.find(SBOL_VERSION) != parent_obj->properties.end())
                {
                    version = parent_obj->properties[SBOL_VERSION].front();
                    version = version.substr(1, version.length() - 2);  // Removes flanking " from the uri
                }
                else
                {
                    version = VERSION_STRING;
                }
                std::string child_persistent_id =  persistent_id + "/" + uri;
                std::string child_id = child_persistent_id + "/" + version;
                
                // Check for uniqueness of URI in the Document
                if (parent_doc && parent_doc->find(child_id))
                    throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + child_id + " is already in the Document");
                
                // Construct a new child object
                //            SBOLClass* child_obj = new SBOLClass(uri);
                
                
                // Initialize SBOLCompliant properties
                child_obj->identity.set(child_id);
                child_obj->persistentIdentity.set(child_persistent_id);
                child_obj->displayId.set(uri);
                child_obj->version.set(version);
                
                // Add the new object to this OwnedObject property
                // this->add(*child_obj);   Can't use this because the add method is prohibited in SBOLCompliant mode!!!
                child_obj->parent = parent_obj;  // Set back-pointer to parent object
                std::vector< sbol::SBOLObject* >& object_store = this->sbol_owner->owned_objects[this->type];
                object_store.push_back((SBOLObject*)child_obj);
                
                // The following effectively adds the child object to the Document by setting its back-pointer.  However, the Document itself only maintains a register of TopLevel objects, otherwise the returned object will not be registered
                if (parent_doc)
                    child_obj->doc = parent_doc;
                if (CHECK_TOP_LEVEL)
                    parent_doc->SBOLObjects[child_id] = (SBOLObject*)child_obj;
                return py_obj;
            }
            else
            {
                if (parent_doc && parent_doc->find(uri))
                    throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + uri + " is already in the Document");
                
                // Construct a new child object
                PyObject* py_obj = PyObject_CallObject(constructor_for_owned_object, NULL);
                Identified* child_obj = (Identified *)getSwigClient(py_obj);
                child_obj->identity.set(uri);
                
                Identified* parent_obj = (Identified*)this->sbol_owner;
                child_obj->parent = parent_obj;  // Set back-pointer to parent object
                child_obj->identity.set(uri);
                child_obj->persistentIdentity.set(uri);
                
                // Add to this property's object store
                std::vector< sbol::SBOLObject* >& object_store = this->sbol_owner->owned_objects[this->type];
                object_store.push_back((SBOLObject*)child_obj);
                
//                this->add(*child_obj);
                // Set pointer to Document
                if (parent_obj->doc)
                    child_obj->doc = parent_obj->doc;
                
                return py_obj;
            }
        }
    };
    
#endif
    
    
    template <class SBOLClass>
    void OwnedObject<SBOLClass>::remove(int index)
    {
        if (this->sbol_owner)
        {
            if (this->sbol_owner->owned_objects.find(this->type) != this->sbol_owner->owned_objects.end())
            {
                if (index >= this->sbol_owner->owned_objects[this->type].size())
                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Index out of range");
                SBOLObject* target = this->sbol_owner->owned_objects[this->type][ index ];
                this->remove(target->identity.get());
                //this->sbol_owner->owned_objects[this->type].erase( this->sbol_owner->owned_objects[this->type].begin() + index);
            }
        }
        throw std::runtime_error("This property is not defined in the parent object");

    };

    template <class SBOLClass>
    SBOLClass& OwnedObject<SBOLClass>::remove(std::string uri)
    {
        if (this->sbol_owner)
        {
            if (this->sbol_owner->owned_objects.find(this->type) != this->sbol_owner->owned_objects.end())
            {
                std::vector<SBOLObject*>& object_store = this->sbol_owner->owned_objects[this->type];
                int i_obj = 0;
                for (; i_obj < object_store.size(); ++i_obj)
                {
                    SBOLObject* obj = object_store[i_obj];
                    if (uri.compare(obj->identity.get()) == 0)
                    {
                        this->sbol_owner->owned_objects[this->type].erase( this->sbol_owner->owned_objects[this->type].begin() + i_obj);
                        //this->remove(i_obj);
                        TopLevel* check_top_level = dynamic_cast<TopLevel*>(obj);
                        if (check_top_level)
                            obj->doc->SBOLObjects.erase(uri);
                        SBOLClass* cast_obj = dynamic_cast<SBOLClass*>(cast_obj);
                        return *cast_obj;
                    }
                }
                
            }
        }
        throw std::runtime_error("This property is not defined in the parent object");

    };
    
//    template <class SBOLClass>
//    void OwnedObject<SBOLClass>::remove(std::string uri)
//    {
//        if (this->sbol_owner)
//        {
//            if (this->sbol_owner->owned_objects.find(this->type) != this->sbol_owner->owned_objects.end())
//            {
//                std::vector<SBOLObject*>& object_store = this->sbol_owner->owned_objects[this->type];
//                int i_obj = 0;
//                for (; i_obj < object_store.size(); ++i_obj)
//                {
//                    SBOLObject& obj = *object_store[i_obj];
//                    if (uri.compare(obj.identity.get()) == 0)
//                    {
//                        this->sbol_owner->owned_objects[this->type].erase( this->sbol_owner->owned_objects[this->type].begin() + i_obj);
//                        //this->remove(i_obj);
//                        TopLevel* check_top_level = dynamic_cast<TopLevel*>(&obj);
//                        if (check_top_level)
//                            obj.doc->SBOLObjects.erase(uri);
//                        break;
//                    }
//                }
//            }
//        }
//    };
    
    template <class SBOLClass>
    void OwnedObject<SBOLClass>::clear()
    {
        if (this->sbol_owner)
        {
            if (this->sbol_owner->owned_objects.find(this->type) != this->sbol_owner->owned_objects.end())
            {
                std::vector<SBOLObject*>& object_store = this->sbol_owner->owned_objects[this->type];
                for (auto i_obj = object_store.begin(); i_obj != object_store.end(); ++i_obj)
                {
                    SBOLObject* obj = *i_obj;
                    obj->close();
                }
                object_store.clear();
            }
        }
    };
    
    template <class SBOLClass>
    SBOLClass& TopLevel::copy(Document* target_doc, std::string ns, std::string version)
    {
        // Register in Document, either this one or the new one
        //Document& parent_doc = *this->doc;
        // register in SBOLObjects
        // register in owned_objects
        if (!target_doc)
            target_doc = this->doc;
        Identified& obj_copy = Identified::copy(target_doc, ns, version);
        SBOLClass& new_obj = (SBOLClass&)obj_copy;
        if (target_doc)
            target_doc->add < SBOLClass > (new_obj);
        return new_obj;
    };

    template <class SBOLClass>
    SBOLClass& TopLevel::simpleCopy(std::string uri)
    {
        Identified& obj_copy = Identified::simpleCopy(uri);
        SBOLClass& new_obj = (SBOLClass&)obj_copy;
        if (doc)
            doc->add < SBOLClass > (new_obj);
        return new_obj;
    };

    
    template < class ExtensionClass >
    void SBOLObject::register_extension_class(std::string ns, std::string ns_prefix, std::string class_name)
    {
        std::string uri = ns + class_name;
        SBOL_DATA_MODEL_REGISTER.insert(make_pair(uri, (SBOLObject&(*)())&create<ExtensionClass>));
        namespaces[ns_prefix] = ns;  // Register extension namespace
    };
}



#endif
