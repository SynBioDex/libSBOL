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

        Participation(std::string uri_prefix = SBOL_URI "/Participation", std::string id = "example", std::string role = SBO_REACTANT, std::string participant_uri = "") :
			Participation(SBOL_PARTICIPATION, uri_prefix, id, role, participant_uri)
			{
			}
        ~Participation(){};
	protected:
        Participation(sbol_type type, std::string uri_prefix, std::string id, std::string role, std::string participant_uri) :
			Identified(type, uri_prefix, id, "", "", ""),
			roles(SBOL_ROLES, this, role),
			participant(SBOL_PARTICIPANT, this, participant_uri)
		{
		}
	};
}

#endif