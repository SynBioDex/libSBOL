#include "toplevel.h"
#include "module.h"
#include "component.h"
#include "interaction.h"

#include <string>

namespace sbol
{
	class ModuleDefinition : public TopLevel
	{
	public:
		List<URIProperty> roles;
		ReferencedObject models;
		List<OwnedObject<Module>> modules;
		List<OwnedObject<Interaction>> interactions;
		List<OwnedObject<FunctionalComponent>> functionalComponents;

		ModuleDefinition(std::string uri_prefix = SBOL_URI "/ModuleDefinition",
			std::string display_id = "example",
			std::string role = UNDEFINED,
			std::string model = "",
			std::string name = "",
			std::string description = "",
			std::string version = "1.0.0") :
			ModuleDefinition(SBOL_MODULE_DEFINITION, uri_prefix, display_id, role, name, description, version)
			{
			}
		~ModuleDefinition();
	protected:
		// This protected constructor is a delegate constructor.  It initializes ComponentDefinitions with the corresponding sbol_type_uri 
		ModuleDefinition(sbol_type sbol_type_uri, std::string uri_prefix, std::string display_id, std::string role, std::string model, std::string name, std::string description, std::string version) :
			TopLevel(sbol_type_uri, uri_prefix, display_id, name, description, version),
			roles(SBOL_ROLES, this, role),
			models(SBOL_MODELS, this, model),
			functionalComponents(SBOL_FUNCTIONAL_COMPONENTS, this),
			modules(SBOL_MODULES, this),
			interactions(SBOL_INTERACTIONS, this)
			{
			}
	};
}