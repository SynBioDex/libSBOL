#include "sbol.h"

#include <string>

#ifndef HOST_INCLUDED
#define HOST_INCLUDED

#define EXTENSION_PREFIX "host_context"
#define EXTENSION_NS "sys-bio.org/HostContext#"
#define EXTENSION_CLASS "Host"

namespace sbol
{
    class Host : public ModuleDefinition, public ComponentDefinition
    {
        
    public:
        List < ReferencedObject < ModuleDefinition > > modules;
        ReferencedObject < Host > parents;
        ReferencedObject < Host > children;
        IntProperty generation;
        URIProperty medium;
        TextProperty vendorId;
        
        // This public constructor is exposed to the user.  By convention all constructors take the object's identity (URI) as the first argument
        
        Host(std::string uri = EXTENSION_NS "example") : Host(EXTENSION_NS EXTENSION_CLASS, uri) {};
        ~Host() {};  // Destructor
   
    protected:
        // This protected constructor is a delegate constructor that directly controls the appearance of RDF/XML tags in serialized SBOL.  These initialize the object with the sbol_type "sys-bio.org/HostContext/Host".  The object appears in an SBOL file as an XML element called Host in the sys-bio.org/HostContext namespace
        Host(sbol_type type, std::string uri) :
           ModuleDefinition(type, uri),
           modules(EXTENSION_NS "modules", this),
           parents(EXTENSION_NS "parents", this),
           children(EXTENSION_NS "children", this),
           generation(EXTENSION_NS "generation", this, 1),
           medium(EXTENSION_NS "medium", this, "www.ebi.ac.uk/efo/EFO_0000579"),
           vendorId(EXTENSION_NS "vendorId", this, "sigmaaldrich.com/L2542")
        {
           register_extension < Host > (EXTENSION_PREFIX, EXTENSION_NS EXTENSION_CLASS);
        };
    };
}

#endif
