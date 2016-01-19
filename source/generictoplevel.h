#ifndef GENERIC_TOP_LEVEL_INCLUDED
#define GENERIC_TOP_LEVEL_INCLUDED

#include "toplevel.h"

#include <string>

namespace sbol 
{
	class GenericTopLevel : public TopLevel
	{
		sbol_type type = SBOL_GENERIC_TOP_LEVEL;

	public:
		GenericTopLevel(std::string uri_prefix, std::string display_id) :
			TopLevel(uri_prefix, display_id)
			{
			}

	};
}

#endif