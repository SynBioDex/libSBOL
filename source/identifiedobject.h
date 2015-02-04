///////////////////////////////////////////////////////////
/// @file
/// Defines the SBOLObject struct, as well as
/// functions for operating on it.
///////////////////////////////////////////////////////////

#ifndef SBOL_IDENTIFIED_HEADER
#define SBOL_IDENTIFIED_HEADER

#include "sbol.h"

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
struct _IdentifiedObject{
	const char* __class;
	TextProperty *identity; ///< different versions of the object indicated by the persistentIdentity
	TextProperty *persistentIdentity; ///< the same persistent URI is shared by SBOL objects which are versions of each other
	TextProperty *version;
	TextProperty *timeStamp;
	PointerArray *annotations;
	PointerArray *xml_annotations; ///< Array of optional non-SBOL annotations
	void *subclass;
};

/// @name Methods
/// @{

/// Create an empty SBOLObject.
/// @return A pointer to the new SBOLObject.
SBOLAPIEXPORTS IdentifiedObject* createIdentifiedObject(const char* uri);

/// Delete an SBOLObject.
/// This shouldn't be called directly;
/// instead, use deleteDNASequence, deleteCollection, etc.
//void deleteSBOLObject(SBOLObject* obj);

///// Delete all SBOLObjects from memory.
///// @todo remove this? is it ever used?
//SBOLAPIEXPORTS void cleanupSBOLObjects(Document* doc);
//
///// Set the URI of an SBOLObject.
///// This shouldn't be called directly.
//void setSBOLObjectURI(SBOLObject* obj, const char* uri);
//
///// Get the URI of an SBOLObject.
///// This shouldn't be called directly.
//char* getSBOLObjectURI(const SBOLObject* obj);
//
///// Returns numer of structured XML annotations associated with this object
//SBOLAPIEXPORTS int getNumStructuredAnnotations(SBOLObject* obj);
//
///// Returns a structured annotation as a libXML2 xmlNode object
//SBOLAPIEXPORTS xmlNode* getNthStructuredAnnotationAsXML(SBOLObject* obj, int n);
//
///// Returns a structured annotation as raw text
//SBOLAPIEXPORTS char* getNthStructuredAnnotationAsText(SBOLObject* obj, int n);
//
///// Private low-level accessor used to add an XML annotation.  Use the high-level
///// accessors instead, eg addXMLAnnotationToDNAComponent
//SBOLAPIEXPORTS void addXMLAnnotationToSBOLObject(SBOLObject* obj, xmlNode *node, xmlDoc* xml_doc);
//
///// Private low-level accessor used to remove an XML annotation.  Use the high-level
///// accessors instead, eg removeXMLAnnotationToDNAComponent
//SBOLAPIEXPORTS xmlNode* removeXMLAnnotationFromSBOLObject(SBOLObject* obj, int index, xmlDoc* xml_doc);

/// @}
/// @}

#endif
