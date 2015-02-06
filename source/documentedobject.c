#include "sbol.h"


DocumentedObject* createDocumentedObject(const char* uri) {
	// @todo Check for URI collision

	// Base definition, same pattern for all SBOL classes
	DocumentedObject* obj = malloc(sizeof(DocumentedObject));
	obj->__class = SBOL_DOCUMENTED;
	obj->__super = super(obj, createIdentifiedObject(uri));
	obj->__sub = NULL;

	// SBOLDocument starts extending base here
	obj->displayID = createTextProperty();
	setTextProperty(obj->displayID, "");
	obj->name = createTextProperty();
	setTextProperty(obj->name, "");
	obj->description = createTextProperty();
	setTextProperty(obj->description, "");
	return obj;
}