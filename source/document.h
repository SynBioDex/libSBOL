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

#include <raptor2.h>
#include <unordered_map>
#include <istream>
#include <algorithm>

namespace sbol {
    
    // This is the global SBOL register for classes.  It maps an SBOL RDF type (eg, "http://sbolstandard.org/v2#Sequence" to a constructor
    extern std::unordered_map<std::string, sbol::SBOLObject&(*)()> SBOL_DATA_MODEL_REGISTER;
    
    // This is a wrapper function for constructors.  This allows us to construct an SBOL object using a function pointer (direct pointers to constructors are not supported by C++)
    template <class SBOLClass>
    sbol::SBOLObject& create()
    {
        // Construct an SBOLObject with emplacement
        void* mem = malloc(sizeof(SBOLClass));
        SBOLClass* a = new (mem) SBOLClass;
        return (sbol::SBOLObject&)*a;
    };

    
    template <class SBOLClass>
    void register_extension(std::string ns_prefix, std::string uri)
	{
		SBOL_DATA_MODEL_REGISTER.insert(make_pair(uri, (SBOLObject&(*)())&create<SBOLClass>));
        // TODO: register ns_prefix in SBOLObject
	};

    void raptor_error_handler(void *user_data, raptor_log_message* message);
	
    /// Read and write SBOL using a Document class.  The Document is a container for Components, Modules, and all other SBOLObjects
    class Document : public SBOLObject
    {
	private:
        std::string home; ///< The authoritative namespace for the Document. Setting the home namespace is like signing a piece of paper.
        int SBOLCompliant; ///< Flag indicating whether to autoconstruct URI's consistent with SBOL's versioning scheme
        std::unordered_map<std::string, std::string> namespaces;  ///< A namespace prefix serves as the hash key for the full namespace URI
        ValidationRules validationRules;  ///< A list of validation functions to run on the Document prior to serialization
        raptor_world *rdf_graph;  ///< RDF triple store that holds SBOL objects and properties

	public:
        /// Construct a Document.  The Document is a container for Components, Modules, and all other SBOLObjects
		Document() :
            SBOLObject("Document", ""),
            home(""),
            SBOLCompliant(0),
            namespaces({}),
			rdf_graph(raptor_new_world()),
            validationRules({ sbolRule10101, sbolRule10102 }),
            componentDefinitions(SBOL_COMPONENT_DEFINITION, this, ""),
            moduleDefinitions(SBOL_MODULE_DEFINITION, this, ""),
            models(SBOL_MODEL, this, ""),
            sequences(SBOL_SEQUENCE, this, ""),
            sequenceAnnotations(SBOL_SEQUENCE_ANNOTATION, this, "")
			{
			};
        
        /// The Document's register of objects
		std::unordered_map<std::string, sbol::SBOLObject*> SBOLObjects;
        
//		std::unordered_map<std::string, sbol::TopLevel*> componentDefinitions;
//		std::unordered_map<std::string, sbol::TopLevel*> models;
//		std::unordered_map<std::string, sbol::TopLevel*> moduleDefinitions;
//		std::unordered_map<std::string, sbol::TopLevel*> sequences;

        /// @cond
        List<OwnedObject<ComponentDefinition>> componentDefinitions;
        List<OwnedObject<ModuleDefinition>> moduleDefinitions;
        List<OwnedObject<Model>> models;
        List<OwnedObject<Sequence>> sequences;
        List<OwnedObject<SequenceAnnotation>> sequenceAnnotations;
        /// @endcond

        
		TopLevel& getTopLevel(std::string);
		raptor_world* getWorld();
        
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
        void write(std::string filename);

        /// Read an RDF/XML file and attach the SBOL objects to this Document. Existing contents of the Document will be wiped.
        /// @param filename The full name of the file you want to read (including file extension)
        void read(std::string filename);

        /// Read an RDF/XML file and attach the SBOL objects to this Document. New objects will be added to the existing contents of the Document
        /// @param filename The full name of the file you want to read (including file extension)
        void append(std::string filename);
        
        /// Run validation rules on this Document.  Validation rules are called automatically during parsing and serialization.
        void validate(void *arg = NULL);

        int find(std::string uri);

        static void parse_objects(void* user_data, raptor_statement* triple);
		static void parse_properties(void* user_data, raptor_statement* triple);
        static void namespaceHandler(void *user_data, raptor_namespace *nspace);

        std::vector<std::string> getNamespaces();
        void addNamespace(std::string ns, std::string prefix, raptor_serializer* sbol_serializer);
        void addNamespace(std::string ns, std::string prefix);
        
		std::vector<SBOLObject*> flatten();
        /// Delete all objects in this Document and destroy the Document
        void close(std::string uri = "");
        
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
            throw SBOLError(DUPLICATE_URI_ERROR, "The object " + sbol_obj.identity.get() + " is already contained in the Document");
        else
        {
            // If TopLevel add the Document
            TopLevel* check_top_level = dynamic_cast<TopLevel*>(&sbol_obj);
            if (check_top_level)
            {
                SBOLObjects[sbol_obj.identity.get()] = (SBOLObject*)&sbol_obj;
                this->owned_objects[sbol_obj.type].push_back((SBOLClass*)&sbol_obj);  // Add the object to the Document's property store, eg, componentDefinitions, moduleDefinitions, etc.
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
		return (SBOLClass &)*(this->SBOLObjects[uri]);
	};
    
    
	std::string cut_sbol_resource(std::string& xml_string, const std::string resource_id);
    void replace_reference_to_resource(std::string& xml_string, const std::string property_name, const std::string resource_id, std::string& replacement_text);
	void seek_element(std::istringstream& xml_buffer, std::string uri);
    void seek_property_element(std::istringstream& xml_buffer, std::string property_name);
	void seek_next_element(std::istringstream& xml_buffer);
	void seek_new_line(std::istringstream& xml_buffer);
	void seek_end_of_line(std::istringstream& xml_buffer);
	void seek_end_of_element(std::istringstream& xml_buffer);
	void seek_end_of_node(std::istringstream& xml_buffer, std::string uri);
    void seek_resource(std::istringstream& xml_buffer, std::string property_name, std::string uri);
	bool is_open_node(std::istringstream& xml_buffer);
	void indent(std::string& text, int indentation); 
	std::string get_qname(std::istringstream& xml_buffer);
	std::string get_local_part(std::string qname);
	std::string get_prefix(std::string qname);
	std::vector<std::string> parse_element(std::istringstream& xml_buffer);

    	template < class SBOLClass >
    	std::vector<SBOLClass*> OwnedObject<SBOLClass>::copy()
    	{
    		std::vector<SBOLClass*> vector_copy;
    		for (auto o = this->sbol_owner->owned_objects[this->type].begin(); o != this->sbol_owner->owned_objects[this->type].end(); o++)
    		{
    			vector_copy.push_back((SBOLClass*)*o);
    		}
    		return vector_copy;
    	};
    
    /// @param If SBOLCompliance is enabled, this should be the displayId for the new child object.  If not enabled, this should be a full raw URI.
    /// @return A reference to the child object
    /// Autoconstructs a child object and attaches it to the parent object.  If SBOLCompliance is enabled, the child object's identity will be constructed using the supplied displayId argument.  Otherwise, the user should supply a full URI.
    /// @TODO check uniqueness of URI in Document
    template <class SBOLClass>
    SBOLClass& OwnedObject<SBOLClass>::create(std::string uri)
    {
        // This is a roundabout way of checking if SBOLClass is TopLevel in the Document
        int CHECK_TOP_LEVEL = 0;
        Document* parent_doc = dynamic_cast<Document*>(this->sbol_owner);
        if (!parent_doc)
        {
            parent_doc = this->sbol_owner->doc;
            CHECK_TOP_LEVEL = 1;
        }
        SBOLObject* parent_obj = this->sbol_owner;

        if (isSBOLCompliant())
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
                throw SBOLError(DUPLICATE_URI_ERROR, "An object with this URI is already in the Document");
            
            // Construct a new child object with emplacement
            void* mem = malloc(sizeof(SBOLClass));
            SBOLClass* child_obj = new (mem)SBOLClass;

            // Initialize SBOLCompliant properties
            child_obj->identity.set(child_id);
            child_obj->persistentIdentity.set(child_persistent_id);
            child_obj->displayId.set(uri);
            child_obj->version.set(version);

            // Add the new object to this OwnedObject property
            // this->add(*child_obj);   Can't use this because the add method is prohibited in SBOLCompliant mode!!!
            std::vector< sbol::SBOLObject* >& object_store = this->sbol_owner->owned_objects[this->type];
            //if (std::find(object_store.begin(), object_store.end(), child_obj) != object_store.end())
            //    throw SBOLError(DUPLICATE_URI_ERROR, "An object " + child_id + " with that identity is already contained by the property");
            object_store.push_back(child_obj);
            
            // The following effectively adds the child object to the Document by setting its back-pointer.  However, the Document itself only maintains a register of TopLevel objects, otherwise the returned object will not be registered
            if (parent_doc)
                child_obj->doc = parent_doc;
            if (CHECK_TOP_LEVEL)
                parent_doc->SBOLObjects[child_id] = (SBOLObject*)child_obj;
            return *child_obj;
        }
        else
        {
            if (parent_doc && parent_doc->find(uri))
                throw SBOLError(DUPLICATE_URI_ERROR, "An object with this URI is already in the Document");
            
            // Construct an SBOLObject with emplacement
            void* mem = malloc(sizeof(SBOLClass));
            SBOLClass* child_obj = new (mem)SBOLClass;
            Identified* parent_obj = (Identified*)this->sbol_owner;
            
            child_obj->identity.set(uri);
            child_obj->persistentIdentity.set(uri);
            
            this->add(*child_obj);
            if (parent_obj->doc)
                child_obj->doc = parent_obj->doc;
            return *child_obj;
        }
    };
    
    /// @param sbol_obj The child object
    template < class SBOLClass>
    void OwnedObject<SBOLClass>::add(SBOLClass& sbol_obj)
    {
        if (isSBOLCompliant())
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "This add method is prohibited while operating in SBOL-compliant mode and is only available when operating in open-world mode. Use the create method instead");
        if (this->sbol_owner)
        {
            // The type for Document is currently hard-coded. Should replace it with a preprocessor symbol
            if (this->sbol_owner->type.compare("Document") == 0)
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
                    object_store.push_back((SBOLObject *)&sbol_obj);
                    if (this->sbol_owner->doc)
                    {
                        sbol_obj.doc = this->sbol_owner->doc;
                    }
                }
            }
        }
    };
    
    /// @param object_id The URI of the child object
    /// @return A reference to the child object
    template <class SBOLClass>
    SBOLClass& OwnedObject<SBOLClass>::get(const std::string object_id)
    {
        std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
        for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
        {
            SBOLObject* obj = *i_obj;
            if (object_id.compare(obj->identity.get()) == 0)
            {
                return (SBOLClass&)*obj;
            }
        }
        throw SBOLError(NOT_FOUND_ERROR, "Object " + object_id + " not found");
    };
    
    /// @param uri The URI of the child object
    /// @return A reference to the child object
    template <class SBOLClass>
    SBOLClass& OwnedObject<SBOLClass>::operator[] (std::string uri)
    {
        // Search this property's object store for the uri
        std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
        for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
        {
            SBOLObject* obj = *i_obj;
            if (uri.compare(obj->identity.get()) == 0)
            {
                return (SBOLClass&)*obj;
            }
        }
        
        // In SBOLCompliant mode, the user may retrieve an object by displayId as well
        if (isSBOLCompliant())
        {
            // Form compliant URI for child object
            SBOLObject* parent_obj = this->sbol_owner;
            std::string persistentIdentity;
            std::string version;
            if (parent_obj->properties.find(SBOL_PERSISTENT_IDENTITY) != parent_obj->properties.end())
            {
                persistentIdentity = parent_obj->properties[SBOL_PERSISTENT_IDENTITY].front();
                persistentIdentity = persistentIdentity.substr(1, persistentIdentity.length() - 2);  // Removes flanking < and > from the uri
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
            uri = persistentIdentity + "/" + uri + "/" + version;

            // Search this property's object store for the uri
            for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
            {
                SBOLObject* obj = *i_obj;
                if (uri.compare(obj->identity.get()) == 0)
                {
                    return (SBOLClass&)*obj;
                }
            }
        }
        throw SBOLError(NOT_FOUND_ERROR, "Object " + uri + " not found");
    };
    
}

#endif
