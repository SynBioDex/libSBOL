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
    
    class SBOLObject
    {
    friend class Document;
    
    public:
        Document *doc = NULL;
    
        //std::unordered_map<sbol::sbol_type, sbol::PropertyBase> properties;
        std::map<sbol::sbol_type, std::vector< std::string > > properties;
        std::map<sbol::sbol_type, std::vector< std::string > > list_properties;
        std::map<sbol::sbol_type, std::vector< sbol::SBOLObject* > > owned_objects;
    
        // Open-world constructor
        SBOLObject(std::string uri = DEFAULT_NS "/SBOLObject/example") : SBOLObject(UNDEFINED, uri) {};

        // Conforms to SBOL compliant URIs
        SBOLObject(std::string uri_prefix, std::string display_id, std::string version) : SBOLObject(UNDEFINED, uri_prefix, display_id, version) {};
        
        ~SBOLObject();
        sbol_type type;
        URIProperty identity;
    
        virtual sbol_type getTypeURI();
        void serialize(raptor_serializer* sbol_serializer, raptor_world *sbol_world = NULL);
        std::string nest(std::string& rdfxml_buffer);
        std::string getClassName(std::string type);

    protected:
        // Open-world constructor
        SBOLObject(sbol_type type, std::string uri) :
            type(type),
            identity(SBOL_IDENTITY, this, uri)
        {
        };

        // Conforms to SBOL compliant URIs
        SBOLObject(sbol_type type, std::string uri_prefix, std::string display_id, std::string version) :
            type(type),
        identity(SBOL_IDENTITY, this, uri_prefix + "/" + getClassName(type) + "/" + display_id + "/" + version)
        {
        };
    };
    
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
        SBOLError(NOT_FOUND_ERROR, "Object not found");
        SBOLClass& dummy = * new SBOLClass();  // Dummy object necessary to suppress warning
        return dummy;
    };
    
    template <class SBOLClass>
    SBOLClass& OwnedObject<SBOLClass>::operator[] (const std::string uri)
    {
        std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
        for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
        {
            SBOLObject* obj = *i_obj;
            if (uri.compare(obj->identity.get()) == 0)
            {
                return (SBOLClass&)*obj;
            }
        }
        SBOLError(NOT_FOUND_ERROR, "Object not found");
        SBOLClass& dummy = * new SBOLClass();  // Dummy object necessary to suppress warning
        return dummy;
    };

    
    class ReferencedObject : public URIProperty
    {
    protected:
        sbol_type reference_type;
    public:
        ReferencedObject(sbol_type type_uri, sbol_type reference_type_uri, SBOLObject *property_owner, std::string initial_value);
        ReferencedObject(sbol_type type_uri = UNDEFINED, SBOLObject *property_owner = NULL, std::string initial_value = "");  // All sbol:::Properties (and therefore OwnedObjects which are derived from Properties) must match this signature in order to put them inside an sbol:List<> container.  In this case, the third argument is just a dummy variable
        //ReferencedObject(sbol_type type_uri, void *property_owner, SBOLObject& first_object);
        
        //void add(SBOLClass& sbol_obj);
        void set(std::string uri);
        //void set(SBOLClass& sbol_obj);
        //SBOLClass& get(std::string object_id);
        std::string operator[] (const int nIndex);
        void addReference(const std::string uri);
        //void addReference(const std::string uri_prefix, const std::string display_id);
        //void addReference(const std::string uri_prefix, const std::string display_id, const std::string version);
        void setReference(const std::string uri);
        //void setReference(const std::string uri_prefix, const std::string display_id);
        //void setReference(const std::string uri_prefix, const std::string display_id, const std::string version);

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
