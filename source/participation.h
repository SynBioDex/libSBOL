#ifndef PARTICIPATION_INCLUDED
#define PARTICIPATION_INCLUDED

#include "identified.h"

namespace sbol
{
    // Forward declaration of FunctionalComponent necessary for Participation.participant property
    class FunctionalComponent;
    
    class Participation : public Identified
	{
	public:
		List<URIProperty> roles;
		ReferencedObject<FunctionalComponent> participant;
        
        Participation(std::string uri = DEFAULT_NS "/Participation/example", std::string participant = "") : Participation(SBOL_PARTICIPATION, uri, participant) {};

        Participation(std::string uri_prefix, std::string display_id, std::string version, std::string participant) : Participation(SBOL_PARTICIPATION, uri_prefix, display_id, version, participant) {};
        
        ~Participation(){};
	protected:
        Participation(sbol_type type, std::string uri, std::string participant) :
            Identified(type, uri),
            roles(SBOL_ROLES, this),
            participant(SBOL_PARTICIPANT, SBOL_FUNCTIONAL_COMPONENT, this, participant)
            {
            };
        
        Participation(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string participant) :
			Identified(type, uri_prefix, display_id, version),
			roles(SBOL_ROLES, this),
			participant(SBOL_PARTICIPANT, SBOL_FUNCTIONAL_COMPONENT, this, participant)
            {
            };
	};
}

#endif