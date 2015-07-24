#include "toplevel.h"

#include <string>

namespace sbol 
{
	class ComponentDefinition : public TopLevel
	{
	public:
		ComponentDefinition(sbol_type type, std::string uri_prefix, std::string display_id, std::string name, std::string description) :
			TopLevel(type, uri_prefix, display_id, name, description),
			type(1, SBOL_TYPE, this)
			{
			}
		ComponentDefinition(std::string uri_prefix = SBOL_URI "/ComponentDefinition", std::string display_id = "example") : ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri_prefix, display_id, "", "")
			{
			}
		ListProperty<int> type;

	};
}