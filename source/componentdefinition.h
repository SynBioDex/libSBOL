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
    class Participation;
    
    /// The ComponentDefinition class represents the structural entities of a biological design. The primary usage of this class is to represent structural entities with designed sequences, such as DNA, RNA, and proteins, but it can also be used to represent any other entity that is part of a design, such as small molecules, proteins, and complexes
    /// @ingroup sbol_core_data_model
    class ComponentDefinition : public TopLevel
	{

	public:
        /// The types property is a REQUIRED set of URIs that specifies the category of biochemical or physical entity (for example DNA, protein, or small molecule) that a ComponentDefinition object abstracts for the purpose of engineering design.  The types property of every ComponentDefinition MUST contain one or more URIs that MUST identify terms from appropriate ontologies, such as the BioPAX ontology or the ontology of Chemical Entities of Biological Interest. See the table below for examples.
        /// | Type              | URI for BioPAX Term                                           | LibSBOL symbol        |
        /// | :---------------- | :------------------------------------------------------------ | :-------------------- |
        /// | DNA               | http://www.biopax.org/release/biopax-level3.owl#DnaRegion     | BIOPAX_DNA            |
        /// | RNA               | http://www.biopax.org/release/biopax-level3.owl#RnaRegion     | BIOPAX_RNA            |
        /// | Protein           | http://www.biopax.org/release/biopax-level3.owl#Protein       | BIOPAX_PROTEIN        |
        /// | Small Molecule    | http://www.biopax.org/release/biopax-level3.owl#SmallMolecule | BIOPAX_SMALL_MOLECULE |
        /// | Complex           | http://www.biopax.org/release/biopax-level3.owl#Complex       | BIOPAX_COMPLEX        |
        List<URIProperty> types;
        
        /// The roles property is an OPTIONAL set of URIs that clarifies the potential function of the entity represented by a ComponentDefinition in a biochemical or physical context. The roles property of a ComponentDefinition MAY contain one or more URIs that MUST identify terms from ontologies that are consistent with the types property of the ComponentDefinition. For example, the roles property of a DNA or RNA ComponentDefinition could contain URIs identifying terms from the Sequence Ontology (SO).  See the table below for common examples
        /// | Role              | URI for Sequence Ontology Term            | LibSBOL symbol    |
        /// | :---------------- | :---------------------------------------- | :---------------- |
        /// | Miscellaneous     | http://identifiers.org/so/SO:0000001      | SO_MISC           |
        /// | Promoter          | http://identifiers.org/so/SO:0000167      | SO_PROMOTER       |
        /// | RBS               | http://identifiers.org/so/SO:0000139      | SO_RBS            |
        /// | CDS               | http://identifiers.org/so/SO:0000316      | SO_CDS            |
        /// | Terminator        | http://identifiers.org/so/SO:0000141      | SO_TERMINATOR     |
        /// | Gene              | http://identifiers.org/so/SO:0000704      |                   |
        /// | Operator          | http://identifiers.org/so/SO:0000057      |                   |
        /// | Engineered Gene   | http://identifiers.org/so/SO:0000280      |                   |
        /// | mRNA              | http://identifiers.org/so/SO:0000234      |                   |
        /// | Effector          | http://identifiers.org/chebi/CHEBI:35224  |                   |
        List<URIProperty> roles;
        
        /// The components property is OPTIONAL and MAY specify a set of Component objects that are contained by the ComponentDefinition. The components properties of ComponentDefinition objects can be used to construct a hierarchy of Component and ComponentDefinition objects. If a ComponentDefinition in such a hierarchy refers to one or more Sequence objects, and there exist ComponentDefinition objects lower in the hierarchy that refer to Sequence objects with the same encoding, then the elements properties of these Sequence objects SHOULD be consistent with each other, such that well-defined mappings exist from the “lower level” elements to the “higher level” elements. This mapping is also subject to any restrictions on the positions of the Component objects in the hierarchy that are imposed by the SequenceAnnotation or SequenceConstraint objects contained by the ComponentDefinition objects in the hierarchy.  The set of relations between Component and ComponentDefinition objects is strictly acyclic.
        List<OwnedObject<Component>> components;
        
        /// The sequences property is OPTIONAL and MAY include a URI that refer to a Sequence object. The referenced object defines the primary structure of the ComponentDefinition.
        List<ReferencedObject> sequences;
        
        /// The sequenceAnnotations property is OPTIONAL and MAY contain a set of SequenceAnnotation objects. Each SequenceAnnotation specifies and describes a potentially discontiguous region on the Sequence objects referred to by the ComponentDefinition.
        List<OwnedObject<SequenceAnnotation>> sequenceAnnotations;
        
        /// The sequenceConstraints property is OPTIONAL and MAY contain a set of SequenceConstraint objects. These objects describe any restrictions on the relative, sequence-based positions and/or orientations of the Component objects contained by the ComponentDefinition. For example, the ComponentDefinition of a gene might specify that the position of its promoter Component precedes that of its CDS Component. This is particularly useful when a ComponentDefinition lacks a Sequence and therefore cannot specify the precise, sequence-based positions of its Component objects using SequenceAnnotation objects.
		List<OwnedObject<SequenceConstraint>> sequenceConstraints;

        /// Construct a ComponentDefinition
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param type A BioPAX ontology term that indicates whether the ComponentDefinition is DNA, RNA, protein, or some other molecule type.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        ComponentDefinition(std::string uri = DEFAULT_NS "/ComponentDefinition/example", std::string type = BIOPAX_DNA, std::string version = "1.0.0") : ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri, type, version) {};
        
//        // SBOL compliant constructor
//        ComponentDefinition(std::string uri_prefix, std::string display_id, std::string version, std::string type) : ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri_prefix, display_id, version, type) {};
        
        /// Assembles the provided vector of Components into a structural hierarchy.  Autoconstructs the required Components and SequenceConstraints.  The resulting data structure is a partial design, still lacking a specific DNA (or other) sequence.  To fully realize a design, use Sequence::assemble().
        /// @param list_of_components A list of subcomponents that will compose this ComponentDefinition
        void assemble(std::vector<ComponentDefinition*> list_of_components);
        std::string updateSequence(std::string composite_sequence = "");

        /// Orders this ComponentDefinition's member Components into a linear arrangement based on Sequence Constraints.
        /// @return Primary sequence structure
        std::vector<Component*> getInSequentialOrder();
        
        /// Checks if the specified Component has a Component upstream in linear arrangement on the DNA strand. Checks that the appropriate SequenceConstraint exists.
        /// @param current_component A Component in this ComponentDefinition
        /// @return 1 if found, 0 if not
        int hasUpstreamComponent(Component& current_component);
        
        /// Get the upstream Component.
        /// @return The upstream component
        Component& getUpstreamComponent(Component& current_component);

        /// Checks if the specified Component has a Component downstream in linear arrangement on the DNA strand. Checks that the appropriate SequenceConstraint exists.
        /// @param current_component A Component in this ComponentDefinition
        /// @return 1 if found, 0 if not
        int hasDownstreamComponent(Component& current_component);
        
        /// Get the downstream Component.
        /// @return The downstream component
        Component& getDownstreamComponent(Component& current_component);
        
        /// Gets the first Component in a linear sequence
        /// @return The first component in sequential order
        Component& getFirstComponent();

        /// Gets the last Component in a linear sequence
        /// @return The last component in sequential order
        Component& getLastComponent();
        
        /// A convenience method that assigns a component to participate in a biochemical reaction.  Behind the scenes, it auto-constructs a FunctionalComponent for this ComponentDefinition and assigns it to a Participation
        /// @param species A Participation object (ie, participant species in a biochemical Interaction).
        void participate(Participation& species);
        
        virtual ~ComponentDefinition() {  };
	protected:
		// This protected constructor is a delegate constructor.  It initializes ComponentDefinitions with the corresponding sbol_type_uri
        ComponentDefinition(sbol_type type, std::string uri, std::string component_type, std::string version) :
            TopLevel(type, uri, version),
            types(SBOL_TYPES, this, component_type),
            roles(SBOL_ROLES, this),
            sequences(SBOL_SEQUENCE_PROPERTY, SBOL_SEQUENCE, this),
            sequenceAnnotations(SBOL_SEQUENCE_ANNOTATIONS, this),
            components(SBOL_COMPONENTS, this),
            sequenceConstraints(SBOL_SEQUENCE_CONSTRAINTS, this)
            {
            };
        
//        ComponentDefinition(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string component_type) :
//			TopLevel(type, uri_prefix, display_id, version),
//			types(SBOL_TYPES, this, component_type),
//			roles(SBOL_ROLES, this),
//			sequence(SBOL_SEQUENCE_PROPERTY, this),
//			sequenceAnnotations(SBOL_SEQUENCE_ANNOTATIONS, this),
//			components(SBOL_COMPONENTS, this),
//			sequenceConstraints(SBOL_SEQUENCE_CONSTRAINTS, this)
//			{
//			}
	};
}

#endif