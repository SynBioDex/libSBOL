///////////////////////////////////////////////////////////
/// @file
/// 
/// Gathers together all the SBOL functions so
/// they can be easily #included. Although the SBOL core
/// is separated into files for easier maintenance,
/// those files are interdependent, so it's probably
/// best to #include them as a group from here.
/// 
/// @todo make a lot of the functions static
///////////////////////////////////////////////////////////

#ifndef SBOL_HEADER
#define SBOL_HEADER

#include "prototypes.h"
#include "constants.h"
#include "property.h"
#include "array.h"
#include "sboldocument.h"
#include "toplevelobject.h"
#include "identifiedobject.h"
#include "documentedobject.h"
#endif
