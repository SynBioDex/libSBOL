#include "sbol.h"

#include <string>

#ifndef HOST_INCLUDED
#define HOST_INCLUDED

#define EXTENSION_NS "sys-bio.org/HostContext/"
#define EXTENSION_CLASS "Host"
#define 

namespace sbol
{
    class Host : public Module
    {
    public:
        List < ReferencedObject < Module > > parents;
        List < ReferencedObject < Module > > children;
        
        IntProperty generation;
        
        URIProperty medium;
        
        // The public constructor is exposed to the user.  By convention the first argument is the object's identity uri.  Followed by that are required properties as specified in the SBOL 2.0 specification.
        Host(std::string uri = EXTENSION_NS "example", std::string definition = "") : Host(EXTENSION_NS EXTENSION_CLASS, uri, definition) {};
        
        ~Host() {};  // Destructor
   
    protected:
        // This protected constructor is a delegate constructor that controls the appearance of RDF/XML tags in serialized SBOL.  These initialize the object with the sbol_type "sys-bio.org/HostContext/Host".  The object appears in an SBOL file as an XML element called Host in the sys-bio.org/HostContext namespace
        Host(sbol_type type, std::string uri, std::string definition) :
           Module(type, uri, definition),
           generation(EXTENSION_NS "generation", this, 1),
           medium(EXTENSION_NS "medium", this, "http://www.ebi.ac.uk/efo/EFO_0000579")
        {
        };
    };
}

#endif
