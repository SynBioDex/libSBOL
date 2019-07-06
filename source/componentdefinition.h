/**
 * @file    componentdefinition.h
 * @brief   ComponentDefinition class
 * @author  Bryan Bartley
 * @email   bartleyba@sbolstandard.org
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBOL.  Please visit http://sbolstandard.org for more
 * information about SBOL, and the latest version of libSBOL.
 *
 *  Copyright 2016 University of Washington, WA, USA
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ------------------------------------------------------------------------->*/

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
    class SBOL_DECLSPEC ComponentDefinition : public TopLevel
	{

	public:
        /// Construct a ComponentDefinition
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param type A BioPAX ontology term that indicates whether the ComponentDefinition is DNA, RNA, protein, or some other molecule type.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        ComponentDefinition(std::string uri = "example", std::string type = BIOPAX_DNA, std::string version = VERSION_STRING) : ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri, type, version) {};

        /// Constructor used for defining extension classes
        /// @param type The RDF type for an extension class derived from this one
        ComponentDefinition(rdf_type type, std::string uri, std::string component_type, std::string version) :
            TopLevel(type, uri, version),
            types(this, SBOL_TYPES, '1', '*', ValidationRules({}), component_type),
            roles(this, SBOL_ROLES, '0', '*', ValidationRules({})),
            // sequence(this, SBOL_SEQUENCE_PROPERTY, SBOL_SEQUENCE, '0', '1', ValidationRules({})),
            sequence(this, SBOL_SEQUENCE, '0', '1', ValidationRules({ libsbol_rule_20 })),
            sequences(this, SBOL_SEQUENCE_PROPERTY, SBOL_SEQUENCE, '0', '*', ValidationRules({ libsbol_rule_21 })),
            sequenceAnnotations(this, SBOL_SEQUENCE_ANNOTATIONS, '0', '*', ValidationRules({})),
            components(this, SBOL_COMPONENTS, '0', '*', ValidationRules({})),
            sequenceConstraints(this, SBOL_SEQUENCE_CONSTRAINTS, '0', '*', ValidationRules({}))
            {
                hidden_properties.push_back(SBOL_SEQUENCE);
            };
        
        /// The types property is a REQUIRED set of URIs that specifies the category of biochemical or physical entity (for example DNA, protein, or small molecule) that a ComponentDefinition object abstracts for the purpose of engineering design.  The types property of every ComponentDefinition MUST contain one or more URIs that MUST identify terms from appropriate ontologies, such as the BioPAX ontology or the ontology of Chemical Entities of Biological Interest. See the table below for examples.
        /// | Type              | URI for BioPAX Term                                           | LibSBOL symbol        |
        /// | :---------------- | :------------------------------------------------------------ | :-------------------- |
        /// | DNA               | http://www.biopax.org/release/biopax-level3.owl#DnaRegion     | BIOPAX_DNA            |
        /// | RNA               | http://www.biopax.org/release/biopax-level3.owl#RnaRegion     | BIOPAX_RNA            |
        /// | Protein           | http://www.biopax.org/release/biopax-level3.owl#Protein       | BIOPAX_PROTEIN        |
        /// | Small Molecule    | http://www.biopax.org/release/biopax-level3.owl#SmallMolecule | BIOPAX_SMALL_MOLECULE |
        /// | Complex           | http://www.biopax.org/release/biopax-level3.owl#Complex       | BIOPAX_COMPLEX        |
        URIProperty types;
        
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
        URIProperty roles;
        
        /// The components property is OPTIONAL and MAY specify a set of Component objects that are contained by the ComponentDefinition. The components properties of ComponentDefinition objects can be used to construct a hierarchy of Component and ComponentDefinition objects. If a ComponentDefinition in such a hierarchy refers to one or more Sequence objects, and there exist ComponentDefinition objects lower in the hierarchy that refer to Sequence objects with the same encoding, then the elements properties of these Sequence objects SHOULD be consistent with each other, such that well-defined mappings exist from the “lower level” elements to the “higher level” elements. This mapping is also subject to any restrictions on the positions of the Component objects in the hierarchy that are imposed by the SequenceAnnotation or SequenceConstraint objects contained by the ComponentDefinition objects in the hierarchy.  The set of relations between Component and ComponentDefinition objects is strictly acyclic.
        OwnedObject<Component> components;
        
        /// The sequences property is OPTIONAL and MAY include a URI that refer to a Sequence object. The referenced object defines the primary structure of the ComponentDefinition.
        ReferencedObject sequences;
        
        OwnedObject<Sequence> sequence;
        
        /// The sequenceAnnotations property is OPTIONAL and MAY contain a set of SequenceAnnotation objects. Each SequenceAnnotation specifies and describes a potentially discontiguous region on the Sequence objects referred to by the ComponentDefinition.
        OwnedObject<SequenceAnnotation> sequenceAnnotations;
        
        /// The sequenceConstraints property is OPTIONAL and MAY contain a set of SequenceConstraint objects. These objects describe any restrictions on the relative, sequence-based positions and/or orientations of the Component objects contained by the ComponentDefinition. For example, the ComponentDefinition of a gene might specify that the position of its promoter Component precedes that of its CDS Component. This is particularly useful when a ComponentDefinition lacks a Sequence and therefore cannot specify the precise, sequence-based positions of its Component objects using SequenceAnnotation objects.
		OwnedObject<SequenceConstraint> sequenceConstraints;
        
        /// Assembles ComponentDefinitions into an abstraction hierarchy. The resulting data structure is a partial design, still lacking a primary structure or explicit sequence. To form a primary structure out of the ComponentDefinitions, call linearize after calling assemble. To fully realize the target sequence, use Sequence::assemble().
        /// @param list_of_components A list of subcomponents that will compose this ComponentDefinition
        /// @param assembly_standard An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how components are composed and the final target sequence
        void assemble(std::vector<ComponentDefinition*>& list_of_components, std::string assembly_standard = "");

        /// Assembles ComponentDefinitions into an abstraction hierarchy. The resulting data structure is a partial design, still lacking a primary structure or explicit sequence. To form a primary structure out of the ComponentDefinitions, call linearize after calling assemble. To fully realize the target sequence, use Sequence::assemble().
        /// @param list_of_components A list of subcomponents that will compose this ComponentDefinition
        /// @param doc The Document to which the assembled ComponentDefinitions will be added
        /// @param assembly_standard An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how components are composed and the final target sequence
        void assemble(std::vector<ComponentDefinition*>& list_of_components, Document& doc, std::string assembly_standard = "");

        /// Assembles ComponentDefinition into a linear primary structure. The resulting data structure is a partial design, still lacking an explicit sequence. To fully realize the target sequence, use Sequence::assemble().
        /// @param primary_structure A list of URIs for the constituent ComponentDefinitions, or displayIds if using SBOL-compliant URIs
        /// @param assembly_standard An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how components are composed and the final target sequence
        void assemblePrimaryStructure(std::vector<std::string>& primary_structure, std::string assembly_standard = "");
        
        /// Assembles ComponentDefinition into a linear primary structure. The resulting data structure is a partial design, still lacking an explicit sequence. To fully realize the target sequence, use Sequence::assemble().
        /// @param list_of_components A list of subcomponents that will compose this ComponentDefinition
        /// @param assembly_standard An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how components are composed and the final target sequence
        void assemblePrimaryStructure(std::vector<ComponentDefinition*>& primary_structure, std::string assembly_standard = "");
        
        /// Assembles ComponentDefinition into a linear primary structure. The resulting data structure is a partial design, still lacking an explicit sequence. To fully realize the target sequence, use Sequence::assemble().
        /// @param list_of_components A list of subcomponents that will compose this ComponentDefinition
        /// @param doc The Document to which the assembled ComponentDefinitions will be added
        /// @param assembly_standard An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how components are composed and the final target sequence
        void assemblePrimaryStructure(std::vector<ComponentDefinition*>& primary_structure, Document& doc, std::string assembly_standard = "");

        /// Assembles ComponentDefinitions into an abstraction hierarchy. The resulting data structure is a partial design, still lacking a primary structure or explicit sequence. To form a primary structure out of the ComponentDefinitions, call linearize after calling assemble. To fully realize the target sequence, use Sequence::assemble().
        /// @param list_of_uris A list of URIs for the constituent ComponentDefinitions, or displayIds if using SBOL-compliant URIs
        /// @param assembly_standard An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how components are composed and the final target sequence
        void assemble(std::vector<std::string>& list_of_uris, std::string assembly_standard = "");

        /// Compiles an abstraction hierarchy of ComponentDefinitions into a nucleotide sequence. If no Sequence object is associated with this ComponentDefinition, one will be automatically instantiated
        std::string compile();

        /// Assemble a parent ComponentDefinition's Sequence from its subcomponent Sequences
        /// @param composite_sequence A recursive parameter, use default value
        /// @return The assembled parent sequence
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
        
        /// Perform an operation on every Component in a structurally-linked hierarchy of Components by applying a callback function. If no callback is specified, the default behavior is to return a pointer list of each Component in the hierarchy.
        /// @param callback_fun A pointer to a callback function with signature void callback_fn(ComponentDefinition *, void *).
        /// @param user_data Arbitrary user data which can be passed in and out of the callback as an argument or return value.
        /// @return Returns a flat list of pointers to all Components in the hierarchy.
        std::vector<ComponentDefinition*> applyToComponentHierarchy(void (*callback_fn)(ComponentDefinition *, void *) = NULL, void * user_data = NULL);

        /// Get the primary sequence of a design in terms of its sequentially ordered Components
        std::vector<ComponentDefinition*> getPrimaryStructure();

        /// Insert a Component downstream of another in a primary sequence, shifting any adjacent Components dowstream as well
        /// @param target The target Component will be upstream of the insert Component after this operation.
        /// @param insert The insert Component is inserted downstream of the target Component.
        void insertDownstream(Component& target, ComponentDefinition& insert);
        
        /// Insert a Component upstream of another in a primary sequence, shifting any adjacent Components upstream as well
        /// @param target The target Component will be downstream of the insert Component after this operation.
        /// @param insert The insert Component is inserted upstream of the target Component.
        void insertUpstream(Component& target, ComponentDefinition& insert);

        /// This may be a useful method when building up SBOL representations of natural DNA sequences. For example it is often necessary to specify components that are assumed to have no meaningful role in the design, but are nevertheless important to fill in regions of sequence. This method autoconstructs a ComponentDefinition and Sequence object to create an arbitrary flanking sequence around design Components. The new ComponentDefinition will have Sequence Ontology type of flanking_region or SO:0000239
        /// @param target The new flanking sequence will be placed upstream of the target
        /// @param elements The primary sequence elements will be assigned to the autoconstructed Sequence object. The encoding is inferred
        void addUpstreamFlank(Component& target, std::string elements);
        
        /// This may be a useful method when building up SBOL representations of natural DNA sequences. For example it is often necessary to specify components that are assumed to have no meaningful role in the design, but are nevertheless important to fill in regions of sequence. This method autoconstructs a ComponentDefinition and Sequence object to create an arbitrary flanking sequence around design Components. The new ComponentDefinition will have Sequence Ontology type of flanking_sequence.
        /// @param target The new flanking sequence will be placed downstream of the target
        /// @param elements The primary sequence elements will be assigned to the autoconstructed Sequence object. The encoding is inferred
        void addDownstreamFlank(Component& target, std::string elements);

        /// Use this diagnose an irregular design. Recursively checks if this ComponentDefinition defines a SequenceAnnotation and Range for every Sequence. Regularity is more stringent than completeness. A design must be complete to be regular.
        /// @param msg A message for diagnosing the irregularity, if any is found. The message is returned through an argument of type std::string&
        /// @return true if the abstraction hierarchy is regular, false otherwise.
        bool isRegular(std::string &msg);

        /// Recursively checks if this ComponentDefinition defines a SequenceAnnotation and Range for every Sequence. Regularity is more stringent than completeness. A design must be complete to be regular. If the Component is irregular, diagnose with isRegular(std::string &msg)
        /// @return true if the abstraction hierarchy is regular, false otherwise.
        bool isRegular();

        /// Use this diagnose an incomplete design. Recursively checks if this ComponentDefinition defines a SequenceAnnotation and Range for every Sequence. Completeness does not guarantee regularity
        /// @param msg A message for diagnosing the irregularity, if any is found. The message is returned through an argument of type std::string&
        /// @return true if the abstraction hierarchy is regular, false otherwise.
        bool isComplete(std::string &msg);
        
        /// Recursively verifies that the parent Document contains a ComponentDefinition and Sequence for each and every ComponentDefinition in the abstraction hierarchy. If a ComponentDefinition is not complete, some objects are missing from the Document or externally linked. Diagnose with isComplete(std::string &msg)
        /// @return true if the abstraction hierarchy is complete, false otherwise.
        bool isComplete();


        /// Instantiates a Component for every SequenceAnnotation. When converting from a flat GenBank file to a flat SBOL file, the result is a ComponentDefinition with SequenceAnnotations. This method will convert the flat SBOL file into hierarchical SBOL.
        void disassemble(int range_start = 1);
        
        void linearize(std::vector<ComponentDefinition*> list_of_components = {});
        
        void linearize(std::vector<std::string> list_of_uris);
        
        ComponentDefinition& build();
        
        std::vector<SequenceAnnotation*> sortSequenceAnnotations();

        /// A convenience method that assigns a component to participate in a biochemical reaction.  Behind the scenes, it auto-constructs a FunctionalComponent for this ComponentDefinition and assigns it to a Participation
        /// @param species A Participation object (ie, participant species in a biochemical Interaction).
        void participate(Participation& species);
        
        virtual ~ComponentDefinition() {  };
        
	};
}

#endif