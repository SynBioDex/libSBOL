#ifndef DOCUMENTED_INCLUDED
#define DOCUMENTED_INCLUDED

#include "identified.h"

#include <string>


namespace sbol {

	class Documented : public Identified {

	// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
	protected:
		Documented(sbol_type type, std::string uri_prefix, std::string display_id, std::string name, std::string description) :
			Identified(type, uri_prefix, display_id),
			displayID(Property<std::string>(SBOL_DISPLAY_ID, this, display_id)),
			name(Property<std::string>(SBOL_NAME, this, name)),
			description(Property<std::string>(SBOL_DESCRIPTION, this, name))
		{
			std::cout << "Constructing Documented" << std::endl;

		}

	public:
		Documented(std::string uri_prefix = SBOL_URI "/Documented", std::string display_id = "example") : Documented(SBOL_DOCUMENTED, uri_prefix, display_id, "", "")
			{
			}

		Property<std::string> displayID;
		Property<std::string> name;
		Property<std::string> description;

		//sbol_type getTypeURI();
	};
}

#endif