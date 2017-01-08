/// @file constants.h
/// Users of libSBOL may find in this file useful and important symbols corresponding to commonly used ontological terms from the Sequence Ontology, Systems Biology Ontology, BioPAX, etc. A number of flags internal to the SBOL standard are also defined here.  Finally, for developers and maintains of libSBOL, this file contains important URIs in the SBOL namespace, some of which can be used to control the appearance of the RDF/XML serialization.
#ifndef CONSTANTS_INCLUDED
#define CONSTANTS_INCLUDED

// All SBOL objects will be created in the default namespace, unless otherwise specified
#define DEFAULT_NS "http://examples.org/"

// The URIs defined here determine the appearance of serialized RDF/XML nodes.  Change these URIs to change the appearance of an SBOL class or property name
#define SBOL_URI "http://sbols.org/v2"  ///< Namespace for the SBOL standard.
#define RDF_URI "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define PURL_URI "http://purl.org/dc/terms/"
#define PROV_URI "http://www.w3.org/ns/prov"

// rdf nodes used in SBOL
#define NODENAME_ABOUT    "rdf:about"
#define NODENAME_RESOURCE "rdf:resource"

#define VERSION_STRING "1.0.0"

/* URIs for SBOL objects */
#define SBOL_DOCUMENT SBOL_URI "#Document"
#define SBOL_IDENTIFIED SBOL_URI "#Identified"
#define SBOL_DOCUMENTED SBOL_URI "#Documented"
#define SBOL_TOP_LEVEL SBOL_URI "#TopLevel"
#define SBOL_GENERIC_TOP_LEVEL SBOL_URI "#GenericTopLevel"
#define SBOL_SEQUENCE_ANNOTATION SBOL_URI "#SequenceAnnotation"
#define SBOL_COMPONENT SBOL_URI "#Component"
#define SBOL_FUNCTIONAL_COMPONENT SBOL_URI "#FunctionalComponent"
#define SBOL_COMPONENT_DEFINITION SBOL_URI "#ComponentDefinition"
#define SBOL_SEQUENCE SBOL_URI "#Sequence"
#define SBOL_MODULE_DEFINITION SBOL_URI "#ModuleDefinition"
#define SBOL_MODULE SBOL_URI "#Module"
#define SBOL_MODEL SBOL_URI "#Model"
#define SBOL_MAPS_TO SBOL_URI "#MapsTo"
#define SBOL_INTERACTION SBOL_URI "#Interaction"
#define SBOL_PARTICIPATION SBOL_URI "#Participation"
#define SBOL_SEQUENCE_CONSTRAINT SBOL_URI "#SequenceConstraint"
#define SBOL_LOCATION SBOL_URI "#Location"
#define SBOL_DOCUMENT SBOL_URI "#Document"
#define SBOL_RANGE SBOL_URI "#Range"
#define SBOL_CUT SBOL_URI "#Cut"
#define SBOL_COLLECTION SBOL_URI "#Collection"
#define SBOL_GENERIC_LOCATION SBOL_URI "#GenericLocation"
#define UNDEFINED SBOL_URI "#Undefined"

/* URIs for SBOL Properties */
#define SBOL_IDENTITY SBOL_URI "#identity"
#define SBOL_PERSISTENT_IDENTITY SBOL_URI "#persistentIdentity"
#define SBOL_VERSION SBOL_URI "#version"
#define SBOL_DISPLAY_ID  SBOL_URI "#displayId"
#define SBOL_NAME PURL_URI "title"
#define SBOL_DESCRIPTION PURL_URI "description"
#define SBOL_TYPES SBOL_URI "#type"
#define SBOL_START SBOL_URI "#start"
#define SBOL_END SBOL_URI "#end"
#define SBOL_SEQUENCE_ANNOTATIONS SBOL_URI "#sequenceAnnotation"
#define SBOL_COMPONENTS SBOL_URI "#component"
#define SBOL_COMPONENT_PROPERTY SBOL_URI "#component"
#define SBOL_ROLES SBOL_URI "#role"
#define SBOL_ELEMENTS SBOL_URI "#elements"
#define SBOL_ENCODING SBOL_URI "#encoding"
#define SBOL_SEQUENCE_PROPERTY SBOL_URI "#sequence"
#define SBOL_WAS_DERIVED_FROM PROV_URI "#wasDerivedFrom"
#define SBOL_DEFINITION SBOL_URI "#definition"
#define SBOL_ACCESS SBOL_URI "#access"
#define SBOL_DIRECTION SBOL_URI "#direction"
#define SBOL_MODELS SBOL_URI "#model"
#define SBOL_MODULES SBOL_URI "#module"
#define SBOL_FUNCTIONAL_COMPONENTS SBOL_URI "#functionalComponent"
#define SBOL_INTERACTIONS SBOL_URI "#interaction"
#define SBOL_MAPS_TOS SBOL_URI "#mapsTo"
#define SBOL_PARTICIPATIONS SBOL_URI "#participation"
#define SBOL_PARTICIPANT SBOL_URI "#participant"
#define SBOL_LOCAL SBOL_URI "#local"
#define SBOL_REMOTE SBOL_URI "#remote"
#define SBOL_REFINEMENT SBOL_URI "#refinement"
#define SBOL_SOURCE SBOL_URI "#source"
#define SBOL_LANGUAGE SBOL_URI "#language"
#define SBOL_FRAMEWORK SBOL_URI "#framework"
#define SBOL_SEQUENCE_CONSTRAINTS SBOL_URI "#sequenceConstraint"
#define SBOL_SUBJECT SBOL_URI "#subject"
#define SBOL_OBJECT SBOL_URI "#object"
#define SBOL_RESTRICTION SBOL_URI "#restriction"
#define SBOL_ORIENTATION SBOL_URI "#orientation"
#define SBOL_LOCATIONS SBOL_URI "#location"
#define SBOL_ROLE_INTEGRATION SBOL_URI "#roleIntegration"
#define SBOL_MEMBERS SBOL_URI "#member"
#define SBOL_AT SBOL_URI "#at"

/* SBOL internal ontologies */
#define SBOL_ACCESS_PRIVATE SBOL_URI "#private"  ///< Option for Component::access or FunctionalComponent::access property
#define SBOL_ACCESS_PUBLIC SBOL_URI "#public"    ///< Option for Component::access or FunctionalComponent::access property
#define SBOL_DIRECTION_IN SBOL_URI "#in"         ///< Option for FunctionalComponent::access property
#define SBOL_DIRECTION_OUT SBOL_URI "#out"       ///< Option for FunctionalComponent::direction property
#define SBOL_DIRECTION_IN_OUT SBOL_URI "#inout"  ///< Option for FunctionalComponent::direction property
#define SBOL_DIRECTION_NONE SBOL_URI "#none"     ///< Option for FunctionalComponent::direction property
#define SBOL_RESTRICTION_PRECEDES SBOL_URI "#precedes"                     ///< Option for SequenceConstraint::restriction property
#define SBOL_RESTRICTION_SAME_ORIENTATION_AS "#sameOrientationAs"          ///< Option for SequenceConstraint::restriction property
#define SBOL_RESTRICTION_OPPOSITE_ORIENTATION_AS "#oppositeOrientationAs"  ///< Option for SequenceConstraint::restriction property
#define SBOL_ENCODING_IUPAC "http://www.chem.qmul.ac.uk/iubmb/misc/naseq.html"    ///< Option for Sequence::encoding property
#define SBOL_ENCODING_IUPAC_PROTEIN "http://www.chem.qmul.ac.uk/iupac/AminoAcid/" ///< Option for Sequence::encoding property
#define SBOL_ENCODING_SMILES "http://www.opensmiles.org/opensmiles.html"          ///< Option for Sequence::encoding property
#define SBOL_ORIENTATION_INLINE SBOL_URI "#inline"                        ///< Option for Location::orientation property
#define SBOL_ORIENTATION_REVERSE_COMPLEMENT SBOL_URI "#reverseComplement" ///< Option for Location::orientation property
#define SBOL_REFINEMENT_USE_REMOTE SBOL_URI "#useRemote" ///< Option for FunctionalComponent::refinement property
#define SBOL_REFINEMENT_USE_LOCAL SBOL_URI "#useLocal"   ///< Option for FunctionalComponent::refinement property
#define SBOL_REFINEMENT_VERIFY_IDENTICAL SBOL_URI "#verifyIdentical" ///< Option for MapsTo::refinement property
#define SBOL_REFINEMENT_MERGE SBOL_URI "#merge"                      ///< Option for MapsTo::refinement property
#define SBOL_ROLE_INTEGRATION_MERGE SBOL_URI "#mergeRoles"           ///< Option for SequenceAnnotation::roleIntegration or Component::roleIntegration property
#define SBOL_ROLE_INTEGRATION_OVERRIDE SBOL_URI "#overrideRoles"     ///< Option for SequenceAnnotation::roleIntegration or Component::roleIntegration property

/* Systems Biology Ontology */
/* Interaction.types */
#define SBO "http://identifiers.org/biomodels.sbo/SBO:"  ///< Namespace for Systems Biology Ontology (SBO) terms
#define SBO_INTERACTION SBO "0000343"                    ///< An SBO term and possible value for an Interaction::type property
#define SBO_INHIBITION SBO "0000169"                     ///< An SBO term and possible value for an Interaction::type property
#define SBO_GENETIC_PRODUCTION SBO "0000589"             ///< An SBO term and possible value for an Interaction::type property
#define SBO_NONCOVALENT_BINDING SBO "0000177"            ///< An SBO term and possible value for an Interaction::type property
#define SBO_STIMULATION SBO "0000170"                    ///< An SBO term and possible value for an Interaction::type property
#define SBO_DEGRADATION SBO "0000179"                    ///< An SBO term and possible value for an Interaction::type property
#define SBO_CONTROL SBO "0000168"                        ///< An SBO term and possible value for an Interaction::type property
#define SBO_BIOCHEMICAL_REACTION SBO "0000176"           ///< An SBO term and possible value for an Interaction::type property

/* Participant.roles */
#define SBO_PROMOTER SBO "0000598"              ///< An SBO term and possible value for an Participant::role property
#define SBO_GENE SBO "0000243"                  ///< An SBO term and possible value for an Participant::role property
#define SBO_INHIBITOR SBO "0000020"            ///< An SBO term and possible value for an Participant::role property
#define SBO_STIMULATOR SBO "0000459"           ///< An SBO term and possible value for an Participant::role property
#define SBO_REACTANT SBO "0000010"             ///< An SBO term and possible value for an Participant::role property
#define SBO_PRODUCT SBO "0000011"              ///< An SBO term and possible value for an Participant::role property
#define SBO_LIGAND SBO "0000280"               ///< An SBO term and possible value for an Participant::role property
#define SBO_NONCOVALENT_COMPLEX SBO "0000253"  ///< An SBO term and possible value for an Participant::role property
#define SBO_BINDING_SITE "0000494"             ///< An SBO term and possible value for an Participant::role property

/* URIs for common Sequence Ontology terms */
#define SO "http://identifiers.org/so/SO:" ///< Namespace for Sequence Ontology (SO) terms
#define SO_MISC SO "0000001"                  ///< An SO term and possible value for ComponentDefinition::role property
#define SO_PROMOTER SO "0000167"           ///< An SO term and possible value for ComponentDefinition::role property
#define SO_CDS SO "0000316"                ///< An SO term and possible value for ComponentDefinition::role property
#define SO_RBS SO "0000139"                ///< An SO term and possible value for ComponentDefinition::role property
#define SO_TERMINATOR SO "0000141"         ///< An SO term and possible value for ComponentDefinition::role property
#define SO_SGRNA SO "0001998"

/* BioPAX is used to indicate macromolecular and molecular types */
/// DNA
#define BIOPAX_DNA "http://www.biopax.org/release/biopax-level3.owl#DnaRegion"  ///< A BioPax term and possible value for ComponentDefinition::type property
/// RNA
#define BIOPAX_RNA "http://www.biopax.org/release/biopax-level3.owl#RnaRegion"  ///< A BioPax term and possible value for ComponentDefinition::type property
/// PROTEIN
#define BIOPAX_PROTEIN "http://www.biopax.org/release/biopax-level3.owl#Protein"  ///< A BioPax term and possible value for ComponentDefinition::type property
/// SMALL_MOLECULE
#define BIOPAX_SMALL_MOLECULE "http://www.biopax.org/release/biopax-level3.owl#SmallMolecule"  ///< A BioPax term and possible value for ComponentDefinition::type property
/// COMPLEX
#define BIOPAX_COMPLEX "http://www.biopax.org/release/biopax-level3.owl#Complex"  ///< A BioPax term and possible value for ComponentDefinition::type property

/* EDAM ontology is used for Model.languages */
#define EDAM_SBML "http://identifiers.org/edam/format_2585"   ///< An EDAM ontology term and option for Model::language
#define EDAM_CELLML "http://identifiers.org/edam/format_3240" ///< An EDAM ontology term and option for Model::language
#define EDAM_BIOPAX "http://identifiers.org/edam/format_3156" ///< An EDAM ontology term and option for Model::language

/* Model.frameworks */
#define SBO_CONTINUOUS SBO "0000062"  ///< SBO term and option for Model::framework
#define SBO_DISCRETE SBO "0000063"    ///< SBO term and option for Model::framework


#endif