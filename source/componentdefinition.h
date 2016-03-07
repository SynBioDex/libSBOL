#ifndef COMPONENT_DEFINITION_INCLUDED
#define COMPONENT_DEFINITION_INCLUDED

#include "toplevel.h"
#include "component.h"
#include "sequenceannotation.h"
#include "sequenceconstraint.h"
#include <string>

namespace sbol 
{
    // Forward declaration of Sequence necessary for ComponentDefinition.sequence property
    class Sequence;
    
    class ComponentDefinition : public TopLevel
	{

	public:
		List<URIProperty> types;
		List<URIProperty> roles;
		ReferencedObject<Sequence> sequence;
		List<OwnedObject<SequenceAnnotation>> sequenceAnnotations;
		List<OwnedObject<Component>> components;
		List<OwnedObject<SequenceConstraint>> sequenceConstraints;

		ComponentDefinition(std::string uri_prefix = SBOL_URI "/ComponentDefinition",
			std::string display_id = "example",
			std::string type = SO_UNDEFINED,
			std::string role = SO_UNDEFINED,
			std::string name = "",
			std::string description = "",
			std::string version = "1.0.0") :
			ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri_prefix, display_id, type, role, name, description, version)
			{
			}
		~ComponentDefinition() {  };
	protected:
		// This protected constructor is a delegate constructor.  It initializes ComponentDefinitions with the corresponding sbol_type_uri 
		ComponentDefinition(sbol_type sbol_type_uri, std::string uri_prefix, std::string display_id, std::string type, std::string role, std::string name, std::string description, std::string version) :
			TopLevel(sbol_type_uri, uri_prefix, display_id, name, description, version),
			types(SBOL_TYPES, this, type),
			roles(SBOL_ROLES, this, role),
			sequence(SBOL_SEQUENCE_PROPERTY, this, ""),
			sequenceAnnotations(SBOL_SEQUENCE_ANNOTATIONS, this),
			components(SBOL_COMPONENTS, this),
			sequenceConstraints(SBOL_SEQUENCE_CONSTRAINTS, this)
			{
			}
	};
}

#endif