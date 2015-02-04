#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @todo remove?
#include "property.h"
#include "array.h"
#include "document.h"
#include "dnacomponent.h"
#include "sequenceannotation.h"
#include "object.h"
#include "dnasequence.h"

DNAComponent* createDNAComponent(Document* doc, const char* uri) {
	if (!doc || !uri || isSBOLObjectURI(doc, uri))
	    return NULL;
	DNAComponent* com = malloc(sizeof(DNAComponent));
	com->doc         = doc;
	com->base        = createSBOLCompoundObject(doc, uri);
	com->dnaSequence = NULL;
	com->annotations = createPointerArray();
    com->type        = createTypeProperty(doc);
	registerDNAComponent(com);
	return com;
}

void deleteDNAComponent(DNAComponent* com) {
	if (com) {
		if (com->base) {
			deleteSBOLCompoundObject(com->base);
			com->base = NULL;
		}
		if (com->annotations) {
			deletePointerArray(com->annotations);
			com->annotations = NULL;
		}
		if (com->doc) {
			removeDNAComponent(com->doc, com);
			com->doc = NULL;
		}
        if (com->type) {
            deleteTypeProperty(com->type);
            com->type = NULL;
        }
		free(com);
		com = NULL;
	}
}

/// Clone a DNAComponent object
/// TODO:  What rule for the URI of the copy?
DNAComponent* copyDNAComponent(const DNAComponent* com, char* id_modifier) {
	int i;
	if (com) {
		//DNAComponent* copy = createDNAComponent(com->doc, uri);
		char* copy_uri = augmentURI(getDNAComponentURI(com), id_modifier);
		DNAComponent* copy = createDNAComponent(com->doc, copy_uri);
		//setSBOLCompoundObjectDisplayID(copy->base, getSBOLCompoundObjectDisplayID(com->base));
		//setSBOLCompoundObjectName(copy->base, getSBOLCompoundObjectName(com->base));
		//setSBOLCompoundObjectDescription(copy->base, getSBOLCompoundObjectDescription(com->base));
		setDNAComponentDisplayID(copy, getDNAComponentDisplayID(com));
		setDNAComponentName(copy, getDNAComponentName(com));
		setDNAComponentDescription(copy, getDNAComponentDescription(com));
		setDNAComponentType(copy, getDNAComponentType(com));
		setDNAComponentSequence(copy, copyDNASequence(com->dnaSequence, id_modifier));
		for (i = 0; i < getNumSequenceAnnotationsFor(com); i++) {	
			addSequenceAnnotation(copy, copySequenceAnnotation(getNthSequenceAnnotationFor(com, i), id_modifier));
		}
		
		return (DNAComponent *)copy;
	}
}

void printDNAComponent(const DNAComponent* com, int tabs) {
	if (!com)
		return;
	indent(tabs);   printf("%s\n", getDNAComponentURI(com));
	indent(tabs+1); printf("displayID:   %s\n", getDNAComponentDisplayID(com));
	indent(tabs+1); printf("name:        %s\n", getDNAComponentName(com));
	indent(tabs+1); printf("description: %s\n", getDNAComponentDescription(com));
	indent(tabs+1); printf("sequence:    %s\n", getDNASequenceURI(com->dnaSequence));
    indent(tabs+1); printf("type:        %s\n", getDNAComponentType(com));

	SequenceAnnotation* seq;
	int i;
	int num = getNumSequenceAnnotationsFor(com);
	if (num > 0) {
		indent(tabs+1); printf("%i annotations:\n", num);
		for (i=0; i<num; i++) {
			seq = getNthSequenceAnnotationFor(com, i);
			indent(tabs+2); printf("%s\n", getSequenceAnnotationURI(seq));
		}
	}
}

/********************
 * get... functions
 ********************/

char* getDNAComponentURI(const DNAComponent* com) {
	if (com)
		return (char *)getSBOLCompoundObjectURI(com->base);
	else
		return NULL;
}

char* getDNAComponentDisplayID(const DNAComponent* com) {
    if (com)
        return getSBOLCompoundObjectDisplayID(com->base);
    else
        return NULL;
}

char* getDNAComponentName(const DNAComponent* com) {
	if (com)
		return getSBOLCompoundObjectName(com->base);
	else
		return NULL;
}

char* getDNAComponentDescription(const DNAComponent* com) {
	if (com)
		return getSBOLCompoundObjectDescription(com->base);
	else
		return NULL;
}

DNASequence* getDNAComponentSequence(DNAComponent* com) {
	if (com && com->dnaSequence)
		return com->dnaSequence;
	else
		return NULL;
}

char* getDNAComponentType(const DNAComponent* com) {
    if (com && com->type)
    {
        TypeProperty* t  = com->type;
        if (t->uri)
            return getURIProperty(t->uri);
    }
    else
        return NULL;
}


/********************
 * set... functions
 ********************/

void setDNAComponentURI(DNAComponent* com, const char* uri) {
	if (com)
		setSBOLCompoundObjectURI(com->base, uri);
}

void setDNAComponentDisplayID(DNAComponent* com, const char* id) {
    if (com)
        setSBOLCompoundObjectDisplayID(com->base, id);
}

void setDNAComponentName(DNAComponent* com, const char* name) {
	if (com)
		setSBOLCompoundObjectName(com->base, name);
}

void setDNAComponentDescription(DNAComponent* com, const char* descr) {
	if (com)
		setSBOLCompoundObjectDescription(com->base, descr);
}

void setDNAComponentSequence(DNAComponent* com, DNASequence* seq) {
	if (com && seq)
		com->dnaSequence = seq;
}

void setDNAComponentType(DNAComponent* com, const char* uri) {
    if (com && uri)
    {
        TypeProperty *t = createTypeProperty(com->doc);
        setTypeProperty(t,uri);
        com->type = t;
    }
}

/************************
 * annotation functions
 ************************/

// TODO make it clear this goes with SequenceAnnotation too
void addSequenceAnnotation(DNAComponent* com, SequenceAnnotation* ann) {
	if (com && ann) {
		insertPointerIntoArray(com->annotations, ann);
	}
}

void removeSequenceAnnotationFromDNAComponent(DNAComponent* com, SequenceAnnotation* ann) {
	if (com && ann) {
		int index = indexOfPointerInArray(com->annotations, ann);
		removePointerFromArray(com->annotations, index);
	}
}


int getNumSequenceAnnotationsFor(const DNAComponent* com) {
	if (com)
		return getNumPointersInArray(com->annotations);
	else
		return -1;
}

SequenceAnnotation* getNthSequenceAnnotationFor(const DNAComponent* com, int n) {
	if (com && getNumSequenceAnnotationsFor(com) > n && n >= 0)
		return (SequenceAnnotation *)getNthPointerInArray(com->annotations, n);
	else
		return NULL;
}

/************************
* arbitrary xml annotation of DNAComponent objects
************************/

xmlNode* getNthXMLAnnotationFromDNAComponent(DNAComponent *com, int index) {
	return getNthStructuredAnnotationAsXML(com->base->base, index);
}

// Annotate a DNAComponent with extra data structured as XML
void addXMLAnnotationToDNAComponent(DNAComponent* com, xmlNode *node) {
	addXMLAnnotationToSBOLObject(com->base->base, node, com->doc->xml_doc);
	return;
}

// Remove XML annotation from DNAComponent
xmlNode* removeXMLAnnotationFromDNAComponent(DNAComponent *com, int index) {
	xmlNode *node = removeXMLAnnotationFromSBOLObject(com->base->base, index, com->doc->xml_doc);
	return node;
}


