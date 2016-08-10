#ifndef MODULE_INCLUDED
#define MODULE_INCLUDED

#include "identified.h"
#include "mapsto.h"

namespace sbol
{
    // Forward declaration of ModuleDefinition necesaary for Module.definition template
    class ModuleDefinition;
    
    /// The Module class represents a submodule of a ModuleDefinition within a hierarchical design.
    class Module : public Identified
	{
	public:
        ReferencedObject definition;
        List<OwnedObject<MapsTo>> mapsTos;
        
        Module(std::string uri = DEFAULT_NS "/Module/example", std::string definition = "", std::string version = "1.0.0") : Module(SBOL_MODULE, uri, definition, version) {};

//        Module(std::string uri_prefix, std::string display_id, std::string version, std::string definition) :
//            Module(SBOL_MODULE, uri_prefix, display_id, version, definition) {};

        virtual ~Module() {};
        
	protected:
        Module(sbol_type type, std::string uri, std::string definition, std::string version) :
            Identified(type, uri, version),
            definition(SBOL_DEFINITION, SBOL_MODULE_DEFINITION, this, definition),
            mapsTos(SBOL_MAPS_TOS, this)
            {
            };
        
//        Module(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition) :
//			Identified(type, uri_prefix, display_id, version),
//			definition(SBOL_DEFINITION, SBOL_MODULE_DEFINITION, this, definition),
//			mapsTos(SBOL_MAPS_TO, this)
//			{
//            };
	};
}

#endif