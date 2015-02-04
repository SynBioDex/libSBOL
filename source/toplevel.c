#include "sbol.h"

/// Create an empty SBOLObject.
/// @return A pointer to the new SBOLObject.
TopLevelObject* createTopLevelObject(const char* uri) {
	// @todo Check for URI collision
	TopLevelObject* obj = malloc(sizeof(TopLevelObject));
	obj->root_document = NULL;
	obj->documented_object = NULL;
	return obj;
}

/// Delete an SBOLObject.
/// This shouldn't be called directly;
/// instead, use deleteDNASequence, deleteCollection, etc.
void deleteTopLevelObject(TopLevelObject* obj) {

};

