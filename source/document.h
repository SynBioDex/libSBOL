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
	class Document {
	private:
		raptor_world *rdf_graph;  ///< Triple store that holds SBOL objects and properties
        std::unordered_map<std::string, std::string> namespaces;
        ValidationRules validationRules;  ///< A list of validation functions to run on the Document prior to serialization

	public:
        /// Construct a Document.  The Document is a container for Components, Modules, and all other SBOLObjects
		Document() :
			rdf_graph(raptor_new_world()),
            validationRules({ sbolRule10101, sbolRule10102 })
			{
			};
        
        /// The Document's register of objects
		std::unordered_map<std::string, sbol::TopLevel*> SBOLObjects;
        
        /// @cond
		std::unordered_map<std::string, sbol::TopLevel*> componentDefinitions;
		std::unordered_map<std::string, sbol::TopLevel*> models;
		std::unordered_map<std::string, sbol::TopLevel*> moduleDefinitions;
		std::unordered_map<std::string, sbol::TopLevel*> sequences;
        /// @endcond

		TopLevel& getTopLevel(std::string);
		raptor_world* getWorld();
        /// Register an object in the Document
        /// @param sbol_obj The SBOL object you want to serialize
        /// @tparam SBOLClass The type of SBOL object
		template < class SBOLClass > void add(SBOLClass& sbol_obj);
        
        /// Retrieve an object from the Document
        /// @param uri The identity of the SBOL object you want to retrieve
        /// @tparam SBOLClass The type of SBOL object
        template < class SBOLClass > SBOLClass& get(std::string uri);

        /// Serialize to an RDF/XML file
        /// @param filename The full name of the file you want to write (including file extension)
        void write(std::string filename);

        /// Serialize to an RDF/XML file
        /// @param filename The full name of the file you want to write (including file extension)
        void read(std::string filename);

        /// Run validation rules on this Document
        void validate(void *arg = NULL);

        static void parse_objects(void* user_data, raptor_statement* triple);
		static void parse_properties(void* user_data, raptor_statement* triple);
        
        
        static void namespaceHandler(void *user_data, raptor_namespace *nspace);
        std::vector<std::string> getNamespaces();

		std::vector<SBOLObject*> flatten();
        void addNameSpace(std::string ns, std::string prefix, raptor_serializer* sbol_serializer);
        void addNameSpace(std::string ns, std::string prefix);
	};

	template <class SBOLClass > void Document::add(SBOLClass& sbol_obj)
	{
		// Check if the uri is already assigned and delete the object, otherwise it will cause a memory leak!!!
		//if (SBOLObjects[whatever]!=SBOLObjects.end()) {delete SBOLObjects[whatever]'}
        std::cout << "Adding " << sbol_obj.identity.get() << std::endl;
		SBOLObjects[sbol_obj.identity.get()] = (TopLevel*)&sbol_obj;
		sbol_obj.doc = this;
	};

	template <class SBOLClass > SBOLClass& Document::get(std::string uri)
	{
		return (SBOLClass &)*(this->SBOLObjects[uri]);
	};
    
    
	std::string cut_sbol_resource(std::string& xml_string, const std::string resource_id);
	void replace_reference_to_resource(std::string& xml_string, const std::string resource_id, std::string& replacement_text);
	void seek_element(std::istringstream& xml_buffer, std::string uri);
	void seek_next_element(std::istringstream& xml_buffer);
	void seek_new_line(std::istringstream& xml_buffer);
	void seek_end_of_line(std::istringstream& xml_buffer);
	void seek_end_of_element(std::istringstream& xml_buffer);
	void seek_end_of_node(std::istringstream& xml_buffer, std::string uri);
	void seek_resource(std::istringstream& xml_buffer, std::string uri);
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
    
}

#endif