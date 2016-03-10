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
        List<OwnedObject<Component>> components;
        ReferencedObject<Sequence> sequence;
        List<OwnedObject<SequenceAnnotation>> sequenceAnnotations;
		List<OwnedObject<SequenceConstraint>> sequenceConstraints;

        // Open world constructor
        ComponentDefinition(std::string uri = DEFAULT_NS "/ComponentDefinition/example", std::string type = BIOPAX_DNA) : ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri, type) {};
        
        // SBOL compliant constructor
        ComponentDefinition(std::string uri_prefix, std::string display_id, std::string version, std::string type) : ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri_prefix, display_id, version, type) {};
        
        ~ComponentDefinition() {  };
	protected:
		// This protected constructor is a delegate constructor.  It initializes ComponentDefinitions with the corresponding sbol_type_uri 
        ComponentDefinition(sbol_type type, std::string uri, std::string component_type) :
            TopLevel(type, uri),
            types(SBOL_TYPES, this, component_type),
            roles(SBOL_ROLES, this),
            sequence(SBOL_SEQUENCE_PROPERTY, this),
            sequenceAnnotations(SBOL_SEQUENCE_ANNOTATIONS, this),
            components(SBOL_COMPONENTS, this),
            sequenceConstraints(SBOL_SEQUENCE_CONSTRAINTS, this)
            {
            };
        
        ComponentDefinition(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string component_type) :
			TopLevel(type, uri_prefix, display_id, version),
			types(SBOL_TYPES, this, component_type),
			roles(SBOL_ROLES, this),
			sequence(SBOL_SEQUENCE_PROPERTY, this),
			sequenceAnnotations(SBOL_SEQUENCE_ANNOTATIONS, this),
			components(SBOL_COMPONENTS, this),
			sequenceConstraints(SBOL_SEQUENCE_CONSTRAINTS, this)
			{
			}
	};
}

#endif