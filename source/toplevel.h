#ifndef TOP_LEVEL_INCLUDED
#define TOP_LEVEL_INCLUDED

#include "documented.h"

#include <string>

namespace sbol 
{
	class SBOLDocument;

	class TopLevel : public Documented
	{
		sbol_type type = SBOL_TOP_LEVEL;

	public:
		TopLevel(std::string uri_prefix, std::string display_id) :
			Documented(uri_prefix, display_id)
			{
			}
		void addToDocument(sbol::SBOLDocument&);

	};
}

#endif