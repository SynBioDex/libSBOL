////////////////////////////////////////////////////////////
/// @file
/// 
/// Defines the Document struct, as well as
/// functions for operating on it.
////////////////////////////////////////////////////////////

#ifndef SBOL_DOCUMENT_HEADER
#define SBOL_DOCUMENT_HEADER

#include <libxml/tree.h>
#include "sbol.h"

/// @todo Objects should be able to belong to multiple documents
/// @defgroup Doc Document
/// @{
/// @struct _Document
/// @brief Represents an SBOL document that can be read from or written to a file.
/// @details It also holds pointers to all the SBOL objects in the document,
/// so it can be used for iterating through all the objects of a certain kind,
/// retrieving the object with a certain URI, checking the type of a pointer, etc.
/// Deleting a Document also deletes the SBOL objects it contains.
/// Each SBOL object must be associated with a document, for two main reasons:
/// to ensure that its URI is unique, and to make memory management simpler.
/// @var _Document::sequences
/// @var _Document::annotations
/// @var _Document::components
/// @var _Document::collections
///

struct _SBOLDocument{
	const char* __class;
	PointerArray* top_level_objects;
	xmlDoc* xml_doc;
};

/// @name Methods
/// @{
/// Create an empty Document.
SBOLAPIEXPORTS SBOLDocument* createSBOLDocument();

/// Delete a Document. This also deletes all the
/// SBOL objects contained in the Document.
SBOLAPIEXPORTS void deleteSBOLDocument(SBOLDocument* doc);

SBOLAPIEXPORTS void registerTopLevelObject(SBOLDocument* doc, TopLevelObject* obj);

SBOLAPIEXPORTS void removeTopLevelObject(SBOLDocument* doc, TopLevelObject* obj);

SBOLAPIEXPORTS void deleteSBOLDocument(SBOLDocument* doc);

SBOLAPIEXPORTS const char* getSBOLType(void* obj);

SBOLAPIEXPORTS int isSBOLType(SBOL_class_defn, obj);

SBOLAPIEXPORTS void* addToDocument(SBOLDocument* doc, void* object);

SBOLAPIEXPORTS int isTopLevelObject(void* obj);

SBOLAPIEXPORTS void* super(void* sub, void* super);

//// Delete a Sequence from a Document's array of sequences
//void removeDNASequence(Document* doc, DNASequence* seq);
//
//// Delete an Annotation from a Document's array of annotations
//void removeSequenceAnnotation(Document* doc, SequenceAnnotation* ann);
//
//// Delete a Component from a Document's array of components
//void removeDNAComponent(Document* doc, DNAComponent* com);
//
//// Delete a Collection from a Document's array of collections
//void removeCollection(Document* doc, Collection* col);
//
///// Find out the total number of SBOL objects in a Document.
//SBOLAPIEXPORTS int getNumSBOLObjects(Document* doc);
//
///// Get the total number of DNASequences in a Document.
//SBOLAPIEXPORTS int getNumDNASequences(const Document* doc);
//
///// Get the total number of SequenceAnnotations in a Document.
///// Useful as a loop condition.
//SBOLAPIEXPORTS int getNumSequenceAnnotations(Document* doc);
//
///// Get the total number of DNAComponents in a Document.
///// Useful as a loop condition.
//SBOLAPIEXPORTS int getNumDNAComponents(const Document* doc);
//
///// Get the total number of Collections in a Document.
///// Useful as a loop condition.
//SBOLAPIEXPORTS int getNumCollections(Document* doc);
//
///// Find out whether a pointer points to a DNASequence in this Document.
//SBOLAPIEXPORTS int isDNASequence(const Document* doc, const void* pointer);
//
///// Find out whether a pointer points to a SequenceAnnotation in this Document.
//SBOLAPIEXPORTS int isSequenceAnnotation(const Document* doc, const void* pointer);
//
///// Find out whether this pointer points to a DNAComponent in this Document.
//SBOLAPIEXPORTS int isDNAComponent(const Document* doc, const void* pointer);
//
///// Find out whether this pointer points to a Collection in this Document.
//SBOLAPIEXPORTS int isCollection(Document* doc, const void* pointer);
//
///// Find out whether there's a DNASequence with this URI in this Document.
//SBOLAPIEXPORTS int isDNASequenceURI(Document* doc, const char* uri);
//
///// Find out whether this URI is associated with a SequenceAnnotation in this Document.
//SBOLAPIEXPORTS int isSequenceAnnotationURI(Document* doc, const char* uri);
//
///// Find out if there's a DNAComponent with this uri in this Document.
//SBOLAPIEXPORTS int isDNAComponentURI(Document* doc, const char* uri);
//
///// Find out if there's a Collection with this uri in this Document.
//SBOLAPIEXPORTS int isCollectionURI(Document* doc, const char* uri);
//
///// Find out whether there's an SBOL object with this URI in this Document.
///// Useful for avoiding duplicates.
//SBOLAPIEXPORTS int isSBOLObjectURI(Document* doc, const char* uri);
//
///// Get the DNASequence associated with this URI in this Document.
///// Returns NULL on failure.
//SBOLAPIEXPORTS DNASequence* getDNASequence(Document* doc, const char* uri);
//
///// Get the SequenceAnnotation associated with this URI in this Document.
///// Returns NULL on failure.
//SBOLAPIEXPORTS SequenceAnnotation* getSequenceAnnotation(Document* doc, const char* uri);
//
///// Get the DNAComponent associated with this uri in this Document.
///// Returns NULL on failure.
//SBOLAPIEXPORTS DNAComponent* getDNAComponent(Document* doc, const char* uri);
//
///// Get the Collection associated with this uri in this Document.
///// Returns NULL on failure.
//SBOLAPIEXPORTS Collection* getCollection(Document* doc, const char* uri);
//
///// Get the Nth DNASequnce in a Document.
///// Returns NULL on failure.
//SBOLAPIEXPORTS DNASequence* getNthDNASequence(Document* doc, int n);
//
///// Get the Nth SequenceAnnotation in a Document.
///// Useful for iterating through them.
//SBOLAPIEXPORTS SequenceAnnotation* getNthSequenceAnnotation(Document* doc, int n);
//
///// Get the Nth DNAComponent in a Document.
///// Useful for iterating over all of them.
//SBOLAPIEXPORTS DNAComponent* getNthDNAComponent(Document* doc, int n);
//
///// Get the Nth Collection in a Document.
///// Useful for iterating over all of them.
//SBOLAPIEXPORTS Collection* getNthCollection(Document* doc, int n);
//
///// Print all the SBOL objects in a Document to stdout.
///// Mainly for debugging.
//SBOLAPIEXPORTS void printDocument(Document* doc);

/// @}
/// @}
#endif
