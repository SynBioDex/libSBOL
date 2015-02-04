///////////////////////////////////////////////////////////
/// @file
/// This file defines SBOL utility functions that don't
/// really fit in anywhere else. Nothing in here should
/// need to be exported.
/// 
/// @todo Don't export this stuff with the library.
///////////////////////////////////////////////////////////

#ifndef SBOL_UTILITIES_HEADER
#define SBOL_UTILITIES_HEADER

#include "constants.h"
#include "prototypes.h"

/// Print the specified number of tabs to stdout.
void indent(int tabs);

/// Convert an int to a string.
char *intToStr(int input);

/// Convert a string to an int.
int strToInt(const char *input);

/// Convert a char into a StrandPolarity value.
/// @param input Either '+', '-', or '*' (bidirectional)
/// @todo move to polarityproperty, writer, or types?
/// @todo better char for bidirectional?
int strToPolarity(const char *input);

/// Convert a StrandPolarity value into a char.
/// @param polarity An index in the StrandPolarity enum.
/// @return The corresponding char--either '+', '-', '*' (bidirectional),
///  or '?' (unknown/invalid input)
/// @todo better char for bidirectional?
char polarityToChar(int polarity);

/// Works around a bug involving libxml and MinGW.
/// Called at the beginning of parsing like regular xmlInitParser,
/// but also makes sure xmlFree won't crash the program.
/// @todo find a way not to export this?
SBOLAPIEXPORTS void safeXmlInitParser();

#endif
