#include "toplevel.h"

#include <string>

namespace sbol 
{
	class ComponentDefinition : public TopLevel
	{
	public:
		ComponentDefinition(sbol_type type, std::string uri_prefix, std::string display_id, std::string name, std::string description) :
			TopLevel(type, uri_prefix, display_id, name, description)
			{
			}
		ComponentDefinition(std::string uri_prefix = SBOL_NAMESPACE "/ComponentDefinition", std::string display_id = "") : ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri_prefix, display_id, "", "")
			{
			}
	};
}