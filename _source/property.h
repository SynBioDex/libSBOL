///////////////////////////////////////////////////////////
/// @file
/// Defines a hierarchy of Properties,
/// which hold data for SBOLObjects. Although they don't
/// do much so far, this is where you would add restraints
/// on the getting and setting of specific values. For
/// example, you could have the NucleotidesProperty only
/// accept strings of a, c, t, g, and sometimes n.
///
/// @todo Make enums for any magic numbers
/// @todo See if separating docs into user, devel works.
///////////////////////////////////////////////////////////

#ifndef SBOL_PROPERTY_HEADER
#define SBOL_PROPERTY_HEADER

#include "sbol.h"

/************
 * Property
 ************/

/// Generic Property that forms the base for all the others.
/// Besides making the inheritance diagrams look nice, this provides
/// a hook for doing something whenever a Property is read or written.
/// It shouln't be used directly though because there's no flag for
/// telling whether it holds an int or a char *.
union _Property {
	int   number;
	char* letters;
};

/// Create an empty Property.
Property *createProperty();

/// Delete a Property.
/// If it holds a string, that needs to be freed separately.
void deleteProperty(Property *pro);

/// Store an int in a Property.
void setNumber(Property *pro, int num);

/// Retrieve an int stored in a Property.
int  getNumber(const Property *pro);

/// Store a string in a Property.
void  setLetters(Property *pro, const char *str);

/// Retrieve the string stored in a Property.
/// @return A new copy of the string that needs to be freed.
/// @todo Check that this one copies.
char *getLetters(const Property *pro);

/****************
 * TextProperty
 ****************/

/// Base struct for text-containing Properties.
/// Also used for the displayID, name, and descriptions
/// of SBOLCompoundObjects.
struct _TextProperty {
	Property *text;
};

/// Create an empty TextProperty.
TextProperty* createTextProperty();

/// Delete a TextProperty.
/// The stored text needs to be freed separately.
/// @todo Make sure that's true.
void deleteTextProperty(TextProperty* pro);

/// Store a string in a TextProperty.
void setTextProperty(TextProperty* pro, const char* text);

/// Retrieve the string stored in a TextProperty.
/// @return A new copy of the string that needs to be freed.
char* getTextProperty(const TextProperty* pro);

/// Compare two TextProperties for string equality.
/// @return -1 on failure. Otherwise, the result of strcmp()ing their contents.
int compareTextProperty(const TextProperty* pro1, const TextProperty* pro2);

/// Print a TextProperty to stdout.
void printTextProperty(const TextProperty* pro);

/***************
 * URIProperty
 ***************/

/// global flag used to determine if new URIs should be minted according to an automatic naming convention
extern int ENFORCE_URI_RULES;

/*
/// A TextProperty that only allows creation
/// of values that aren't already in use as the
/// uri of an SBOLObject.
struct _URIProperty {
	//Document* doc;     ///< For verifying uniqueness
	TextProperty* uri;
};

/// Create an empty URIProperty.
URIProperty* createURIProperty(Document* doc);

/// Delete a URIProperty.
/// The stored URI needs to be freed separately.
/// @todo Make sure that's true.
void deleteURIProperty(URIProperty* pro);

/// Store a string in a URIProperty.
/// This will fail if the same URI is already used by an SBOLObject.
void setURIProperty(URIProperty* pro, const char* uri);

/// Retrieve the string stored in a URIProperty.
/// @return A new copy of the string that needs to be freed.
char* getURIProperty(const URIProperty* pro);

/// Append a string to the given uri.
/// @return A new string with the modified uri.
char* augmentURI(char* uri, char* identifier);

char* trimURI(char* uri, char delimiter);

/// Compare two URIProperties for string equality.
/// @return -1 on failure. Otherwise, the result of strcmp()ing their contents.
/// @todo Check that that's true.
int compareURIProperty(const URIProperty* pro1, const URIProperty* pro2);

void activateURIRules();

void disableURIRules();

/// Print a URIProperty to stdout.
void printURIProperty(const URIProperty* pro);

*/

/***********************
 * NucleotidesProperty
 ***********************/

/// A TextProperty that represents a series of nucleotides.
/// So far, it doesn't enforce storing reasonable values.
struct _NucleotidesProperty {
	TextProperty *nucleotides;
};

/// Create an empty NucleotidesProperty.
NucleotidesProperty *createNucleotidesProperty();

/// Delete a NucleotidesProperty.
/// The stored text needs to be freed separately.
void deleteNucleotidesProperty(NucleotidesProperty *pro);

/// Store a string in a NucleotidesProperty.
/// So far, this doesn't check that the string is a reasonable DNA sequence.
void  setNucleotidesProperty(NucleotidesProperty *pro, const char *nucleotides);

/// Retrieve the string stored in a NucleotidesProperty.
/// @return A new copy of the string that needs to be freed.
char *getNucleotidesProperty(const NucleotidesProperty *pro);

/// Compare two NucleotidesProperties for string equality.
/// @return -1 on failure. Otherwise, the result of strcmp()ing their contents.
int compareNucleotidesProperty(const NucleotidesProperty *pro1, const NucleotidesProperty *pro2);

/// Print a NucleotidesProperty to stdout.
void printNucleotidesProperty(const NucleotidesProperty *pro);

/********************
 * PositionProperty
 ********************/

/// Represents an index in a DNA sequence.
/// It only allows non-negative values.
/// There should also be other restrictions, but they
/// only make sense for groups, not individual PositionProperties.
/// For example, SequenceAnnotation->bioEnd should be at least
/// as large as SequenceAnnotation->bioStart.
/// @todo Is 0 a valid position?
struct _PositionProperty {
	Property* position;
};

/// Create an empty PositionProperty.
PositionProperty* createPositionProperty();

/// Delete a PositionProperty.
void deletePositionProperty(PositionProperty* pro);

/// Store an int in a PositionProperty.
/// This will fail if the int is negative.
void setPositionProperty(PositionProperty* pro, const int value);

/// Retrieve the int stored in a PositionProperty.
int getPositionProperty(const PositionProperty* pro);

/// Compare two PositionProperties numerically.
/// @return -1 on failure. Otherwise, the difference between them.
int comparePositionProperty(const PositionProperty* pro1, const PositionProperty* pro2);

/// Print a PositionProperty to stdout.
void printPositionProperty(const PositionProperty* pro);

/********************
 * PolarityProperty
 ********************/

/// IntProperty that only allows StrandPolarity values.
/// 1 indicates the positive strand relative to the parent
/// component, and 0 indicates the reverse complement.
/// @todo rename to StrandProperty? or OrientationProperty?
struct _PolarityProperty {
	Property* polarity;
};

/// Create an empty PolarityProperty.
PolarityProperty* createPolarityProperty();

/// Delete a PolarityProperty.
void deletePolarityProperty(PolarityProperty* pro);

/// Store an int in a PolarityProperty.
/// Fails unless that int matches one of the values in the StrandPolarity enum.
void setPolarityProperty(PolarityProperty* pro, const int value);

/// Retrieve the int stored in a PolarityProperty.
/// @return An int corresponding to a value in the StrandPolarity enum.
int getPolarityProperty(const PolarityProperty* pro);

/// Compare two PositionProperties.
/// @return -1 on failure. Otherwise, the difference between them.
int comparePolarityProperty(const PolarityProperty* pro1, const PolarityProperty* pro2);

/// Print a PolarityProperty to stdout.
void printPolarityProperty(const PolarityProperty* pro);

/********************
 * TypeProperty
 ********************/
/*
/// Type property that stores document and uri for part type
struct _TypeProperty {
    //Document* doc;
    URIProperty* uri;
};

/// Create an empty TypeProperty
TypeProperty* createTypeProperty(Document* doc);

/// Delete a TypeProperty
void deleteTypeProperty(TypeProperty* pro);

/// Store a uri in a TypeProperty
void setTypeProperty(TypeProperty* pro, const char* uri);

/// Retrieve the uri stored in a TypeProperty
/// @return The uri corresponding to value in TypeProperty
char* getTypeProperty(const TypeProperty* pro);

/// Compare two TypeProperties for uri equality
/// @return 0 if uri's don't exsit, -1 on failure.
int compareTypeProperty(const TypeProperty* pro1, const TypeProperty* pro2);

/// Print a TypeProperty to stdout
void printTypeProperty(const TypeProperty* pro);
*/
#endif
