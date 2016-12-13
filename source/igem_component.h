#ifndef iGEMComponentDefinition_INCLUDED
#define iGEMComponentDefinition_INCLUDED

#include "sbol.h"
#include <string>

// These constants determine the appearance of nodes in the output file
#define EXTENSION_PREFIX "igem"           // Namespace prefix in XML output
#define EXTENSION_NS "http://igem.org#"   // Must end in a hash or forward-slash
#define EXTENSION_CLASS "iGEMCDef"        // Name of the class in XML output

namespace sbol
{
    /// @cond
    class iGEMComponentDefinition : public ComponentDefinition  // Derive an extension class
    {
        
    public:
        TextProperty partStatus;
        TextProperty experience;
        TextProperty notes;
        TextProperty created;
        TextProperty source;
        URIProperty category;
        URIProperty results;
        URIProperty status;
        
        // Define the constructor. Put required fields in the argument list. Each required field must have a default value specified, even if only an empty string.
        iGEMComponentDefinition(std::string uri = "", std::string partStatus = "Under construction") :
            ComponentDefinition(uri),                                 // Call public base class constructor
            partStatus(EXTENSION_NS "partStatus", this, partStatus),  // The field is initialized to the value "Under construction"
            experience(EXTENSION_NS "experience", this),              // The optional field is not initialized with any value
            notes(EXTENSION_NS "notes", this),
            created(EXTENSION_NS "created", this),
            source(EXTENSION_NS "source", this),
            category(EXTENSION_NS "category", this),
            results(EXTENSION_NS "results", this),
            status(EXTENSION_NS "status", this)
            {
                // Register the extension class.
                register_extension_class < iGEMComponentDefinition >(EXTENSION_NS, EXTENSION_PREFIX, EXTENSION_CLASS);
            };
        
        // Destructor
        ~iGEMComponentDefinition() {};
   
    };
    /// @endcond
}

#endif
