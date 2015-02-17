#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @todo remove?
#include "property.h"
#include "object.h"
#include "array.h"
#include "document.h"
#include "collection.h"
#include "dnacomponent.h"

Collection* createCollection(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
	    return NULL;
	Collection* col  = malloc(sizeof(Collection));
	col->doc         = doc;
	col->base        = createSBOLCompoundObject(doc, uri);
	col->components  = createPointerArray();
	registerCollection(col);
	return col;
}

void deleteCollection(Collection* col) {
	if (col) {
		if (col->base) {
			deleteSBOLCompoundObject(col->base);
			col->base = NULL;
		}
		if (col->components) {
			deletePointerArray(col->components);
			col->components = NULL;
		}
		if (col->doc) {
			removeCollection(col->doc, col);
			col->doc = NULL;
		}
		free(col);
		col = NULL;
	}
}

char* getCollectionURI(const Collection* col) {
	if (col)
		return getSBOLCompoundObjectURI(col->base);
	else
		return NULL;
}

char* getCollectionDisplayID(const Collection* col) {
    if (col)
    	return getSBOLCompoundObjectDisplayID(col->base);
    else
    	return NULL;
}

char* getCollectionName(const Collection* col) {
	if (col)
		return getSBOLCompoundObjectName(col->base);
	else
		return NULL;
}

char* getCollectionDescription(const Collection* col) {
	if (col)
		return getSBOLCompoundObjectDescription(col->base);
	else
		return NULL;
}

int getNumDNAComponentsIn(const Collection* col) {
	if (col)
		return getNumPointersInArray(col->components);
	else
		return -1;
}

DNAComponent* getNthDNAComponentIn(const Collection* col, int n) {
    if (col)
        return (DNAComponent *)getNthPointerInArray(col->components, n);
    else
        return NULL;
}

void setCollectionURI(Collection* col, const char* uri) {
    if (col)
    	setSBOLCompoundObjectURI(col->base, uri);
}

void setCollectionDisplayID(Collection* col, const char* id) {
	if (col)
		setSBOLCompoundObjectDisplayID(col->base, id);
}

void setCollectionName(Collection* col, const char* name) {
	if (col)
		setSBOLCompoundObjectName(col->base, name);
}

void setCollectionDescription(Collection* col, const char* descr) {
	if (col)
		setSBOLCompoundObjectDescription(col->base, descr);
}

void addDNAComponentToCollection(Collection* col, DNAComponent* com) {
	if (col && com) {
		insertPointerIntoArray(col->components,  com);
	}
}

void removeDNAComponentFromCollection(Collection* col, DNAComponent* com) {
	if (col && com) {
		int index = indexOfPointerInArray(col->components, com);
		removePointerFromArray(col->components, index);
	}
}

int dnaComponentInCollection(const DNAComponent *com, const Collection *col) {
	if (!com || !col)
		return 0;
	DNAComponent *candidate;
	int n;
	for (n=0; n<getNumDNAComponentsIn(col); n++) {
		candidate = getNthDNAComponentIn(col, n);
		if (candidate == com)
			return 1;
	}
	return 0;
}

void printCollection(const Collection* col, int tabs) {
    if (!col)
        return;
    indent(tabs);   printf("%s\n", getCollectionURI(col));
    indent(tabs+1); printf("name:        %s\n", getCollectionName(col));
    indent(tabs+1); printf("description: %s\n", getCollectionDescription(col));
    int i;
    int num;
    if (col->components) {
        DNAComponent* com;
        num = getNumDNAComponentsIn(col);
        if (num > 0) {
            indent(tabs+1); printf("%i components:\n", num);
            for (i=0; i<num; i++) {
                com = getNthDNAComponentIn(col, i);
                indent(tabs+2); printf("%s\n", getDNAComponentURI(com));
            }
        }
    }
}

xmlNode* getNthXMLAnnotationFromCollection(Collection *col, int index) {
	return getNthStructuredAnnotationAsXML(col->base->base, index);
}

void addXMLAnnotationToCollection(Collection *col, xmlNode *node) {
	addXMLAnnotationToSBOLObject(col->base->base, node, col->doc->xml_doc);
	return;
}

xmlNode* removeXMLAnnotationFromCollection(Collection *col, int index) {
	xmlNode *node = removeXMLAnnotationFromSBOLObject(col->base->base, index, col->doc->xml_doc);
	return node;
}