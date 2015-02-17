#include "sbol.h"

/// Create an empty SBOLObject.
/// @return A pointer to the new SBOLObject.
TopLevelObject* createTopLevelObject(const char* uri) {
	// Base definition, same pattern for all SBOL classes
	TopLevelObject* obj = malloc(sizeof(TopLevelObject));
	doc->__class = SBOL_TOP_LEVEL;

	// @todo Check for URI collision

	// TopLevelObject starts extending base here
	obj->root_document = NULL;
	obj->documented_object = NULL;
	return obj;
}

/// Delete an SBOLObject.
/// This shouldn't be called directly;
/// instead, use deleteDNASequence, deleteCollection, etc.
void deleteTopLevelObject(TopLevelObject* obj) {

};

