#include "toplevel.h"

#include <string>

namespace sbol 
{
	class ComponentDefinition : public TopLevel
	{
		sbol_type type = SBOL_COMPONENT_DEFINITION;

	public:
		ComponentDefinition(std::string uri_prefix, std::string display_id) :
			TopLevel(uri_prefix, display_id)
			{
			}

	};
}