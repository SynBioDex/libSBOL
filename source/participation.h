#ifndef PARTICIPATION_INCLUDED
#define PARTICIPATION_INCLUDED

#include "identified.h"

namespace sbol
{
	class Participation : public Identified
	{

	public:
		List<URIProperty> roles;
		ReferencedObject participant;

		Participation(std::string uri_prefix = SBOL_URI "/Participation", std::string id = "example") :
			Participation(SBOL_PARTICIPATION, uri_prefix, id)
			{
			}
        ~Participation(){};
	protected:
		Participation(sbol_type type, std::string uri_prefix, std::string id) :
			Identified(type, uri_prefix, id, "", "", ""),
			roles(SBOL_ROLES, this, UNDEFINED),
			participant(SBOL_PARTICIPANT, this, UNDEFINED) 
		{
		}
	};
}

#endif