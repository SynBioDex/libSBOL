#ifndef MODULE_DEFINITION_INCLUDED
#define MODULE_DEFINITION_INCLUDED

#include "toplevel.h"
#include "module.h"
#include "component.h"
#include "interaction.h"

#include <string>

namespace sbol
{
    // Forward declaration of Model necessary for template instantiation of ModuleDefinition.models;
    class Model;
    
    /// The ModuleDefinition class represents a grouping of structural and functional entities in a biological design. The primary usage of this class is to assert the molecular interactions and abstract function of its child entities.
    class ModuleDefinition : public TopLevel
	{

	public:
		List<URIProperty> roles;
		List<OwnedObject<Module>> modules;
		List<OwnedObject<Interaction>> interactions;
		List<OwnedObject<FunctionalComponent>> functionalComponents;
        ReferencedObject models;
        
		ModuleDefinition(std::string uri = DEFAULT_NS "/ModuleDefinition/example") : ModuleDefinition(SBOL_MODULE_DEFINITION, uri) {};
        
		ModuleDefinition(std::string uri_prefix, std::string display_id, std::string version) : ModuleDefinition(SBOL_MODULE_DEFINITION, uri_prefix, display_id, version) {};
        
        ~ModuleDefinition() {};
	protected:
		// This protected constructor is a delegate constructor.  It initializes ComponentDefinitions with the corresponding sbol_type_uri
        ModuleDefinition(sbol_type sbol_type_uri, std::string uri) :
            TopLevel(sbol_type_uri, uri),
            roles(SBOL_ROLES, this),
            models(SBOL_MODELS, this),
            functionalComponents(SBOL_FUNCTIONAL_COMPONENTS, this),
            modules(SBOL_MODULES, this),
            interactions(SBOL_INTERACTIONS, this)
            {
            };

		ModuleDefinition(sbol_type sbol_type_uri, std::string uri_prefix, std::string display_id, std::string version) :
			TopLevel(sbol_type_uri, uri_prefix, display_id, version),
			roles(SBOL_ROLES, this),
			models(SBOL_MODELS, this),
			functionalComponents(SBOL_FUNCTIONAL_COMPONENTS, this),
			modules(SBOL_MODULES, this),
			interactions(SBOL_INTERACTIONS, this)
			{
            };
	};
}

#endif