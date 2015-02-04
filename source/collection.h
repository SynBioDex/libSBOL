///////////////////////////////////////////////////////////
/// @file
/// Defines the Collection struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_COLLECTION_HEADER
#define SBOL_COLLECTION_HEADER

#include "constants.h"
#include "prototypes.h"

/// @defgroup Col Collection
/// @{
/// @struct _Collection
/// @brief Implements the SBOL Core Collection object.
/// @var _Collection::doc
/// @var _Collection::base
/// @var _Collection::components
///
struct _Collection {
	Document* doc;             ///< parent Document
	SBOLCompoundObject* base;  ///< uri, displayID, name, description
	PointerArray* components;  ///< array of DNAComponents
};
/// @name Methods
/// @{

/// Create an empty Collection.
SBOLAPIEXPORTS Collection* createCollection(Document* doc, const char* uri);

/// Delete a Collection.
/// This doesn't delete any of the other structs
/// it references; For that you want cleanupSBOLCore.
SBOLAPIEXPORTS void deleteCollection(Collection* col);

/// Get the number of DNAComponents in a Collection.
/// @todo rename to NOT reflect doc
SBOLAPIEXPORTS int getNumDNAComponentsIn(const Collection* col);

/// Get the Nth DNAComponent inside a Collection.
/// @todo rename to NOT reflect doc
SBOLAPIEXPORTS DNAComponent* getNthDNAComponentIn(const Collection* col, int n);

/// Get the uri of a Collection.
/// Gotcha: this is different from both name and displayID.
SBOLAPIEXPORTS char* getCollectionURI(const Collection* col);

/// Get the displayID of a Collection.
/// Gotcha: this is different from both uri and name.
/// Gotcha: uppercase D
SBOLAPIEXPORTS char* getCollectionDisplayID(const Collection* col);

/// Get the name of a Collection.
/// Gotcha: this is different from both uri and displayID.
SBOLAPIEXPORTS char* getCollectionName(const Collection* col);

/// Get the description of a Collection.
SBOLAPIEXPORTS char* getCollectionDescription(const Collection* col);

/// Set the displayID of a Collection.
/// Gotcha: this is different from both name and displayID.
SBOLAPIEXPORTS void setCollectionDisplayID(Collection* col, const char* id);

/// Set the name of a Collection.
/// Gotcha: this is different from both uri and displayID.
SBOLAPIEXPORTS void setCollectionName(Collection* col, const char* name);

/// Set the description of a Collection.
SBOLAPIEXPORTS void setCollectionDescription(Collection* col, const char* desc);

/// Add a DNAComponent to a Collection.
/// @todo move to dnacomponent.h?
SBOLAPIEXPORTS void addDNAComponentToCollection(Collection* col, DNAComponent* com);

/// Delete a Component from a Collection's list of components
SBOLAPIEXPORTS void removeDNAComponentFromCollection(Collection* col, DNAComponent* com);

/// Find out whether a DNAComponent is inside a Collection.
/// @todo better name
/// Gotcha: lowercase dna
SBOLAPIEXPORTS int dnaComponentInCollection(const DNAComponent* com, const Collection* col);

/// Print an outline of a Collection to stdout.
SBOLAPIEXPORTS void printCollection(const Collection* col, int tabs);

/// Retrieve extra information about a Collection stored as structured XML
SBOLAPIEXPORTS xmlNode* getNthXMLAnnotationFromCollection(Collection *col, int index);

/// Annotate a Collection object with structured XML
SBOLAPIEXPORTS void addXMLAnnotationToCollection(Collection *col, xmlNode *node);

/// Remove the nth XML annotation from Collection specified by the index
SBOLAPIEXPORTS xmlNode* removeXMLAnnotationFromCollection(Collection *col, int index);

/// @}
/// @}
#endif
