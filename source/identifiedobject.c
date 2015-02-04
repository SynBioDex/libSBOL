#include "sbol.h"
#include <libxml/tree.h>

/// Create an empty SBOLObject.
/// @return A pointer to the new SBOLObject.
IdentifiedObject* createIdentifiedObject(const char* uri) {
	// @todo Check for URI collision
	
	// Base definition, same pattern for all SBOL classes
	IdentifiedObject* obj = malloc(sizeof(IdentifiedObject));
	obj->__class = SBOL_IDENTIFIED;
	
	// SBOLDocument starts extending base here
	obj->identity = createTextProperty();
	setTextProperty(obj->identity, uri);
	obj->persistentIdentity = createTextProperty();
	setTextProperty(obj->persistentIdentity, uri);
	obj->version = createTextProperty();
	setTextProperty(obj->persistentIdentity, "0");
	obj->timeStamp = NULL;
	obj->annotations = createPointerArray();;
	obj->xml_annotations = createPointerArray();;
	obj->subclass = NULL;
	return obj;
}


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
