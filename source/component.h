#ifndef COMPONENT_INCLUDED
#define COMPONENT_INCLUDED

#include "identified.h"
#include <string>

namespace sbol
{
	class ComponentInstance : public Identified
	{

	public:
		URIProperty access;

	protected:
		ComponentInstance(sbol_type type = SBOL_COMPONENT, std::string uri_prefix = SBOL_URI "/Component", std::string id = "example", std::string access = SBOL_ACCESS_PRIVATE) :
			Identified(type, uri_prefix, id, "", "", ""),
			access(SBOL_ACCESS, this, access)
		{};
	};

	class Component : public ComponentInstance
	{
	public:
		Component(sbol_type type = SBOL_COMPONENT, std::string uri_prefix = SBOL_URI "/Component", std::string id = "example", std::string access = SBOL_ACCESS_PRIVATE) : ComponentInstance(type, uri_prefix, id, access) {};
		~Component();
	};

	class FunctionalComponent : public ComponentInstance
	{
	public:
		URIProperty direction;
		~FunctionalComponent();

		FunctionalComponent(sbol_type type = SBOL_COMPONENT, std::string uri_prefix = SBOL_URI "/FunctionalComponent", std::string id = "example") : 
			ComponentInstance(type, uri_prefix, id),
			direction(SBOL_DIRECTION, this, SBOL_DIRECTION_NONE)
		{};
	};
}

#endif