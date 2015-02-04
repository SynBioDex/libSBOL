#include "sbol.h"

/// Creates a TopLevelObject.  This constructor is called automatically
/// anytime a derived object is added to a Document.  Ordinarily, the user
/// need not interface with TopLevelObjects.
/// @private 
/// @return A pointer to the new SBOLObject.
TopLevelObject* createTopLevelObject(SBOLDocument* doc) {
	// @todo Check for URI collision
	TopLevelObject* obj = malloc(sizeof(TopLevelObject));
	obj->__class = "TopLevel";
	obj->root_document = doc;
	obj->documented_object = NULL;
	return obj;
}

/// Delete an SBOLObject.
/// This shouldn't be called directly;
/// instead, use deleteDNASequence, deleteCollection, etc.
void deleteTopLevelObject(TopLevelObject* obj) {

};

