#ifndef DOCUMENTED_INCLUDED
#define DOCUMENTED_INCLUDED

#include "identified.h"

#include <string>


namespace sbol {

	class Documented : public Identified {

	public:
		Documented(std::string uri_prefix = "http://sbolstandard.org/documented", std::string display_id = "example") : Documented(SBOL_DOCUMENTED, uri_prefix, display_id, "", "")
			{
			}
		Documented(sbol_type type, std::string uri_prefix, std::string display_id, std::string name, std::string description) :
			Identified(type, uri_prefix, display_id),
			displayID(TextProperty(SBOL_DISPLAY_ID, this, display_id)),
			name(TextProperty(SBOL_NAME, this, name)),
			description(TextProperty(SBOL_DESCRIPTION, this, name))
			{
			}

		TextProperty displayID;
		TextProperty name;
		TextProperty description;

		//sbol_type getTypeURI();
	};
}

#endif