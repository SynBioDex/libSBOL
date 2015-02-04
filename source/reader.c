#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/xpath.h>

#include "array.h"
#include "document.h"
#include "dnasequence.h"
#include "sequenceannotation.h"
#include "dnacomponent.h"
#include "collection.h"
#include "reader.h"
#include "object.h"

#include "sbol.h"

// these are static mainly to avoid passing them around constantly
static xmlDoc          *DOCUMENT;
static xmlXPathContext *CONTEXT;
static Document        *DESTINATION;

/*********************
 * utility functions
 *********************/

static xmlChar *getNodeURI(xmlNode *node) {
	if (!node)
		return NULL;
	xmlChar *uri;
	// assume this is a normal node
	uri = xmlGetNsProp(node, BAD_CAST NODENAME_ABOUT, BAD_CAST NSURL_RDF);
	if (!uri)
		// nope, hopefully it's a reference node then
		uri = xmlGetNsProp(node, BAD_CAST NODENAME_RESOURCE, BAD_CAST NSURL_RDF);
	return uri;
}

static PointerArray *getNodesMatchingXPath(xmlNode *node, xmlChar *path) {
    if (!path)
        return NULL;

	xmlXPathObject *results_set;
	PointerArray *results_array;
	xmlNode *result_node;
	int n;
	
	// get results
    if (node)
        CONTEXT->node = node;
	results_set = xmlXPathEvalExpression(path, CONTEXT);
	if (!results_set)
		return NULL;
	
	// put them in the array
	results_array = createPointerArray();
	if (results_set->nodesetval && results_set->nodesetval->nodeNr > 0) {
		for (n=0; n < results_set->nodesetval->nodeNr; n++) {
			result_node = results_set->nodesetval->nodeTab[n];
			insertPointerIntoArray(results_array, result_node);
		}
	}
	
	// finish up
	xmlXPathFreeObject(results_set);
	CONTEXT->node = NULL;
	return results_array;
}

static xmlNode *getSingleNodeMatchingXPath(xmlNode *node, xmlChar *path) {
	PointerArray *results_array = getNodesMatchingXPath(node, path);
	if (!results_array)
		return NULL;
	else if (getNumPointersInArray(results_array) == 0) {
		deletePointerArray(results_array);
		return NULL;
	} else {
		if (getNumPointersInArray(results_array) > 1) {
			#ifdef SBOL_DEBUG_STATEMENTS
			printf("Got too many nodes matching xpath %s\n", (char *)path);
			#endif
		}
		xmlNode *result = getNthPointerInArray(results_array, 0);
		deletePointerArray(results_array);
		return result;
	}
}

static xmlChar *getContentsOfNodeMatchingXPath(xmlNode *node, xmlChar *path) {
	xmlNode *result = getSingleNodeMatchingXPath(node, path);
	if (result)
		return xmlNodeGetContent(result);
	else
		return NULL;
}

static xmlChar *getURIOfNodeMatchingXPath(xmlNode *node, xmlChar *path) {
	xmlNode *result = getSingleNodeMatchingXPath(node, path);
	if (result)
		return getNodeURI(result);
	else
		return NULL;
}

static void applyFunctionToNodesMatchingXPath(void (*fn)(xmlNode *), xmlNode *node, xmlChar *path) {
	if (!path)
		return;
	PointerArray *results = getNodesMatchingXPath(node, path);
	if (results) {
        if (getNumPointersInArray(results) > 0) {
            int n;
            for (n=0; n<getNumPointersInArray(results); n++)
                fn(getNthPointerInArray(results, n));
        }
	deletePointerArray(results);
    }
}

static void processNodes(void (*read)(xmlNode *), xmlChar *path) {
	applyFunctionToNodesMatchingXPath(read, NULL, path);
}

static int isSBOLNamespace(const xmlChar *uri) {
	return (strcmp(uri, NSURL_RDF) == 0 ||
		strcmp(uri, NSURL_RDFS) == 0 ||
		strcmp(uri, NSURL_SO) == 0 ||
		strcmp(uri, NSURL_SBOL) == 0);
}


/***************************
 * functions for reading
 * individual SBOL objects
 ***************************/

static void readSBOLCompoundObject(SBOLCompoundObject *obj, xmlNode *node) {
	xmlChar *path;
	xmlChar *content;

	// add displayID
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_DISPLAYID;
	if (content = getContentsOfNodeMatchingXPath(node, path)) {
		setSBOLCompoundObjectDisplayID(obj, (char *)content);
		xmlFree(content);
	}

	// add name
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_NAME;
	if (content = getContentsOfNodeMatchingXPath(node, path)) {
		setSBOLCompoundObjectName(obj, (char *)content);
		xmlFree(content);
	}

	// add description
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_DESCRIPTION;
	if (content = getContentsOfNodeMatchingXPath(node, path)) {
		setSBOLCompoundObjectDescription(obj, (char *)content);
		xmlFree(content);
	}
}

static void readDNASequenceContent(xmlNode *node) {
	xmlChar *uri;
	xmlChar *path;
	xmlChar *nt;
	DNASequence *seq;
	xmlNode *child_node; // structured xml annotation
	int i;

	// create DNASequence
	uri = getNodeURI(node);
	seq = createDNASequence(DESTINATION, (char *)uri);

	// add nucleotides
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_NUCLEOTIDES;
	if (nt = getContentsOfNodeMatchingXPath(node, path)) {
		setDNASequenceNucleotides(seq, (char *)nt);
		xmlFree(nt);
	}
	// scan other xml nodes attached to this Annotation for structured xml annotations
	// @TODO factor out this block of code.  This routine is generally used by each of the SBOL core objects
	// but it requires some custom knowledge of the calling object (in this case, Annotation)
	child_node = node->children;
	while (child_node) {
		if (child_node->ns && !isSBOLNamespace(child_node->ns->href)) {
			// copy xml tree and save it in the SBOLDocument object as a structural annotation 
			xmlNode* node_copy = xmlDocCopyNode(child_node, seq->doc->xml_doc, 1);
			node_copy = xmlAddChild(xmlDocGetRootElement(seq->doc->xml_doc), node_copy);
			i = xmlReconciliateNs(seq->doc->xml_doc, xmlDocGetRootElement(seq->doc->xml_doc));
			insertPointerIntoArray(seq->base->xml_annotations, node_copy);
		}
		child_node = child_node->next;
	}
	xmlFree(uri);
}

static void readSequenceAnnotationContent(xmlNode *node) {
	SequenceAnnotation *ann;
	xmlChar *ann_uri;
	xmlChar *path;
	xmlChar *contents;
	xmlNode *child_node; // structured xml annotation
	int i;

	// create SequenceAnnotation
	ann_uri = getNodeURI(node);
	ann = createSequenceAnnotation(DESTINATION, (char *)ann_uri);
	xmlFree(ann_uri);

	// add bioStart
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_BIOSTART;
	if (contents = getContentsOfNodeMatchingXPath(node, path)) {
		setSequenceAnnotationStart(ann, strToInt((char *)contents));
		xmlFree(contents);
	}

	// add bioEnd
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_BIOEND;
	if (contents = getContentsOfNodeMatchingXPath(node, path)) {
		setSequenceAnnotationEnd(ann, strToInt((char *)contents));
		xmlFree(contents);
	}

	// add strand
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_STRAND;
	if (contents = getContentsOfNodeMatchingXPath(node, path)) {
		setSequenceAnnotationStrand(ann, strToPolarity((char *)contents));
		xmlFree(contents);
	}

	// scan other xml nodes attached to this Annotation for structured xml annotations
	// @TODO factor out this block of code.  This routine is generally used by each of the SBOL core objects
	// but it requires some custom knowledge of the calling object (in this case, Annotation)
	child_node = node->children;
	while (child_node) {
		if (child_node->ns && !isSBOLNamespace(child_node->ns->href)) {
			// copy xml tree and save it in the SBOLDocument object as a structural annotation 
			xmlNode* node_copy = xmlDocCopyNode(child_node, ann->doc->xml_doc, 1);
			node_copy = xmlAddChild(xmlDocGetRootElement(ann->doc->xml_doc), node_copy);
			i = xmlReconciliateNs(ann->doc->xml_doc, xmlDocGetRootElement(ann->doc->xml_doc));
			insertPointerIntoArray(ann->base->xml_annotations, node_copy);
		}
		child_node = child_node->next;
	}
}

static void readSequenceAnnotationReferences(xmlNode *node) {
	SequenceAnnotation *ann;
	xmlChar *path;
	xmlChar *ann_uri;
	xmlChar *ref_uri;
	xmlNode *ref_node;
	PointerArray *results;
	int n;

 	// get SequenceAnnotation
	ann_uri = getNodeURI(node);
	ann = getSequenceAnnotation(DESTINATION, (char *)ann_uri);
	xmlFree(ann_uri);

	// add subComponent
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_SUBCOMPONENT
					 "/" NSPREFIX_SBOL ":" NODENAME_DNACOMPONENT;
	if (ref_uri = getURIOfNodeMatchingXPath(node, path)) {
		setSequenceAnnotationSubComponent(ann, getDNAComponent(DESTINATION, (char *)ref_uri));
		xmlFree(ref_uri);
	}

	// add precedes
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_PRECEDES;
	if (results = getNodesMatchingXPath(node, path)) {
		for (n=0; n<getNumPointersInArray(results); n++) {
			ref_node = (xmlNode *) getNthPointerInArray(results, n);
			ref_uri  = getNodeURI(ref_node);
			addPrecedesRelationship(ann, getSequenceAnnotation(DESTINATION, (char *)ref_uri));
			xmlFree(ref_uri);
		}
		deletePointerArray(results);
	}
}


static void readDNAComponentContent(xmlNode *node) {
    DNAComponent *com;
    xmlChar *com_uri;
	xmlChar *path;
	xmlChar *type_property;
	xmlNode *type_node;
	xmlNode *child_node; // structured xml annotation

	PointerArray *results;
	int i;

    // create DNAComponent
    com_uri = getNodeURI(node);
    com = createDNAComponent(DESTINATION, (char *)com_uri);
    xmlFree(com_uri);

    // add displayID, name, description
    readSBOLCompoundObject(com->base, node);
    
    // add type
	path = NSPREFIX_RDF ":" NODENAME_TYPE;
	if (results = getNodesMatchingXPath(node, path)) {
		type_node = (xmlNode *)getNthPointerInArray(results, 0);
		type_property = xmlGetNsProp(type_node, BAD_CAST NODENAME_RESOURCE, BAD_CAST NSURL_RDF);
		setDNAComponentType(com, (char *)type_property);
		xmlFree(results);
	}

	// scan other xml nodes attached to this DNAComponent for structured xml annotations
	// @TODO factor out this block of code.  This routine is generally used by each of the SBOL core objects
	// but it requires some custom knowledge of the calling object (in this case, DNAComponent)
	child_node = node->children;
	while (child_node) {
		if (child_node->ns && !isSBOLNamespace(child_node->ns->href)) {
			// copy xml tree and save it in the SBOLDocument object as a structural annotation 
			xmlNode* node_copy = xmlDocCopyNode(child_node, com->doc->xml_doc, 1);
			node_copy = xmlAddChild(xmlDocGetRootElement(com->doc->xml_doc), node_copy);
			i = xmlReconciliateNs(com->doc->xml_doc, xmlDocGetRootElement(com->doc->xml_doc));
			insertPointerIntoArray(com->base->base->xml_annotations, node_copy);
		}
		child_node = child_node->next;
	}

}

static void readDNAComponentReferences(xmlNode *node) {
    DNAComponent *com;
	xmlChar *path;
    xmlChar *com_uri;
    xmlChar *ref_uri;
    PointerArray *ref_nodes;
    xmlNode *ref_node;
    int n;

    // get DNAComponent
    com_uri = getNodeURI(node);
    com = getDNAComponent(DESTINATION, (char *)com_uri);
    xmlFree(com_uri);

    // add sequence
    path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_DNASEQUENCE_REF
    				 "/" NSPREFIX_SBOL ":" NODENAME_DNASEQUENCE;
    if (ref_uri = getURIOfNodeMatchingXPath(node, path)) {
        setDNAComponentSequence(com, getDNASequence(DESTINATION, (char *)ref_uri));
        xmlFree(ref_uri);
    }
    
    // add annotations
	path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_ANNOTATION
					 "/" NSPREFIX_SBOL ":" NODENAME_SEQUENCEANNOTATION;
    if (ref_nodes = getNodesMatchingXPath(node, path)) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addSequenceAnnotation(com, getSequenceAnnotation(DESTINATION, (char *)ref_uri));
            xmlFree(ref_uri);
        }
        deletePointerArray(ref_nodes);
    }
}

static void readCollectionContent(xmlNode *node) {
    Collection *col;
    xmlChar *col_uri;
	xmlNode *child_node; // structured xml annotation
	int i;

    // create Collection
    col_uri = getNodeURI(node);
    col = createCollection(DESTINATION, (char *)col_uri);
    xmlFree(col_uri);

    // add displayID, name, description
    readSBOLCompoundObject(col->base, node);

	// scan other xml nodes attached to this Collection for structured xml annotations
	// @TODO factor out this block of code.  This routine is generally used by each of the SBOL core objects
	// but it requires some custom knowledge of the calling object (in this case, Collection)
	child_node = node->children;
	while (child_node) {
		if (child_node->ns && !isSBOLNamespace(child_node->ns->href)) {
			// copy xml tree and save it in the SBOLDocument object as a structural annotation 
			xmlNode* node_copy = xmlDocCopyNode(child_node, col->doc->xml_doc, 1);
			node_copy = xmlAddChild(xmlDocGetRootElement(col->doc->xml_doc), node_copy);
			i = xmlReconciliateNs(col->doc->xml_doc, xmlDocGetRootElement(col->doc->xml_doc));
			insertPointerIntoArray(col->base->base->xml_annotations, node_copy);
		}
		child_node = child_node->next;
	}

}

static void readCollectionReferences(xmlNode *node) {
    Collection *col;
	xmlChar *path;
    xmlChar *col_uri;
    xmlChar *ref_uri;
    PointerArray *ref_nodes;
    xmlNode *ref_node;
    int n;

    // get Collection
    col_uri = getNodeURI(node);
    col = getCollection(DESTINATION, (char *)col_uri);
    xmlFree(col_uri);

    // add components
    path = BAD_CAST "./" NSPREFIX_SBOL ":" NODENAME_COMPONENT
    				 "/" NSPREFIX_SBOL ":" NODENAME_DNACOMPONENT;
    if (ref_nodes = getNodesMatchingXPath(node, path)) {
        for (n=0; n<getNumPointersInArray(ref_nodes); n++) {
            ref_node = (xmlNode *) getNthPointerInArray(ref_nodes, n);
            ref_uri = getNodeURI(ref_node);
            addDNAComponentToCollection(col, getDNAComponent(DESTINATION, (char *)ref_uri));
            xmlFree(ref_uri);
        }
        deletePointerArray(ref_nodes);
    }
}

/*************************
 * main parsing function
 *************************/

void readDocument(Document* destination, char* filename) {
	DESTINATION = destination;

	// parse
	safeXmlInitParser();
	DOCUMENT = xmlParseFile(filename);
	if (!DOCUMENT) {
		printf("Error reading %s\n", filename);
		return;
	}

	// validate
	if (!isValidSBOL(DOCUMENT)) {
		printf("%s is not a valid SBOL document.\n", filename);
		return;
	}
		
	// create XPath context
	CONTEXT = xmlXPathNewContext(DOCUMENT);
	xmlXPathRegisterNs(CONTEXT, NSPREFIX_SBOL, NSURL_SBOL);
	xmlXPathRegisterNs(CONTEXT, NSPREFIX_RDF, NSURL_RDF);

	#define GLOBAL_XPATH BAD_CAST "//" NSPREFIX_SBOL ":"

	// create all the SBOLObjects
	processNodes(readDNASequenceContent,        GLOBAL_XPATH NODENAME_DNASEQUENCE);
	processNodes(readSequenceAnnotationContent, GLOBAL_XPATH NODENAME_SEQUENCEANNOTATION);
	processNodes(readDNAComponentContent,       GLOBAL_XPATH NODENAME_DNACOMPONENT);
	processNodes(readCollectionContent,         GLOBAL_XPATH NODENAME_COLLECTION);
	
	// link them together with pointers
	processNodes(readSequenceAnnotationReferences, GLOBAL_XPATH NODENAME_SEQUENCEANNOTATION);
	processNodes(readDNAComponentReferences,       GLOBAL_XPATH NODENAME_DNACOMPONENT);
	processNodes(readCollectionReferences,         GLOBAL_XPATH NODENAME_COLLECTION);

	#undef GLOBAL_XPATH
	
	// clean up
	xmlXPathFreeContext(CONTEXT);
	xmlFreeDoc(DOCUMENT);
	DESTINATION = NULL;
	xmlCleanupParser();
}
