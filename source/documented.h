#ifndef DOCUMENTED_INCLUDED
#define DOCUMENTED_INCLUDED

#include "identified.h"

#include <string>


namespace sbol {

	class Documented : public Identified {
		sbol_type type = SBOL_DOCUMENTED;

	public:
		Documented(std::string uri_prefix = "http://examples.com/", std::string display_id = "Documented") :
			Identified(uri_prefix, display_id),
			displayID(TextProperty()),
			name(TextProperty()),
			description(TextProperty())
			{
			}
		TextProperty displayID;
		TextProperty name;
		TextProperty description;

		sbol_type getTypeURI();
	};
}

#endif