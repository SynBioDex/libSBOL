#ifndef DOCUMENTED_INCLUDED
#define DOCUMENTED_INCLUDED

#include "identified.h"

#include <string>


namespace sbol {

	class Documented : public Identified {

	public:
		Documented(std::string uri_prefix = SBOL_URI "/Documented", std::string display_id = "example") : Documented(SBOL_URI "#" SBOL_DOCUMENTED, uri_prefix, display_id, "", "")
			{
			}
		Documented(sbol_type type, std::string uri_prefix, std::string display_id, std::string name, std::string description) :
			Identified(type, uri_prefix, display_id),
			displayID(Property<std::string>(display_id, SBOL_DISPLAY_ID, this)),
			name(Property<std::string>(name, SBOL_NAME, this)),
			description(Property<std::string>(name, SBOL_DESCRIPTION, this))
			{
			}

		Property<std::string> displayID;
		Property<std::string> name;
		Property<std::string> description;

		//sbol_type getTypeURI();
	};
}

#endif