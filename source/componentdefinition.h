#include "toplevel.h"

#include <string>

namespace sbol 
{
	class ComponentDefinition : public TopLevel
	{
	public:
		ComponentDefinition(sbol_type type = SBOL_COMPONENT_DEFINITION) :
			TopLevel(type)
			{
			}
		ComponentDefinition(std::string, std::string);
	};
}