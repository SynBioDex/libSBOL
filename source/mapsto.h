#ifndef MAPS_TO_INCLUDED
#define MAPS_TO_INCLUDED

#include "identified.h"

namespace sbol
{
    class ComponentInstance;  // Forward declaration necessary for ReferencedObject templates
    
    class MapsTo : public Identified
	{
	public:
        URIProperty refinement;
        ReferencedObject local;
        ReferencedObject remote;

        MapsTo(std::string uri = DEFAULT_NS "/MapsTo/example", std::string local = "", std::string remote = "", std::string refinement = SBOL_REFINEMENT_VERIFY_IDENTICAL) : MapsTo(SBOL_MAPS_TO, uri, local, remote, refinement) {};
        
        MapsTo(std::string uri_prefix, std::string display_id, std::string version, std::string local, std::string remote, std::string refinement) : MapsTo(SBOL_MAPS_TO, uri_prefix, display_id, version, local, remote, refinement) {};
        
        ~MapsTo() {};
	protected:
        MapsTo(sbol_type type, std::string uri, std::string local, std::string remote, std::string refinement) :
            Identified(type, uri),
            refinement(SBOL_REFINEMENT, this, refinement),
            local(SBOL_LOCAL, this, local),
            remote(SBOL_REMOTE, this, remote)
            {
            }
        MapsTo(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string local, std::string remote, std::string refinement) :
			Identified(type, uri_prefix, display_id, version),
			refinement(SBOL_REFINEMENT, this, refinement),
			local(SBOL_LOCAL, this, local),
			remote(SBOL_REMOTE, this, remote)
			{
			}
	};
}

#endif