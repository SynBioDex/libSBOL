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
        /// The definition property is a REQUIRED URI that refers to the ModuleDefinition for the Module.
        ReferencedObject definition;
        
        /// The mapsTos property is an OPTIONAL set of MapsTo objects that refer to and link ComponentInstance objects together within the heterarchy of Module, ModuleDefinition, ComponentInstance, and ComponentDefinition objects.
        List<OwnedObject<MapsTo>> mapsTos;
        
        /// Construct a Module. If operating in SBOL-compliant mode, use ModuleDefinition::modules::create instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param definition The identity of the Component with this structural constraint
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Module(std::string uri = DEFAULT_NS "/Module/example", std::string definition = "", std::string version = "1.0.0") : Module(SBOL_MODULE, uri, definition, version) {};

        virtual ~Module() {};
        
	protected:
        Module(sbol_type type, std::string uri, std::string definition, std::string version) :
            Identified(type, uri, version),
            definition(SBOL_DEFINITION, SBOL_MODULE_DEFINITION, this, definition),
            mapsTos(SBOL_MAPS_TOS, this)
            {
            };
	};
}

#endif