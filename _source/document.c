#include <stdio.h>
#include <stdlib.h>

#include <libxml/parser.h>

#include "document.h"
#include "array.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"

/********************
 * isXURI functions
 ********************/

int isDNASequenceURI(Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0; /// @todo return -1 instead?
	int n;
	char* candidate;
	DNASequence* seq;
	for (n=0; n < getNumDNASequences(doc); n++) {
		seq = getNthDNASequence(doc, n);
		candidate = getDNASequenceURI(seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

int isSequenceAnnotationURI(Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0; /// @todo return -1 instead?
	int n;
	char* candidate;
	SequenceAnnotation* ann;
	for (n=0; n < getNumSequenceAnnotations(doc); n++) {
		ann = getNthSequenceAnnotation(doc, n);
		candidate = getSequenceAnnotationURI(ann);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

int isDNAComponentURI(Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0; /// @todo return -1 instead?
	int n;
	char* candidate;
	DNAComponent* com;
	for (n=0; n < getNumDNAComponents(doc); n++) {
		com = getNthDNAComponent(doc, n);
		candidate = getDNAComponentURI(com);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

int isCollectionURI(Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0; /// @todo return -1 instead?
	int n;
	char* candidate;
	Collection* col;
	for (n=0; n < getNumCollections(doc); n++) {
		col = getNthCollection(doc, n);
		candidate = getCollectionURI(col);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}
	return 0;
}

int isSBOLObjectURI(Document* doc, const char* uri) {
	return isDNASequenceURI(doc, uri)
		|| isSequenceAnnotationURI(doc, uri)
		|| isDNAComponentURI(doc, uri)
		|| isCollectionURI(doc, uri);
}

/***********************
 * registerX functions
 ***********************/

void registerDNASequence(DNASequence* seq) {
	if (seq && seq->doc) {
		insertPointerIntoArray(seq->doc->sequences, seq);
	}
}

void registerSequenceAnnotation(SequenceAnnotation* ann) {
	if (ann && ann->doc) {
		insertPointerIntoArray(ann->doc->annotations, ann);
	}
}

void registerDNAComponent(DNAComponent* com) {
	if (com && com->doc) {
		insertPointerIntoArray(com->doc->components, com);
	}
}

void registerCollection(Collection* col) {
	if (col && col->doc) {
		insertPointerIntoArray(col->doc->collections, col);
	}
}

/*********************
 * removeX functions
 *********************/

void removeDNASequence(Document* doc, DNASequence* seq) {
	if (doc && doc->sequences && seq) {
		int index = indexOfPointerInArray(doc->sequences, seq);
		if (index >= 0)
			removePointerFromArray(doc->sequences, index);
	}
}

void removeSequenceAnnotation(Document* doc, SequenceAnnotation* ann) {
	if (doc && doc->annotations && ann) {
		int index = indexOfPointerInArray(doc->annotations, ann);
		if (index >= 0)
			removePointerFromArray(doc->annotations, index);
	}
}

void removeDNAComponent(Document* doc, DNAComponent* com) {
	if (doc && doc->components && com) {
		int index = indexOfPointerInArray(doc->components, com);
		if (index >= 0)
			removePointerFromArray(doc->components, index);
	}
}

void removeCollection(Document* doc, Collection* col) {
	if (doc && doc->collections && col) {
		int index = indexOfPointerInArray(doc->collections, col);
		if (index >= 0)
			removePointerFromArray(doc->collections, index);
	}
}

/*********************
 * getNumX functions
 *********************/

int getNumDNASequences(const Document* doc) {
	if (doc && doc->sequences)
	    return getNumPointersInArray(doc->sequences);
	else
	    return 0;
}

int getNumSequenceAnnotations(Document* doc) {
	if (doc && doc->annotations)
		return getNumPointersInArray(doc->annotations);
	else
		return 0;
}

int getNumDNAComponents(const Document* doc) {
	if (doc && doc->components)
		return getNumPointersInArray(doc->components);
	else
		return 0; /// @todo return -1 instead?
}

int getNumCollections(Document* doc) {
	if (doc && doc->collections)
		return getNumPointersInArray(doc->collections);
	else
		return 0; /// @todo return -1 instead?
}

int getNumSBOLObjects(Document* doc) {
	if (doc)
		return getNumDNASequences(doc)
			+ getNumSequenceAnnotations(doc)
			+ getNumDNAComponents(doc)
			+ getNumCollections(doc);
	else
		return -1;
}

/*****************
 * isX functions
 *****************/

int isDNASequence(const Document* doc, const void* pointer) {
	if (doc) {
		return (int) indexOfPointerInArray(doc->sequences, pointer) >= 0;
	} else
		return 0; /// @todo return -1 instead?
}

int isSequenceAnnotation(const Document* doc, const void* pointer) {
	if (doc) {
		return (int) indexOfPointerInArray(doc->annotations, pointer) >= 0;
	} else
		return 0; /// @ todo return -1 instead?
}

int isDNAComponent(const Document* doc, const void* ptr) {
	if (doc) {
		return (int) indexOfPointerInArray(doc->components, ptr) >= 0;
	} else
		return 0; /// @todo return -1 instead?
}

int isCollection(Document* doc, const void* pointer) {
	if (doc && doc->collections && pointer) {
		return pointerContainedInArray(doc->collections, pointer);
	}
}

/******************
 * getX functions
 ******************/

DNASequence* getDNASequence(Document* doc, const char* uri) {
	if (!doc || !uri)
		return NULL;
	int n;
	char* candidate;
	DNASequence* seq;
	for (n=0; n < getNumDNASequences(doc); n++) {
		seq = getNthDNASequence(doc, n);
		candidate = getDNASequenceURI(seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return seq;
	}
	return NULL;
}

SequenceAnnotation* getSequenceAnnotation(Document* doc, const char* uri) {
	if (!doc || !uri)
		return NULL;
	int n;
	char* candidate;
	SequenceAnnotation* ann;
	for (n=0; n < getNumSequenceAnnotations(doc); n++) {
		ann = getNthSequenceAnnotation(doc, n);
		candidate = getSequenceAnnotationURI(ann);
		if (candidate && strcmp(candidate, uri) == 0)
			return ann;
	}
	return NULL;
}

DNAComponent* getDNAComponent(Document* doc, const char* uri) {
	if (!doc || !uri)
		return NULL;
	int n;
	char* candidate;
	DNAComponent* com;
	for (n=0; n < getNumDNAComponents(doc); n++) {
		com = getNthDNAComponent(doc, n);
		candidate = getDNAComponentURI(com);
		if (candidate && strcmp(candidate, uri) == 0)
			return com;
	}
	return NULL;
}

Collection* getCollection(Document* doc, const char* uri) {
	if (!doc || !uri)
		return NULL;
	int n;
	char* candidate;
	Collection* col;
	for (n=0; n < getNumCollections(doc); n++) {
		col = getNthCollection(doc, n);
		candidate = getCollectionURI(col);
		if (candidate && strcmp(candidate, uri) == 0)
			return col;
	}
	return NULL;
}

/*********************
 * getNthX functions
 *********************/

DNASequence* getNthDNASequence(Document* doc, int n) {
	if (doc && getNumDNASequences(doc) > n && n >= 0)
		return (DNASequence*) getNthPointerInArray(doc->sequences, n);
	else
		return NULL;
}

SequenceAnnotation* getNthSequenceAnnotation(Document* doc, int n) {
	if (doc && getNumSequenceAnnotations(doc) > n)
		return getNthPointerInArray(doc->annotations, n);
	else
		return NULL;
}

DNAComponent* getNthDNAComponent(Document* doc, int n) {
	if (doc && getNumDNAComponents(doc) > n && n >= 0)
		return (DNAComponent *)getNthPointerInArray(doc->components, n);
	else
		return NULL;
}

Collection* getNthCollection(Document* doc, int n) {
    if (doc && getNumCollections(doc) > n && n >= 0)
        return (Collection *)getNthPointerInArray(doc->collections, n);
    else
        return NULL;
}

/****************************
 * whole-Document functions
 ****************************/

Document* createDocument() {
	Document* doc = malloc(sizeof(Document));
	doc->sequences        = createPointerArray();
	doc->annotations = createPointerArray();
	doc->components       = createPointerArray();
	doc->collections         = createPointerArray();
	doc->xml_doc = xmlNewDoc(BAD_CAST "1.0");
	xmlDocSetRootElement(doc->xml_doc, xmlNewNode(NULL, "root"));
	return doc;
}

void deleteDocument(Document* doc) {
	if (!doc)
		return;
	int n;

	// sequences
	if (doc->sequences) {
		DNASequence* seq;
		for (n=0; n<getNumDNASequences(doc); n++) {
			seq = getNthDNASequence(doc, n);
			deleteDNASequence(seq);
			seq = NULL;
		}
		deletePointerArray(doc->sequences);
		doc->sequences = NULL;
	}

	// annotations
	if (doc->annotations) {
		SequenceAnnotation* seq;
		for (n=0; n<getNumSequenceAnnotations(doc); n++) {
			seq = getNthSequenceAnnotation(doc, n);
			deleteSequenceAnnotation(seq);
		}
		deletePointerArray(doc->annotations);
		doc->annotations = NULL;
	}

	// components
	if (doc->components) {
		DNAComponent* com;
		for (n=0; n<getNumDNAComponents(doc); n++) {
			com = getNthDNAComponent(doc, n);
			deleteDNAComponent(com);
		}
		deletePointerArray(doc->components);
		doc->components = NULL;
	}

	// collections
	if (doc->collections) {
		Collection* col;
		for (n=0; n<getNumCollections(doc); n++) {
       		col = getNthCollection(doc, n);
			removeCollection(doc, col);
			deleteCollection(col);
		}
		deletePointerArray(doc->collections);
		doc->collections = NULL;
	}

	// structured xml annotations
	if (doc->xml_doc) {
		xmlFreeDoc(doc->xml_doc);
	}
	free(doc);
	doc = NULL;
}

void printDocument(Document* doc) {
	if (!doc)
		return;
	int n;
	int total;

	// sequences
	total = getNumDNASequences(doc);
	if (total > 0) printf("%i sequences:\n", total);
	for (n=0; n<total; n++)
	printDNASequence(getNthDNASequence(doc, n), 1);

	// annotations
    total = getNumSequenceAnnotations(doc);
    if (total > 0) printf("%i annotations:\n", total);
    for (n=0; n<total; n++)
    	printSequenceAnnotation(getNthSequenceAnnotation(doc, n), 1);

	// components
	total = getNumDNAComponents(doc);
	if (total > 0) printf("%i components:\n", total);
	for (n=0; n<total; n++)
		printDNAComponent(getNthDNAComponent(doc, n), 1);

	// collections
    total = getNumCollections(doc);
    if (total > 0) printf("%i collections:\n", total);
    for (n=0; n<total; n++)
        printCollection(getNthCollection(doc, n), 1);
}

