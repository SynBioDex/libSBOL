///////////////////////////////////////////////////////////
/// @file
/// This file contains functions for writing the SBOL core
/// to an XML file. Only writeDocument is meant to be
/// exported; everything else supports it.
///////////////////////////////////////////////////////////

#ifndef SBOL_WRITER_HEADER
#define SBOL_WRITER_HEADER

#include "constants.h"
#include "prototypes.h"

/************************
 * utility functions for
 * setting up, writing,
 * and tearing down
 ************************/

/// Increase the indent level of the WRITER.
static void indentMore();

/// Decrease the indent level of the WRITER.
static void indentLess();

/// Set up everything for writing.
static void createSBOLWriter();

/// Clean up after the writer.
/// This doesn't delete SBOLObjects;
/// for that you also want to cleanupSBOLCore()
static void cleanupSBOLWriter();

/// Write the document header.
static void startSBOLDocument();

/// Write closing tags.
static void endSBOLDocument();

/// Save the finished document to a file.
/// Most of the "writing" is actually to a memory
/// location; this validates the document in
/// memory and copies it to disk.
static int saveSBOLDocument(const char* filename);

/************************************
 * functions for writing individual
 * SBOLObjects to the WRITER
 ************************************/

/// Write a DNASequence to the WRITER.
static void writeDNASequence(DNASequence* seq);

/// Write a SequenceAnnotation to the WRITER.
static void writeSequenceAnnotation(SequenceAnnotation* ann);

/// Write a DNAComponent to the WRITER.
static void writeDNAComponent(DNAComponent* com);

/// Write a Collection to the WRITER.
static void writeCollection(Collection* col);

/***********************
 * main write function
 ***********************/

/// Write document to static xmlDoc
void writeDocument(Document* doc);

/// Create, validate, and save an XML document based on
/// the SBOLObjects currently in memory. Those objects
/// still need to be deleted afterwards.
SBOLAPIEXPORTS int writeDocumentToFile(Document* doc, const char* filename);

/// Create and return contents of XML written for SBOLObjects
/// currently in memory. Does not validate xml
SBOLAPIEXPORTS char* writeDocumentToString(Document* doc);

#endif
