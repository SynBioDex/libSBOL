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
    
    
    protected:
        //protected:
        //	sbol_type type;
    
    public:
        Document *doc = NULL;
    
        //std::unordered_map<sbol::sbol_type, sbol::PropertyBase> properties;
        std::map<sbol::sbol_type, std::vector< std::string > > properties;
        std::map<sbol::sbol_type, std::vector< std::string > > list_properties;
        std::map<sbol::sbol_type, std::vector< sbol::SBOLObject* > > owned_objects;
    
        SBOLObject(sbol_type type = UNDEFINED, std::string uri_prefix = SBOL_URI, std::string id = "example") :
            type(type),
            identity(URIProperty(SBOL_IDENTITY, this, uri_prefix + "/" + id))
        {
        };
        ~SBOLObject();
        sbol_type type;
        URIProperty identity;
    
        virtual sbol_type getTypeURI();
        void serialize(raptor_serializer* sbol_serializer, raptor_world *sbol_world = NULL);
        std::string nest(std::string& rdfxml_buffer);
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
