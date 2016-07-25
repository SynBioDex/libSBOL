#ifndef COMPONENT_INCLUDED
#define COMPONENT_INCLUDED

#include "identified.h"
#include "mapsto.h"

#include <string>

namespace sbol
{
    // Forward declaration necessary for ComponentInstance.definition
    class ComponentDefinition;
    
    /// @cond
    class ComponentInstance : public Identified
	{

	public:
		URIProperty access;
		List<OwnedObject<MapsTo>> mapsTos;
        ReferencedObject definition;
        
	protected:
        ComponentInstance(sbol_type type, std::string uri, std::string definition, std::string access, std::string version) :
            Identified(type, uri, version),
            definition(SBOL_DEFINITION, SBOL_COMPONENT_DEFINITION, this, definition),
            access(SBOL_ACCESS, this, access),
            mapsTos(SBOL_MAPS_TOS, this)
            {
            };
//        ComponentInstance(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access) :
//            Identified(type, uri_prefix, display_id, version),
//            definition(SBOL_DEFINITION, SBOL_COMPONENT_DEFINITION, this, definition),
//            access(SBOL_ACCESS, this, access),
//            mapsTos(SBOL_MAPS_TOS, this)
//            {
//            };
	};
    /// @endcond

    /// The Component class is used to compose ComponentDefinition objects into a structural hierarchy. For example, the ComponentDefinition of a gene could contain four Component objects: a promoter, RBS, CDS, and terminator. In turn, the ComponentDefinition of the promoter Component could contain Component objects defined as various operator sites.
	class Component : public ComponentInstance
	{
	public:
        Component(std::string uri = DEFAULT_NS "/Component/example", std::string definition = "", std::string access = SBOL_ACCESS_PRIVATE, std::string version = "1.0.0") :
            Component(SBOL_COMPONENT, uri, definition, access, version) {};
        
//        Component(std::string uri_prefix, std::string display_id, std::string version, std::string definition,std::string access) : Component(SBOL_COMPONENT, uri_prefix, display_id, version, definition, access) {};
        
        ~Component() {};

	protected:
        Component(sbol_type type, std::string uri, std::string definition, std::string access, std::string version) :
            ComponentInstance(type, uri, definition, access, version) {};
        
//        Component(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access) : ComponentInstance(type, uri_prefix, display_id, version, definition, access) {};
	};
 
    /// The FunctionalComponent class is used to specify the functional usage of a ComponentDefinition inside a ModuleDefinition. The ModuleDefinition describes how the that describes how the FunctionalComponent interacts with others and summarizes their aggregate function.
	class FunctionalComponent : public ComponentInstance
	{
	public:
		URIProperty direction;

        FunctionalComponent(std::string uri = DEFAULT_NS "/FunctionalComponent/example", std::string definition = "", std::string access = SBOL_ACCESS_PRIVATE, std::string direction = SBOL_DIRECTION_NONE) : FunctionalComponent(SBOL_FUNCTIONAL_COMPONENT, uri, definition, access, direction) {};
        
//        FunctionalComponent(std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access, std::string direction) : FunctionalComponent(SBOL_FUNCTIONAL_COMPONENT, uri_prefix, display_id, version, definition, access, direction) {};
        
        ~FunctionalComponent() {};

	protected:
        FunctionalComponent(sbol_type type, std::string uri, std::string definition, std::string access, std::string direction) :
            ComponentInstance(type, uri, definition, access, ""),
            direction(SBOL_DIRECTION, this, direction) {};
        
//        FunctionalComponent(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access, std::string direction) :
//            ComponentInstance(type, uri_prefix, display_id, version, definition, access),
//            direction(SBOL_DIRECTION, this, direction) {};

	};
}

#endif