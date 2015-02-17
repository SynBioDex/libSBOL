///////////////////////////////////////////////////////////
/// @file
/// 
/// Contains functions for importing SBOL objects
/// from an XML file. Only readDocument is meant to be
/// exported; everything else supports it.
/// 
/// @todo Figure out how to generate documentation for
///       static functions.
///////////////////////////////////////////////////////////

#ifndef SBOL_READER_HEADER
#define SBOL_READER_HEADER

// declares xmlChar, xmlNode
#include <libxml/xmlstring.h>
#include <libxml/tree.h>

#include "constants.h"
#include "prototypes.h"

/// Get the URI of an xmlNode.
static xmlChar *getNodeURI(xmlNode *node);

/// Get an array of pointers to xmlNodes that match an XPath expression.
/// You need to free the array, but the nodes themselves are part of an
/// xmlDoc and will be freed by xmlFreeDoc after parsing is finished.
/// @param node The root node for the XPath to search from.
/// @return a PointerArray* that must freed with deletePointerArray()
static PointerArray *getNodesMatchingXPath(xmlNode *node, xmlChar *path);

/// Like getNodesMatchingXPath, except it only returns the first node.
/// If SBOL_DEBUG_STATEMENTS are used, it will also warn if there were
/// other matching nodes.
/// @return an xmlNode* that doesn't need to be separately freed
static xmlNode *getSingleNodeMatchingXPath(xmlNode *node, xmlChar *path);

/// Like getSingleNodeMatchingXPath, except it only returns the node contents.
/// @return An xmlChar* that needs to be freed with xmlFree()
static xmlChar *getContentsOfNodeMatchingXPath(xmlNode *node, xmlChar *path);

/// Like getSingleNodeMatchingXPath, except it only returns the node's URI.
/// @return An xmlChar* that needs to be freed with xmlFree()
static xmlChar *getURIOfNodeMatchingXPath(xmlNode *node, xmlChar *path);

/// Searches for nodes matching an XPath expression, and applies a function
/// to them.
/// @param fn A function that takes an xmlNodePtr and returns void
/// @param node The root node for XPath to search from
static void applyFunctionToNodesMatchingXPath(void (*fn)(xmlNode *), xmlNode *node, xmlChar *path);

/// Convenience function for applying one of the read*
/// functions to the whole document.
static void processNodes(void (*read)(xmlNode *), xmlChar *path);

/// @todo void readNamespaces(xmlNode *node)?

/// Read the contents of a node into an existing SBOLCompoundObject.
/// This one is a little weird in that it's the only read* function
/// that needs a pointer to an existing SBOLObject.
static void readSBOLCompoundObject(SBOLCompoundObject *obj, xmlNode *node);

/// Read the contents of a node and use it to add
/// references between existing SBOLObjects.
static void readDNASequenceContent(xmlNode *node);

/// Read the contents of a node into a new SequenceAnnotation,
/// ignoring any reference nodes.
static void readSequenceAnnotationContent(xmlNode *node);

/// Read the contents of a node and use it to add
/// references between existing SBOLObjects.
static void readSequenceAnnotationReferences(xmlNode *node);

/// Read the contents of a node into a new DNAComponent,
/// ignoring any reference nodes.
static void readDNAComponentContent(xmlNode *node);

/// Read the contents of a node and use it to add
/// references between existing SBOLObjects.
static void readDNAComponentReferences(xmlNode *node);

/// Read the contents of a node into a new Collection,
/// ignoring any reference nodes.
static void readCollectionContent(xmlNode *node);

/// Read the contents of a node and use it to add
/// references between existing SBOLObjects.
static void readCollectionReferences(xmlNode *node);

/// Parse an SBOL document from disk and create
/// matching structs in memory. Also validates
/// before parsing. Prints a message to stdout
/// if the document is invalid.
/// @todo Return an error code on invalid documents
SBOLAPIEXPORTS void readDocument(Document* doc, char* filename);

#endif
