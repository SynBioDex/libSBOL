#ifndef TOP_LEVEL_INCLUDED
#define TOP_LEVEL_INCLUDED

#include "documented.h"

#include <string>

namespace sbol 
{
	class TopLevel : public Documented
	{
	public:
		TopLevel(sbol_type type = SBOL_TOP_LEVEL) :
			Documented(type)
			{
			}
		TopLevel(std::string uri_prefix, std::string display_id);
		void addToDocument(sbol::Document&);

	};
}

#endif