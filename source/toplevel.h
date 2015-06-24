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
			Documented(type, uri_prefix, display_id, "", "")
			{
			}
		TopLevel(std::string uri_prefix, std::string display_id) : TopLevel(SBOL_TOP_LEVEL, uri_prefix, display_id, "", "")
			{
			}
		void addToDocument(sbol::Document&);

	};
}

#endif