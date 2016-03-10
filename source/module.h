#ifndef MODULE_INCLUDED
#define MODULE_INCLUDED

#include "identified.h"
#include "mapsto.h"

namespace sbol
{
    // Forward declaration of ModuleDefinition necesaary for Module.definition template
    class ModuleDefinition;
    
    class Module : public Identified
	{
	public:
		ReferencedObject<ModuleDefinition> definition;
        List<OwnedObject<MapsTo>> mapsTos;
        
        Module(std::string uri = DEFAULT_NS "/Module/example", std::string definition = "") : Module(SBOL_MODULE, uri, definition) {};

        Module(std::string uri_prefix, std::string display_id, std::string version, std::string definition) :
            Module(SBOL_MODULE, uri_prefix, display_id, version, definition) {};

        ~Module() {};
        
	protected:
        Module(sbol_type type, std::string uri, std::string definition) :
            Identified(type, uri),
            definition(SBOL_DEFINITION, this, definition),
            mapsTos(SBOL_MAPS_TO, this)
            {
            };
        
        Module(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition) :
			Identified(type, uri_prefix, display_id, version),
			definition(SBOL_DEFINITION, this, definition),
			mapsTos(SBOL_MAPS_TO, this)
			{
            };
	};
}

#endif