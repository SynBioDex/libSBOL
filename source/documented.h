#ifndef DOCUMENTED_INCLUDED
#define DOCUMENTED_INCLUDED

#include "identified.h"

#include <string>


namespace sbol {

	class Documented : public Identified {

	public:
		Documented(sbol_type type = SBOL_DOCUMENTED) :
			Identified(type),
			displayID(TextProperty()),
			name(TextProperty()),
			description(TextProperty())
			{
			}
		Documented(std::string, std::string);
		TextProperty displayID;
		TextProperty name;
		TextProperty description;

		//sbol_type getTypeURI();
	};
}

#endif