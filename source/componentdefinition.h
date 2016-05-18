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
    
    /// The ComponentDefinition class represents the structural entities of a biological design. The primary usage of this class is to represent structural entities with designed sequences, such as DNA, RNA, and proteins, but it can also be used to represent any other entity that is part of a design, such as small molecules, molecular complexes, and light
    class ComponentDefinition : public TopLevel
	{

	public:
        /// The types property is a REQUIRED set of URIs that specifies the category of biochemical or physical entity (for example DNA, protein, or small molecule) that a ComponentDefinition object abstracts for the purpose of engineering design.  The types property of every ComponentDefinition MUST contain one or more URIs that MUST identify terms from appropriate ontologies, such as the BioPAX ontology or the ontology of Chemical Entities of Biological Interest.  Examples are #BIOPAX_DNA, #BIOPAX_RNA, #BIOPAX_PROTEIN
		List<URIProperty> types;
        
        /// The roles property is an OPTIONAL set of URIs that clarifies the potential function of the entity represented by a ComponentDefinition in a biochemical or physical context. The roles property of a ComponentDefinition MAY contain one or more URIs that MUST identify terms from ontologies that are consistent with the types property of the ComponentDefinition. For example, the roles property of a DNA or RNA ComponentDefinition could contain URIs identifying terms from the Sequence Ontology (SO).
        List<URIProperty> roles;
        List<OwnedObject<Component>> components;
        ReferencedObject sequence;        
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
            sequence(SBOL_SEQUENCE_PROPERTY, SBOL_SEQUENCE, this),
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