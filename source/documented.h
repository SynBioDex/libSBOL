#ifndef DOCUMENTED_INCLUDED
#define DOCUMENTED_INCLUDED

#include "identified.h"

#include <string>


namespace sbol {

	class Documented : public Identified {
		sbol_type type = SBOL_DOCUMENTED;

	public:
		Documented(std::string uri_prefix, std::string display_id) :
			Identified(uri_prefix, display_id),
			displayID(TextProperty(display_id)),
			name(TextProperty()),
			description(TextProperty())
			{
			}
		TextProperty displayID;
		TextProperty name;
		TextProperty description;
	};
}

#endif