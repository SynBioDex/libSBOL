#ifndef TOP_LEVEL_INCLUDED
#define TOP_LEVEL_INCLUDED

#include "documented.h"

#include <string>

namespace sbol 
{
	class TopLevel : public Documented
	{
	public:
		TopLevel(sbol_type type, std::string uri_prefix, std::string display_id, std::string name, std::string description) :
			Documented(type, uri_prefix, display_id, name, description)
			{
			}
		TopLevel(std::string uri_prefix = SBOL_URI "/TopLevel", std::string display_id = "example") : TopLevel(SBOL_URI "#" SBOL_TOP_LEVEL, uri_prefix, display_id, "", "")
			{
			}
		void addToDocument(sbol::Document&);

	};
}

#endif