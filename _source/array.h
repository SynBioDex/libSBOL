///////////////////////////////////////////////////////////
/// @file
/// Defines the PointerArray struct, as well as
/// functions for operating on it.
/// 
/// @todo Rename PointerArray to SBOLObjectArray?
/// @todo Actually convert it to hold SBOLObjects via casts?
///////////////////////////////////////////////////////////

#ifndef SBOL_ARRAY_HEADER
#define SBOL_ARRAY_HEADER

#define POINTERARRAY_INITIAL_LENGTH 10 ///< Number of pointers to allocate memory for initially.
#define POINTERARRAY_SCALING_FACTOR  2 ///< What to multiply/divide capacity by when growing/shrinking arrays.

#include "constants.h"
#include "prototypes.h"

/// A dynamic array of void pointers. Used anywhere a variable
/// number of SBOLObjects needs to be stored. It would be called
/// "SBOLObjectArray", except that descendants of SBOLObject
/// start with a pointer to their base struct rather than the
/// struct itself, so you can only cast part of them to
/// (SBOLObject *). That's probably fixable though.
struct _PointerArray {
	int numPointersInUse; ///< Number of pointers holding useful information.
	int numPointersTotal; ///< Number of pointers that can be stored before expanding the array.
	void** pointers;      ///< The actual array.
};

/// Create an empty PointerArray.
PointerArray* createPointerArray();

/// Delete a PointerArray.
/// This frees the array itself, but not the pointers.
void deletePointerArray(PointerArray* arr);

/// Add a new pointer to a PointerArray.
/// Anything works as long as you cast it to (void*)
void insertPointerIntoArray(PointerArray* arr, void* ptr);

/// Delete a pointer from a PointerArray.
/// This doesn't actually return the pointer;
/// for that you want getNthPointerInArray.
void removePointerFromArray(PointerArray* arr, int index);

/// Get the number of pointers stored in a PointerArray.
/// Returns -1 on failure.
int getNumPointersInArray(const PointerArray* arr);

/// Get the Nth pointer from a PointerArray.
/// Returns NULL on failure.
void* getNthPointerInArray(const PointerArray* arr, int n);

/// Get the index of a pointer stored in a PointerArray.
/// Returns -1 if the pointer isn't found.
int indexOfPointerInArray(const PointerArray* arr, const void* ptr);

/// Find out whether a PointerArray contains a certain pointer.
/// Returns -1 on failure.
int pointerContainedInArray(const PointerArray* arr, const void* ptr);

#endif
