///////////////////////////////////////////////////////////
/// @file
/// Contains the DNAComponent struct, as well
/// as functions for operating on it.
///////////////////////////////////////////////////////////



#ifndef SBOL_DNACOMPONENT_HEADER
#define SBOL_DNACOMPONENT_HEADER

#include "constants.h"
#include "prototypes.h"


/// @defgroup DC DNA Component
/// @{
/// @struct _DNAComponent
/// @brief Implements the SBOL Core DNAComponent object.
/// @var _DNAComponent::doc
/// @var _DNAComponent::base
/// @var _DNAComponent::dnaSequence
/// @var _DNAComponent::annotations
/// @var _DNAComponent::type
///
struct _DNAComponent {
	Document* doc;             ///< parent Document
	SBOLCompoundObject* base;  ///< uri, displayID, name, description
	DNASequence* dnaSequence;  ///< sequence
	PointerArray* annotations; ///< array of SequenceAnnotations
    TypeProperty* type;        ///< type
};

/// @name Methods
/// @{

/// Create an empty DNAComponent.
SBOLAPIEXPORTS DNAComponent* createDNAComponent(Document* doc, const char* uri);

/// Delete a DNAComponent.
/// This doesn't delete any of the other structs
/// it references.
SBOLAPIEXPORTS void deleteDNAComponent(DNAComponent* com);

/// Clone a DNAComponent object
SBOLAPIEXPORTS DNAComponent* copyDNAComponent(const DNAComponent* com, char* id_modifier);

/// Get the number of SequenceAnnotations for a DNAComponent.
SBOLAPIEXPORTS int getNumSequenceAnnotationsFor(const DNAComponent* com);

/// Get the Nth SequenceAnnotation for a DNAComponent.
SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotationFor(const DNAComponent* com, int n);

/// Get the uri of a DNAComponent.
/// Gotcha: this is different from both name and displayID.
SBOLAPIEXPORTS char* getDNAComponentURI(const DNAComponent* com);

/// Get the displayID of a DNAComponent.
/// Gotcha: this is different from both uri and name.
SBOLAPIEXPORTS char* getDNAComponentDisplayID(const DNAComponent* com);

/// Get the name of a DNAComponent.
/// Gotcha: this is different from both uri and displayID.
SBOLAPIEXPORTS char* getDNAComponentName(const DNAComponent* com);

/// Get the description of a DNAComponent.
SBOLAPIEXPORTS char* getDNAComponentDescription(const DNAComponent* com);

/// Get the DNASequence of a DNAComponent.
/// Gotcha: DNA, not Dna
SBOLAPIEXPORTS DNASequence* getDNAComponentSequence(DNAComponent* com);

/// Get the type of a DNAComponent
SBOLAPIEXPORTS char* getDNAComponentType(const DNAComponent* com);

/// Set the uri of a DNAComponent.
/// Gotcha: this is different from both name and displayID.
SBOLAPIEXPORTS void setDNAComponentURI(DNAComponent* com, const char* uri);

/// Set the displayID of a DNAComponent.
/// Gotcha: this is different from both uri and name.
SBOLAPIEXPORTS void setDNAComponentDisplayID(DNAComponent* com, const char* id);

/// Set the name of a DNAComponent.
/// Gotcha: this is different from both uri and displayID.
SBOLAPIEXPORTS void setDNAComponentName(DNAComponent* com, const char* name);

/// Set the description of a DNAComponent.
SBOLAPIEXPORTS void setDNAComponentDescription(DNAComponent* com, const char* desc);

/// Set the DNASequence of a DNAComponent.
/// Gotcha: DNA, not Dna
/// @todo how should this handle docs?
SBOLAPIEXPORTS void setDNAComponentSequence(DNAComponent* com, DNASequence* seq);

/// Set the type of a DNAComponent
SBOLAPIEXPORTS void setDNAComponentType(DNAComponent* com, const char* uri);

/// Add a SequenceAnnotation to a DNAComponent.
/// @todo where should this go? here, sequenceannotation.h, sbol.h?
/// @todo how should this handle docs?
SBOLAPIEXPORTS void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann);

/// Delete a SequenceAnnotation from a DNAComponent's list of annotations.
/// @todo where should this go? here, sequenceannotation.h, sbol.h?
/// @todo how should this handle docs?
SBOLAPIEXPORTS void removeSequenceAnnotationFromDNAComponent(DNAComponent* com, SequenceAnnotation* ann);

/// Print an outline of a DNAComponent to stdout.
SBOLAPIEXPORTS void printDNAComponent(const DNAComponent* com, int tabs);

/// Retrieve extra information about a DNAComponent stored as structured XML
SBOLAPIEXPORTS xmlNode* getNthXMLAnnotationFromDNAComponent(DNAComponent *com, int index);

/// Annotate this DNAComponent with structured XML
SBOLAPIEXPORTS void addXMLAnnotationToDNAComponent(DNAComponent* com, xmlNode *node);

/// Remove XML annotation from DNAComponent
SBOLAPIEXPORTS xmlNode* removeXMLAnnotationFromDNAComponent(DNAComponent *com, int index);

/// @}
/// @}

#endif
