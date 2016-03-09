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
		ReferencedObject<ComponentDefinition> definition;
		URIProperty access;
		List<OwnedObject<MapsTo>> mapsTos;

	protected:
        ComponentInstance(sbol_type type = SBOL_COMPONENT, std::string uri_prefix = SBOL_URI "/Component", std::string id = "example", std::string definition = "", std::string access = SBOL_ACCESS_PRIVATE) :
			Identified(type, uri_prefix, id, "", "", ""),
			definition(SBOL_DEFINITION, this, definition),
			access(SBOL_ACCESS, this, access),
			mapsTos(SBOL_MAPS_TOS, this)
			{
			};
	};

	class Component : public ComponentInstance
	{
	public:
        Component(std::string uri_prefix = SBOL_URI "/Component", std::string id = "example", std::string definition = "", std::string access = SBOL_ACCESS_PRIVATE) :
			Component(SBOL_COMPONENT, uri_prefix, id, definition, access)
			{
			};
        ~Component() {};

	protected:
        Component(sbol_type type, std::string uri_prefix, std::string id, std::string definition, std::string access) :
			ComponentInstance(type, uri_prefix, id, definition, access)
			{
			};
	};

	class FunctionalComponent : public ComponentInstance
	{
	public:
		URIProperty direction;
        FunctionalComponent(std::string uri_prefix = SBOL_URI "/FunctionalComponent", std::string id = "example", std::string definition = "", std::string access = SBOL_ACCESS_PRIVATE) :
			FunctionalComponent(SBOL_FUNCTIONAL_COMPONENT, uri_prefix, id, definition, access)
			{
			};
        ~FunctionalComponent() {};

	protected:
        FunctionalComponent(sbol_type type, std::string uri_prefix, std::string id, std::string definition, std::string access) :
			ComponentInstance(type, uri_prefix, id, definition, access),
			direction(SBOL_DIRECTION, this, SBOL_DIRECTION_NONE)
		{};

	};
}

#endif