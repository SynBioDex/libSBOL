///////////////////////////////////////////////////////////
/// @file
/// TopLevel is a class that is extended by any Documented object 
/// that can be found at the top level of a SBOL file, that is any 
/// SBOL object that is not nested inside another object when written 
/// to a file. Instead of nesting, composite TopLevel objects link to 
/// their subordinate TopLevel objects via URIs when written to a file. 
/// For example, a composite Component object A would link to its 
/// sub-Component object B using B’s URI.
///////////////////////////////////////////////////////////

#include "sbol.h"

struct _TopLevel {
	const char* __class = "TopLevel";
	SBOLDocument* root_document;
	Documented* documented_object;
	void* subclass;
};

TopLevelObject* createTopLevelObject(SBOLDocument* doc);