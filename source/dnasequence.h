///////////////////////////////////////////////////////////
/// @file
/// Defines the DNASequence struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_DNASEQUENCE_HEADER
#define SBOL_DNASEQUENCE_HEADER

#include "constants.h"
#include "prototypes.h"

#define NUCLEOTIDES_TO_PRINT "50" ///< Cutoff for how much of a long sequence to print.

/// @defgroup Seq DNA Sequence
/// @{
/// @struct _DNASequence
/// @brief Implements the SBOL Core DNASequence object.
/// @var _DNASequence::doc
/// @var _DNASequence::base
/// @var _DNASequence::nucleotides
///
struct _DNASequence {
	Document* doc;                    ///< parent Document
	SBOLObject* base;                 ///< uri
	NucleotidesProperty* nucleotides; ///< sequence
};

/// @name Methods
/// @{

/// Create an empty DNASequence.
SBOLAPIEXPORTS DNASequence* createDNASequence(Document* doc, const char* uri);

/// Delete a DNASequence.
/// Since DNASequences are self-contained,
/// no other freeing should be needed
SBOLAPIEXPORTS void deleteDNASequence(DNASequence* seq);

/// Clone a DNASequence object
SBOLAPIEXPORTS DNASequence* copyDNASequence(const DNASequence* seq, char* id_modifier);

/// Get a copy of the nucleotides contained in this DNASequence.
/// @return A string that needs to be freed.
/// @todo rename to getDNASequenceNucleotides?
SBOLAPIEXPORTS char* getDNASequenceNucleotides(const DNASequence* seq);

/// Copy a string of nucleotides into this DNASequence.
/// So far, no validation is done to ensure that these are valid nucleotides.
/// @todo rename to setDNASequenceNucleotides?
SBOLAPIEXPORTS void setDNASequenceNucleotides(DNASequence* seq, const char* nucleotides);

/// Get the URI of a DNASequence.
/// Returns NULL on failure.
SBOLAPIEXPORTS char* getDNASequenceURI(const DNASequence* seq);

/// Set the URI of a DNASequence.
SBOLAPIEXPORTS void setDNASequenceURI(DNASequence* seq, const char* uri);

/// Print a DNASequence to stdout.
/// Mainly for debugging.
SBOLAPIEXPORTS void printDNASequence(const DNASequence* seq, int tabs);

/// Retrieve extra information about a DNAComponent stored as structured XML
SBOLAPIEXPORTS xmlNode* getNthXMLAnnotationFromDNASequence(DNASequence *seq, int index);

/// Annotate this DNAComponent with structured XML
SBOLAPIEXPORTS void addXMLAnnotationToDNASequence(DNASequence *seq, xmlNode *node);

/// Remove XML annotation from DNAComponent
SBOLAPIEXPORTS xmlNode* removeXMLAnnotationFromDNASequence(DNASequence *seq, int index);

/// @}
/// @}

#endif
