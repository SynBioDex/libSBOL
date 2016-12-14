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

namespace sbol
{
    
    
    /* All SBOLObjects have a pointer back to their Document.  This requires forward declaration of SBOL Document class here */
    class Document;
    
    /// An SBOLObject converts a C++ class data structure into an RDF triple store and contains methods for serializing and parsing RDF triples
    class SBOLObject
    {
        friend class Document;
        
        template < class LiteralType >
        friend class Property;
        
    protected:
        std::unordered_map<std::string, std::string> namespaces;
        void serialize(raptor_serializer* sbol_serializer, raptor_world *sbol_world = NULL);  // Convert an SBOL object into RDF triples
        std::string nest(std::string& rdfxml_buffer);  // Pretty-writer that converts flat RDF/XML into nested RDF/XML (ie, SBOL)
        
        /// Register an extension class and its namespace, so custom data can be embedded into and read from SBOL files
        /// @tparam ExtensionClass The new class
        /// @param ns The extension namespace, eg, http://myhome.org/my_extension#. It's important that the namespace ends in a forward-slash or hash
        /// @param ns_prefix A shorthand symbol for the full namespace as it will appear in the output file, eg, my_extension
        template < class ExtensionClass > void register_extension_class(std::string ns, std::string ns_prefix, std::string class_name);

    public:
        Document *doc = NULL;
    
        std::map<sbol::sbol_type, std::vector< std::string > > properties;
        std::map<sbol::sbol_type, std::vector< std::string > > list_properties;
        std::map<sbol::sbol_type, std::vector< sbol::SBOLObject* > > owned_objects;
    
        // Open-world constructor
        SBOLObject(std::string uri = DEFAULT_NS "/SBOLObject/example") : SBOLObject(UNDEFINED, uri) {};

        // Conforms to SBOL compliant URIs
        SBOLObject(std::string uri_prefix, std::string display_id, std::string version) : SBOLObject(UNDEFINED, uri_prefix, display_id, version) {};
        
        virtual ~SBOLObject();

        sbol_type type;
        SBOLObject* parent;
        URIProperty identity;
    
        virtual sbol_type getTypeURI();
        std::string getClassName(std::string type);

        
        /// Search this object recursively to see if an object with the URI already exists.
        /// @param uri The URI to search for.
        /// @return 1 if an object with this URI exists, 0 if it doesn't
        int find(std::string uri);
        
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
        
        /// Use this method to destroy an SBOL object that is not contained by a parent Document.  If the object does have a parent Document, instead use doc.close() with the object's URI identity as an argument.
        /// @TODO Recurse through child objects and delete them.
        void close();
        
    protected:
        // Open-world constructor
        SBOLObject(sbol_type type, std::string uri) :
            type(type),
            namespaces({}),
            identity(SBOL_IDENTITY, this, uri, { sbol_rule_10202 })
        {
            if (hasHomespace())
                identity.set(getHomespace() + "/" + uri);
        };

        // Conforms to SBOL compliant URIs
        SBOLObject(sbol_type type, std::string uri_prefix, std::string display_id, std::string version) :
            type(type),
            namespaces({}),
            identity(SBOL_IDENTITY, this, uri_prefix + "/" + getClassName(type) + "/" + display_id + "/" + version)
        {
        };
    };

    template <class LiteralType>
    void Property<LiteralType>::initializeNamespace(std::string ns)
    {
        
    };

    
    /// @ingroup extension_layer
    /// @brief A reference to another SBOL object
    /// Contains a Uniform Resource Identifier (URI) that refers to an an associated object.  The object it points to may be another resource in this Document or an external reference, for example to an object in an external repository.  In the SBOL specification, association by reference is indicated in class diagrams by arrows with open (white) diamonds.
    class ReferencedObject : public URIProperty
    {
    protected:
        sbol_type reference_type_uri;
    public:
        ReferencedObject(sbol_type type_uri, sbol_type reference_type_uri, SBOLObject *property_owner, std::string initial_value = "");
        std::string create(std::string uri);

        //void add(SBOLClass& sbol_obj);
        void set(std::string uri);

        //void set(SBOLClass& sbol_obj);
        //SBOLClass& get(std::string object_id);
        std::string operator[] (const int nIndex);
        void addReference(const std::string uri);
        void setReference(const std::string uri);

        
        /// Provides iterator functionality for SBOL properties that contain multiple references
        class iterator : public std::vector<std::string>::iterator
        {
        public:
            iterator( std::vector<std::string>::iterator i_str = std::vector<std::string>::iterator()) : std::vector<std::string>::iterator(i_str)
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
            std::size_t size = this->sbol_owner->owned_objects[this->type].size();
            return (int)size;
        };
        
        std::vector<std::string>::iterator python_iter;
    };

    template <class PropertyType>
    void List<PropertyType>::remove(std::string uri)
    {
        if (this->sbol_owner)
        {
            if (this->sbol_owner->owned_objects.find(this->type) != this->sbol_owner->owned_objects.end())
            {
                std::vector<SBOLObject*>& object_store = this->sbol_owner->owned_objects[this->type];
                int i_obj = 0;
                for (; i_obj <= object_store.size(); ++i_obj)
                {
                    SBOLObject& obj = *object_store[i_obj];
                    if (uri.compare(obj.identity.get()) == 0)
                        break;
                }
                if (i_obj < object_store.size())
                    this->remove(i_obj);
            }
        }
    };

}

//// This is a wrapper function for constructors.  This allows us to construct an SBOL object using a function pointer (direct pointers to constructors are not supported by C++)
//template <class SBOLClass>
//sbol::SBOLObject& create()
//{
//    // Construct an SBOLObject with emplacement
//    void* mem = malloc(sizeof(SBOLClass));
//    SBOLClass* a = new (mem) SBOLClass;
//    return (sbol::SBOLObject&)*a;
//};



#endif /* OBJECT_INCLUDED */
