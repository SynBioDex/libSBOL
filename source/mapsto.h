#ifndef MAPS_TO_INCLUDED
#define MAPS_TO_INCLUDED

#include "identified.h"

namespace sbol
{
    class ComponentInstance;  // Forward declaration necessary for ReferencedObject templates
    
    class MapsTo : public Identified
	{
	public:
		ReferencedObject<ComponentInstance> local;
		ReferencedObject<ComponentInstance> remote;
		URIProperty refinement;

		MapsTo(std::string uri_prefix = SBOL_URI "/MapsTo", std::string id = "example") :
			MapsTo(SBOL_MAPS_TO, uri_prefix, id)
		{
		}
        ~MapsTo() {};
	protected:
		MapsTo(sbol_type type, std::string uri_prefix, std::string id) :
			Identified(type, uri_prefix, id, "", "", ""),
			refinement(SBOL_REFINEMENT, this),
			local(SBOL_LOCAL, this, UNDEFINED),
			remote(SBOL_REMOTE, this, UNDEFINED)
			{
			}
	};
}

#endif