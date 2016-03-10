#ifndef COMPONENT_INCLUDED
#define COMPONENT_INCLUDED

#include "identified.h"
#include "mapsto.h"

#include <string>

namespace sbol
{
    // Forward declaration necessary for ComponentInstance.definition
    class ComponentDefinition;
    
    class ComponentInstance : public Identified
	{

	public:
		URIProperty access;
		List<OwnedObject<MapsTo>> mapsTos;
#ifdef SBOL_GENERATE_PY
        ReferencedObject definition;
#else
        ReferencedObject<ComponentDefinition> definition;
#endif
        
	protected:
        ComponentInstance(sbol_type type, std::string uri, std::string definition, std::string access) :
            Identified(type, uri),
            definition(SBOL_DEFINITION, this, definition),
            access(SBOL_ACCESS, this, access),
            mapsTos(SBOL_MAPS_TOS, this)
            {
            };
        ComponentInstance(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access) :
            Identified(type, uri_prefix, display_id, version),
            definition(SBOL_DEFINITION, this, definition),
            access(SBOL_ACCESS, this, access),
            mapsTos(SBOL_MAPS_TOS, this)
            {
            };
	};

	class Component : public ComponentInstance
	{
	public:
        Component(std::string uri = DEFAULT_NS "/Component/example", std::string definition = "", std::string access = SBOL_ACCESS_PRIVATE) :
            Component(SBOL_COMPONENT, uri, definition, access) {};
        
        Component(std::string uri_prefix, std::string display_id, std::string version, std::string definition,std::string access) : Component(SBOL_COMPONENT, uri_prefix, display_id, version, definition, access) {};
        
        ~Component() {};

	protected:
        Component(sbol_type type, std::string uri, std::string definition, std::string access) :
            ComponentInstance(type, uri, definition, access) {};
        
        Component(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access) : ComponentInstance(type, uri_prefix, display_id, version, definition, access) {};
	};

	class FunctionalComponent : public ComponentInstance
	{
	public:
		URIProperty direction;

        FunctionalComponent(std::string uri = DEFAULT_NS "/FunctionalComponent/example", std::string definition = "", std::string access = SBOL_ACCESS_PRIVATE) : FunctionalComponent(SBOL_FUNCTIONAL_COMPONENT, uri, definition, access) {};
        
        FunctionalComponent(std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access) : FunctionalComponent(SBOL_FUNCTIONAL_COMPONENT, uri_prefix, display_id, version, definition, access) {};
        
        ~FunctionalComponent() {};

	protected:
        FunctionalComponent(sbol_type type, std::string uri, std::string definition, std::string access) :
            ComponentInstance(type, uri, definition, access),
            direction(SBOL_DIRECTION, this, SBOL_DIRECTION_NONE) {};
        
        FunctionalComponent(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access) :
			ComponentInstance(type, uri_prefix, display_id, version, definition, access),
			direction(SBOL_DIRECTION, this, SBOL_DIRECTION_NONE) {};

	};
}

#endif