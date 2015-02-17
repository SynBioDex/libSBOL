#include <stdlib.h>
#include <string.h>
#include "property.h"
#include "array.h"
#include "object.h"
#include "document.h"
#include <libxml/tree.h>
#include <libxml/xmlstring.h>

/**************
 * SBOLObject
 **************/

SBOLObject* createSBOLObject(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
		return NULL;
	SBOLObject* obj = malloc(sizeof(SBOLObject));
	obj->uri = createURIProperty(doc);
	obj->xml_annotations = createPointerArray();
	setSBOLObjectURI(obj, uri);
	return obj;
}

void deleteSBOLObject(SBOLObject* obj) {
	if (obj) {
		if (obj->uri) {
			deleteURIProperty(obj->uri);
			obj->uri = NULL;
		}
		if (obj->xml_annotations) {
			/// @todo free xmlNodes contained in PointerArray
			deletePointerArray(obj->xml_annotations);
		}
		//free(obj); /// @todo what's wrong with this?
		obj = NULL;
	}
}

void setSBOLObjectURI(SBOLObject* obj, const char* uri) {
	if (obj && uri)
		setURIProperty(obj->uri, uri);
}

char* getSBOLObjectURI(const SBOLObject* obj) {
	if (obj)
		return (char *)getURIProperty(obj->uri);
	else
		return NULL;
}

int getNumStructuredAnnotations(SBOLObject* obj) {
	return getNumPointersInArray(obj->xml_annotations);
}

// Returns a structured annotation as a libXML2 xml node
xmlNode* getNthStructuredAnnotationAsXML(SBOLObject* obj, const int n) {
	if (n >= getNumStructuredAnnotations(obj)) {
		return;
	} else {
		return (xmlNode *)getNthPointerInArray(obj->xml_annotations, n);
	}
}

// Returns a structured annotation as raw text
char* getNthStructuredAnnotationAsText(SBOLObject* obj, const int n) {
	if (n >= getNumStructuredAnnotations(obj)) {
		return;
	} else {
		xmlBufferPtr buffer = xmlBufferCreate();
		xmlKeepBlanksDefault(0);
		char *text = NULL;

		int size = xmlNodeDump(buffer, obj->uri->doc->xml_doc, getNthStructuredAnnotationAsXML(obj, n), 0, 0);
		if (buffer->content) {
			text = malloc(size + 1);  // Allocate an extra byte for termination char
			strcpy(text, buffer->content);
		}
		xmlFree(buffer);
		return text;
	}
}

void addXMLAnnotationToSBOLObject(SBOLObject* obj, xmlNode *node, xmlDoc* xml_doc) {
	node = xmlAddChild(xmlDocGetRootElement(xml_doc), node);
	insertPointerIntoArray(obj->xml_annotations, node);
	int i = xmlReconciliateNs(xml_doc, xmlDocGetRootElement(xml_doc));
	return;
}

xmlNode* removeXMLAnnotationFromSBOLObject(SBOLObject* obj, int index, xmlDoc* xml_doc) {
	xmlNode *node = getNthStructuredAnnotationAsXML(obj, index);
	removePointerFromArray(obj->xml_annotations, index);
	xmlUnlinkNode(node);
	// xmlFreeNode(node);
	int i = xmlReconciliateNs(xml_doc, xmlDocGetRootElement(xml_doc));
	return node;
}

/**********************
 * SBOLCompoundObject
 **********************/

SBOLCompoundObject* createSBOLCompoundObject(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
		return NULL;
	SBOLCompoundObject* obj = malloc(sizeof(SBOLCompoundObject));
	obj->base        = createSBOLObject(doc, uri);
	obj->displayID   = createTextProperty();
	obj->name        = createTextProperty();
	obj->description = createTextProperty();
	return obj;
}

void deleteSBOLCompoundObject(SBOLCompoundObject* obj) {
	if (obj) {
		if (obj->base) {
			deleteSBOLObject(obj->base);
			obj->base = NULL;
		}
		if (obj->displayID) {
			deleteTextProperty(obj->displayID);
			obj->displayID = NULL;
		}
		if (obj->name) {
			deleteTextProperty(obj->name);
			obj->name = NULL;
		}
		if (obj->description) {
			deleteTextProperty(obj->description);
			obj->description = NULL;
		}
		free(obj);
		obj = NULL;
	}
}

void setSBOLCompoundObjectURI(SBOLCompoundObject* obj, const char* uri) {
	if (obj)
		setSBOLObjectURI(obj->base, uri);
}

char* getSBOLCompoundObjectURI(const SBOLCompoundObject* obj) {
	if (obj)
		return (char *)getSBOLObjectURI(obj->base);
	else
		return NULL;
}

void setSBOLCompoundObjectDisplayID(SBOLCompoundObject* obj, const char* id) {
	if (obj) {
		setTextProperty(obj->displayID, id);
	}
}

char* getSBOLCompoundObjectDisplayID(const SBOLCompoundObject* obj) {
	if (obj)
		return getTextProperty(obj->displayID);
	else
		return NULL;
}

void setSBOLCompoundObjectName(SBOLCompoundObject* obj, const char* name) {
	if (obj) {
		setTextProperty(obj->name, name);
	}
}

char* getSBOLCompoundObjectName(const SBOLCompoundObject* obj) {
	if (obj)
		return getTextProperty(obj->name);
	else
		return NULL;
}

void setSBOLCompoundObjectDescription(SBOLCompoundObject* obj, const char* descr) {
	if (obj) {
		setTextProperty(obj->description, descr);
	}
}

char* getSBOLCompoundObjectDescription(const SBOLCompoundObject* obj) {
	if (obj)
		return getTextProperty(obj->description);
	else
		return NULL;
}

