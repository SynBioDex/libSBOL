#include "sbol.h"


DocumentedObject* create_documented_object(const char* uri) {
	// @todo Check for URI collision

	// Base definition, same pattern for all SBOL classes
	DocumentedObject* obj = malloc(sizeof(DocumentedObject));
	obj->__class = SBOL_DOCUMENTED;
	obj->__super = _sbol_extend(obj, sbol_create_identified(uri));
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

char* sbol_get_display_id(void* obj) {
	if (_sbol_is_type(SBOL_DOCUMENTED, obj)) {
		return getTextProperty(((DocumentedObject*)obj)->displayID);
	}
	else if (_sbol_base(obj)) {
		sbol_get_display_id(_sbol_base(obj));
		return NULL;
	}
	else {
		// Return an error 'This SBOL object is not Identified or any of its derived classes'
		return NULL;
	}
}

char* sbol_get_name(void* obj) {
	if (_sbol_is_type(SBOL_DOCUMENTED, obj)) {
		return getTextProperty(((DocumentedObject*)obj)->name);
	}
	else if (_sbol_base(obj)) {
		sbol_get_name(_sbol_base(obj));
		return NULL;
	}
	else {
		// Return an error 'This SBOL object is not Identified or any of its derived classes'
		return NULL;
	}
}

char* sbol_get_description(void* obj) {
	if (_sbol_is_type(SBOL_DOCUMENTED, obj)) {
		return getTextProperty(((DocumentedObject*)obj)->description);
	}
	else if (_sbol_base(obj)) {
		sbol_get_description(_sbol_base(obj));
		return NULL;
	}
	else {
		// Return an error 'This SBOL object is not Identified or any of its derived classes'
		return NULL;
	}
};

