///////////////////////////////////////////////////////////
/// @file
/// Defines the SBOLObject struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_OBJECT_HEADER
#define SBOL_OBJECT_HEADER

#include "constants.h"
#include "prototypes.h"
#include <libxml/tree.h>

/**************
 * SBOLObject
 **************/

/// @defgroup SBOLObject SBOLObject
/// @{
/// @struct _SBOLObject
/// @brief SBOL base object, mainly consisting of a uri.
/// @details Used as a makeshift "base class" for DNASequence, 
/// SequenceAnnotation, DNAComponent, and Collection.
/// This is where to put anything that needs to be 
/// accessible from each of the four main structs.
/// Arbitrary XML objects that contain additional
/// descriptive information about an SBOL object
/// can also be added
/// @var _SBOLObject::uri
/// @var _SBOLObject::xml_annotations
///
struct _SBOLObject {
	URIProperty* uri; ///< Unique string for identification.
	PointerArray* xml_annotations; ///< Array of optional non-SBOL annotations
};

/// @name Methods
/// @{

/// Create an empty SBOLObject.
/// @return A pointer to the new SBOLObject.
SBOLObject* createSBOLObject(Document* doc, const char* uri);

/// Delete an SBOLObject.
/// This shouldn't be called directly;
/// instead, use deleteDNASequence, deleteCollection, etc.
void deleteSBOLObject(SBOLObject* obj);

/// Delete all SBOLObjects from memory.
/// @todo remove this? is it ever used?
SBOLAPIEXPORTS void cleanupSBOLObjects(Document* doc);

/// Set the URI of an SBOLObject.
/// This shouldn't be called directly.
void setSBOLObjectURI(SBOLObject* obj, const char* uri);

/// Get the URI of an SBOLObject.
/// This shouldn't be called directly.
char* getSBOLObjectURI(const SBOLObject* obj);

/// Returns numer of structured XML annotations associated with this object
SBOLAPIEXPORTS int getNumStructuredAnnotations(SBOLObject* obj);

/// Returns a structured annotation as a libXML2 xmlNode object
SBOLAPIEXPORTS xmlNode* getNthStructuredAnnotationAsXML(SBOLObject* obj, int n);

/// Returns a structured annotation as raw text
SBOLAPIEXPORTS char* getNthStructuredAnnotationAsText(SBOLObject* obj, int n);

/// Private low-level accessor used to add an XML annotation.  Use the high-level
/// accessors instead, eg addXMLAnnotationToDNAComponent
SBOLAPIEXPORTS void addXMLAnnotationToSBOLObject(SBOLObject* obj, xmlNode *node, xmlDoc* xml_doc);

/// Private low-level accessor used to remove an XML annotation.  Use the high-level
/// accessors instead, eg removeXMLAnnotationToDNAComponent
SBOLAPIEXPORTS xmlNode* removeXMLAnnotationFromSBOLObject(SBOLObject* obj, int index, xmlDoc* xml_doc);


/// @}
/// @}

/**********************
 * SBOLCompoundObject
 **********************/

/// @defgroup SBOLCompoundObject SBOLCompoundObject
/// @{
/// @struct _SBOLCompoundObject
/// @brief SBOLObject that also includes a name,
/// displayID, and description.
/// @details Used a base struct for DNAComponent and Collection.
/// @var _SBOLCompoundObject::base
/// @var _SBOLCompoundObject::displayID
/// @var _SBOLCompoundObject::name
/// @var _SBOLCompoundObject::description

struct _SBOLCompoundObject {
	SBOLObject*   base;        ///< uri
	TextProperty* displayID;   ///< Like the uri but for display purposes. Not necessarily unique.
	TextProperty* name;        ///< Like the uri but human-readable. Not necessarily unique.
	TextProperty* description; ///< Some text describing the object.
};

/// @name Methods
/// @{

/// Create an empty SBOLCompoundObject.
/// @return A pointer to the new SBOLCompoundObject.
SBOLCompoundObject* createSBOLCompoundObject(Document* doc, const char* uri);

/// Delete an SBOLObject.
/// This shouldn't be called directly;
/// instead, use deleteDNAComponent, deleteCollection, etc.
void deleteSBOLCompoundObject(SBOLCompoundObject* obj);

/// Set the URI of an SBOLComoundObject.
/// This shouldn't be called directly.
void setSBOLCompoundObjectURI(SBOLCompoundObject* obj, const char* uri);

/// Get the URI of an SBOLCompoundObject.
/// This shouldn't be called directly.
char* getSBOLCompoundObjectURI(const SBOLCompoundObject* obj);

/// Set the displayID of an SBOLCompoundObject.
/// This shouldn't be called directly.
/// Gotcha: uppercase D
void setSBOLCompoundObjectDisplayID(SBOLCompoundObject* obj, const char* id);

/// Get the URI of an SBOLCompoundObject.
/// This shouldn't be called directly.
/// Gotcha: uppercase D
char* getSBOLCompoundObjectDisplayID(const SBOLCompoundObject* obj);

/// Set the name of an SBOLCompoundObject.
/// This shouldn't be called directly.
void setSBOLCompoundObjectName(SBOLCompoundObject* obj, const char* name);

/// Get the name of an SBOLCompoundObject.
/// This shouldn't be called directly.
char* getSBOLCompoundObjectName(const SBOLCompoundObject* obj);

/// Set the description of an SBOLCompoundObject.
/// This shouldn't be called directly.
void setSBOLCompoundObjectDescription(SBOLCompoundObject* obj, const char* descr);

/// Get the description of an SBOLCompoundObject.
/// This shouldn't be called directly.
char* getSBOLCompoundObjectDescription(const SBOLCompoundObject* obj);

/// @}
/// @}

#endif
