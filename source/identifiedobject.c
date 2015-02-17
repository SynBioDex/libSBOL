#include "sbol.h"

/// Create an empty SBOLObject.
/// @return A pointer to the new SBOLObject.
IdentifiedObject* sbol_create_identified(const char* uri) {
	// @todo Check for URI collision
	
	// Base definition, same pattern for all SBOL classes
	IdentifiedObject* obj = malloc(sizeof(IdentifiedObject));
	obj->__class = SBOL_IDENTIFIED;
	obj->__super = _sbol_base(obj, sbol_create_top_level());
	obj->__sub = NULL;

	// SBOLIdentifiedObject starts extending base here
	obj->identity = createTextProperty();
	setTextProperty(obj->identity, uri);
	obj->persistentIdentity = createTextProperty();
	setTextProperty(obj->persistentIdentity, uri);
	obj->version = createTextProperty();
	setTextProperty(obj->persistentIdentity, "0");
	obj->timeStamp = NULL;
	obj->annotations = sbol_get_annotations;
	obj->xml_annotations = sbol_get_xml_annotations;
	//obj->__annotations = createPointerArray();;
	//obj->__xmlAnnotations = createPointerArray();;
	obj->subclass = NULL;
	return obj;
}

void* sbol_get_annotations(int index) {
	return;
}

void* sbol_get_xml_annotations(int index){
	return;
}

char* sbol_get_identity(void* obj) {
	if ( _sbol_is_type(SBOL_IDENTIFIED, obj) ) {
		return getTextProperty(((IdentifiedObject*)obj)->identity);
	}
	else if ( _sbol_base(obj) ) {
		sbol_get_identity( _sbol_base(obj) );
		return;
	}
	else {
		// Return an error 'This SBOL object is not Identified or any of its derived classes'
		return;
	}
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
