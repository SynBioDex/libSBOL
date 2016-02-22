#ifndef INTERACTION_INCLUDED
#define INTERACTION_INCLUDED

#include "identified.h"
#include "participation.h"

namespace sbol
{
	class Interaction : public Identified
	{

	public:
		List<URIProperty> types;
		List<OwnedObject<Participation>> participations;
		
		Interaction(std::string uri_prefix = SBOL_URI "/Interaction", std::string id = "example") :
			Interaction(SBOL_INTERACTION, uri_prefix, id)
			{
			}
        ~Interaction() {};
	protected:
		Interaction(sbol_type type, std::string uri_prefix, std::string id) :
			Identified(type, uri_prefix, id, "", "", ""),
			types(SBOL_TYPES, this, UNDEFINED),
			participations(SBOL_PARTICIPATIONS, this)
			{
			}
	};
}

#endif