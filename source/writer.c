#include <stdio.h>
#include <string.h>

#include <libxml/xmlwriter.h>
#include <libxml/tree.h>

#include "writer.h"
#include "utilities.h"
#include "array.h"
#include "object.h"

#include "sbol.h"

static int            INDENT;
static xmlTextWriter* WRITER;
static xmlDoc*        OUTPUT;
static PointerArray*  PROCESSED;

/************************
 * utility functions for
 * setting up, writing,
 * and tearing down
 ************************/

void indentMore() { xmlTextWriterSetIndent(WRITER, ++INDENT); }
void indentLess() { xmlTextWriterSetIndent(WRITER, --INDENT); }

static void createSBOLWriter() {
	INDENT = 0;
	WRITER = xmlNewTextWriterDoc(&OUTPUT, 0);
	xmlTextWriterSetIndentString(WRITER,xmlCharStrdup("\t"));
	xmlTextWriterSetIndent(WRITER, INDENT);
}

static void cleanupSBOLWriter() {
	xmlFreeTextWriter(WRITER);
	xmlFreeDoc(OUTPUT);
	WRITER = NULL;
	OUTPUT = NULL;
	deletePointerArray(PROCESSED);
	PROCESSED = NULL;
	xmlCleanupParser();
}

static void markProcessed(void *obj) {
	insertPointerIntoArray(PROCESSED, obj);
}

static int alreadyProcessed(void *obj) {
	return pointerContainedInArray(PROCESSED, obj); 
}

static void resetProcessed() {
	deletePointerArray(PROCESSED);
	PROCESSED = createPointerArray();
}

static void startSBOLDocument() {
	resetProcessed();
	createSBOLWriter();
	xmlTextWriterStartDocument(WRITER, NULL, NULL, NULL);
	xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_RDF));
	xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup("xmlns:" NSPREFIX_RDF), xmlCharStrdup(NSURL_RDF));
	xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup("xmlns:" NSPREFIX_RDFS), xmlCharStrdup(NSURL_RDFS));
	xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup("xmlns:" NSPREFIX_SO),   xmlCharStrdup(NSURL_SO));
	xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup("xmlns:" NSPREFIX_SBOL), xmlCharStrdup(NSURL_SBOL));
	indentMore();
}

// Joins two xmlChar*s with a ":"
static xmlChar* constructXPath(const xmlChar *prefix, const xmlChar *name) {
	xmlChar* token = xmlStrncatNew(prefix, xmlCharStrdup(":"), -1);
	return xmlStrncatNew(token, name, -1);
}

static void addNamespacesToDocument(Document *doc) {
	xmlNode *root = xmlDocGetRootElement(doc->xml_doc);
	xmlNs *ns = root->nsDef;
	indentLess();
	while (ns) {
		// Construct element path for non-SBOL namespace
		xmlTextWriterWriteAttribute(WRITER, constructXPath(xmlCharStrdup("xmlns"), ns->prefix), ns->href);
		ns = ns->next;
	}
	indentMore();
	return;
}

static void endSBOLDocument() {
	indentLess();
	xmlTextWriterEndElement(WRITER);
	xmlTextWriterEndDocument(WRITER);
}

static int saveSBOLDocument(const char* filename) {
	int invalid = 0;
	if (!isValidSBOL(OUTPUT)) {
		invalid = 1;
		printf("WARNING: %s is not valid SBOL. Saving anyway.\n", filename);
	}
	int written = xmlSaveFile(filename, OUTPUT);
	return (int) invalid || written == -1;
}



/************************************
 * functions for writing individual
 * SBOLObjects to the WRITER
 ************************************/

// Writes xml nodes with namespaces not used by SBOL
static void writeStructuredAnnotation(xmlNode *node) {
	// Ignore all non-Element xml nodes, eg, text
	if (node->type != XML_ELEMENT_NODE) {
		return;
	}
	else {
		xmlChar *path = constructXPath(node->ns->prefix, node->name);
		xmlTextWriterStartElement(WRITER, path);
		xmlAttr *attr = node->properties;
		while (attr)
		{
			if (attr->name && attr->children->content) {
				xmlTextWriterWriteAttribute(WRITER, attr->name, attr->children->content);
			}
			attr = attr->next;
		}

		if (node->content) xmlTextWriterWriteElement(WRITER, path, node->content);

		xmlNode *child_node;
		child_node = node->children;
		while (child_node) {
			indentMore();
			writeStructuredAnnotation(child_node);
			indentLess();
			child_node = child_node->next;
		}
		xmlTextWriterEndElement(WRITER);
		return;
	}
}

static void writeDNASequence(DNASequence* seq) {
	if (!seq)
		return;
	xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_DNASEQUENCE));
	xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_ABOUT), xmlCharStrdup(getDNASequenceURI(seq)));

	// nucleotides
	if (!alreadyProcessed((void *)seq)) {
		char* nt = getDNASequenceNucleotides(seq);
		if (nt) {
		 	xmlTextWriterWriteElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_NUCLEOTIDES), xmlCharStrdup(nt));
			markProcessed((void *)seq);
		}
		free(nt);
	}
	
	xmlTextWriterEndElement(WRITER);
}

static void writeSequenceAnnotation(SequenceAnnotation* ann) {
	if (!ann)
		return;
	markProcessed((void *)ann);
	xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_SEQUENCEANNOTATION));
	xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_ABOUT), xmlCharStrdup(getSequenceAnnotationURI(ann)));
	
	// precedes
	int n;
	SequenceAnnotation* ann2;
	indentMore();
	for (n=0; n<getNumPrecedes(ann); n++) {
		ann2 = getNthPrecedes(ann, n);
		xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_PRECEDES));
		xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_RESOURCE), xmlCharStrdup(getSequenceAnnotationURI(ann2)));
		xmlTextWriterEndElement(WRITER);
	}
	indentLess();
	
	// start, end
	int start = getSequenceAnnotationStart(ann);
	int end   = getSequenceAnnotationEnd(ann);
	if (start>0)
		xmlTextWriterWriteElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_BIOSTART), xmlCharStrdup(intToStr(start)));
	if (end>0)
		xmlTextWriterWriteElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_BIOEND),  xmlCharStrdup(intToStr(end)));
	
	// subComponent
	char* uri;
	indentMore();
	if (ann->subComponent) {
		uri = getDNAComponentURI(ann->subComponent);
		xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_SUBCOMPONENT));
		if (alreadyProcessed((void *)(ann->subComponent)))
			xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_RESOURCE), xmlCharStrdup(uri));
		else {
	 		indentMore();
	 		writeDNAComponent(ann->subComponent);
	 		indentLess();
	 	}
		xmlTextWriterEndElement(WRITER);
	}
	indentLess();
	
	xmlTextWriterEndElement(WRITER);
}

static void writeDNAComponent(DNAComponent* com) {
	if (!com)
		return;
	xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_DNACOMPONENT));
	if (!alreadyProcessed((void *)com)) {
		markProcessed((void *)com);
		xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_ABOUT), xmlCharStrdup(getDNAComponentURI(com)));
		
		// properties
		char* data;
		
		data = getDNAComponentType(com);		
		if (data) {
			xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_TYPE));
			xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_RESOURCE), xmlCharStrdup(data));
			xmlTextWriterEndElement(WRITER);
		}
		data = getDNAComponentDisplayID(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_DISPLAYID), xmlCharStrdup(data));
		data = getDNAComponentName(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_NAME), xmlCharStrdup(data));
		data = getDNAComponentDescription(com);
		if (data)
			xmlTextWriterWriteElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_DESCRIPTION), xmlCharStrdup(data));
        
		// sequence
		if (com->dnaSequence) {
			xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_DNASEQUENCE_REF));
			indentMore();
			/// @todo sometimes no contents?
			writeDNASequence(com->dnaSequence);
			markProcessed(com->dnaSequence);
			indentLess();
			xmlTextWriterEndElement(WRITER);
		}
		
		// annotations
		int n;
		int num = getNumSequenceAnnotationsFor(com);
		SequenceAnnotation* ann;
		indentMore();
		if (num>0) {
			for (n=0; n<num; n++) {
				ann = getNthSequenceAnnotationFor(com, n);
				indentMore();
				xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_ANNOTATION));
				writeSequenceAnnotation(ann);
				xmlTextWriterEndElement(WRITER);
				indentLess();
			}
		}
		
		// Copy a structured annotation as an xml node object from the base Document's xml_doc to 
		// the destination document
		xmlNode *node;
		xmlNode *node_copy;
		for (n = 0; n < getNumPointersInArray(com->base->base->xml_annotations); n++) {
			node = (xmlNode *)getNthPointerInArray(com->base->base->xml_annotations, n);
			node_copy = xmlDocCopyNode(node, OUTPUT, 1);
			indentMore();
			writeStructuredAnnotation(node_copy);
			indentLess();
		}
		indentLess();
		
	} else
		xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_RESOURCE), xmlCharStrdup(getDNAComponentURI(com)));
	xmlTextWriterEndElement(WRITER);
}

static void writeCollection(Collection* col) {
	if (!col)
		return;
	xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_COLLECTION));
	if (!alreadyProcessed((void *)col)) {
		markProcessed((void *)col);
		int n;
		int num;
        
        // properties
        if (getCollectionURI(col))
            xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_ABOUT),        xmlCharStrdup(getCollectionURI(col)));
        if(getCollectionDisplayID(col))
            xmlTextWriterWriteElement(WRITER,   xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_DISPLAYID),   xmlCharStrdup(getCollectionDisplayID(col)));
        if (getCollectionName(col))
            xmlTextWriterWriteElement(WRITER,   xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_NAME), xmlCharStrdup(getCollectionName(col)));
        if (getCollectionDescription(col))
            xmlTextWriterWriteElement(WRITER,   xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_DESCRIPTION), xmlCharStrdup(getCollectionDescription(col)));
		
		// components
		DNAComponent* com;
		num = getNumDNAComponentsIn(col);
		if (num>0) {
			indentMore();
			for (n=0; n<num; n++) {
				xmlTextWriterStartElement(WRITER, xmlCharStrdup(NSPREFIX_SBOL ":" NODENAME_COMPONENT));
				com = getNthDNAComponentIn(col, n);
				indentMore();
				writeDNAComponent(com);
				indentLess();
				xmlTextWriterEndElement(WRITER);
			}
			indentLess();
		}

		// Copy a structured annotation as an xml node object from the base Document's xml_doc to 
		// the destination document
		xmlNode *node;
		xmlNode *node_copy;
		for (n = 0; n < getNumPointersInArray(col->base->base->xml_annotations); n++) {
			node = (xmlNode *)getNthPointerInArray(col->base->base->xml_annotations, n);
			node_copy = xmlDocCopyNode(node, OUTPUT, 1);
			indentMore();
			writeStructuredAnnotation(node_copy);
			indentLess();
		}
	} else
		xmlTextWriterWriteAttribute(WRITER, xmlCharStrdup(NSPREFIX_RDF ":" NODENAME_RESOURCE), xmlCharStrdup(getCollectionURI(col)));
	xmlTextWriterEndElement(WRITER);
}

/***********************
 * main write function
 ***********************/

void writeDocument(Document* doc) {
	int n;
	startSBOLDocument();
	addNamespacesToDocument(doc);

	// write collections
	Collection* col;
	for (n=0; n<getNumCollections(doc); n++) {
		col = getNthCollection(doc, n);
		if (!alreadyProcessed((void *)col))
			writeCollection(col);
	}

	// write components
	DNAComponent* com;
	for (n=0; n<getNumDNAComponents(doc); n++) {
		com = getNthDNAComponent(doc, n);
		if (!alreadyProcessed((void *)com))
			writeDNAComponent(com);
	}

	// At this point there shouldn't be anything left.
	// But in case there are orphaned DNASequences or
	// SequenceAnnotations, SBOL will write them out anyway
	// and fail the schema validation.
	
	// write orphaned sequences
	DNASequence* seq;
	for (n=0; n<getNumDNASequences(doc); n++) {
		seq = getNthDNASequence(doc, n);
		if (!alreadyProcessed((void *)seq))
			writeDNASequence(seq);
	}
	
	// write orphaned sequence annotations
	SequenceAnnotation* ann;
	for (n=0; n<getNumSequenceAnnotations(doc); n++) {
		ann = getNthSequenceAnnotation(doc, n);
		if (!alreadyProcessed((void *)ann))
			writeSequenceAnnotation(ann);
	}

	endSBOLDocument();
}

int writeDocumentToFile(Document *doc, const char* filename)
{
    writeDocument(doc);
    int returnVal = saveSBOLDocument(filename);
	cleanupSBOLWriter();
	return returnVal;
}

char* writeDocumentToString(Document *doc)
{
    writeDocument(doc);
    // WARNING: Does not check for proper xmlChar* allocation
    xmlChar* out;
    int s;
    xmlDocDumpMemory(OUTPUT, &out, &s);
    cleanupSBOLWriter();
    return (char *)out;
}


