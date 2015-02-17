#include <stdlib.h>
#include <stdio.h>

#include "array.h"

PointerArray* createPointerArray() {
	PointerArray* arr = malloc(sizeof(PointerArray));
	arr->numPointersInUse = 0;
	arr->numPointersTotal = POINTERARRAY_INITIAL_LENGTH;
	arr->pointers = calloc(POINTERARRAY_INITIAL_LENGTH, sizeof(void*));
	#ifdef SBOL_DEBUG_STATEMENTS
	int n;
	for (n=0; n<POINTERARRAY_INITIAL_LENGTH; n++)
		if (arr->pointers[n])
			printf("PointerArray not initialized properly\n");
	#endif
	return arr;
}

void deletePointerArray(PointerArray* arr) {
	if (arr) {
		if (arr->numPointersInUse) arr->numPointersInUse = 0;
		if (arr->numPointersTotal) arr->numPointersTotal = 0;
		if (arr->pointers) {
			free(arr->pointers);
			arr->pointers = NULL;
		}
		#ifdef SBOL_DEBUG_STATEMENTS
		if (arr->numPointersInUse || 
			arr->numPointersTotal || 
			arr->pointers)
			printf("PointerArray deleted improperly\n");
		#endif
		free(arr);
		arr = NULL;
	}
}

int getNumPointersInArray(const PointerArray* arr) {
	if (arr)
		return arr->numPointersInUse;
	else
		return -1;
}

int indexOfPointerInArray(const PointerArray* arr, const void* ptr) {
	if (arr && ptr) {
		int n;
		for (n=0; n < getNumPointersInArray(arr); n++)
			if (getNthPointerInArray(arr, n) == ptr)
				return n;
		return -1;
	}
	#ifdef SBOL_DEBUG_STATEMENTS
	else {
		if (!arr)
			printf("Tried to get index of pointer in NULL array\n");
		else
			printf("Tried to get array index of NULL pointer\n");
		return -1;
	}
	#endif
}

int pointerContainedInArray(const PointerArray* arr, const void* ptr) {
    return (int) indexOfPointerInArray(arr, ptr) >= 0;
}

static void resizePointerArray(PointerArray* arr, int capacity) {
	if (arr) {
		if (capacity < POINTERARRAY_INITIAL_LENGTH)
			return;
		arr->numPointersTotal = capacity;
		arr->pointers = realloc(arr->pointers, capacity * sizeof(void*));
	}
	#ifdef SBOL_DEBUG_STATEMENTS
	else
		printf("Tried to resize NULL array\n");
	#endif
}

static void expandPointerArray(PointerArray* arr) {
	if (arr) {
		int capacity;
		if (arr->numPointersTotal < POINTERARRAY_INITIAL_LENGTH)
			capacity = POINTERARRAY_INITIAL_LENGTH;
		else
			capacity = arr->numPointersTotal * POINTERARRAY_SCALING_FACTOR;
		resizePointerArray(arr, capacity);
	}
	#ifdef SBOL_DEBUG_STATEMENTS
	else
		printf("Tried to expand NULL array\n");
	#endif
}

static void shrinkPointerArray(PointerArray* arr) {
	if (arr) {
		if (getNumPointersInArray(arr) > POINTERARRAY_INITIAL_LENGTH * POINTERARRAY_SCALING_FACTOR)
			resizePointerArray(arr, arr->numPointersTotal / POINTERARRAY_SCALING_FACTOR);
	}
	#ifdef SBOL_DEBUG_STATEMENTS
	else
		printf("Tried to shrink NULL array\n");
	#endif
}

void removePointerFromArray(PointerArray* arr, int index) {
	if (arr && getNumPointersInArray(arr) > index && index >= 0) {
	
		// shift everything over, deleting array[index]
		int n;
		for (n=index+1; n < getNumPointersInArray(arr); n++)
			arr->pointers[n-1] = arr->pointers[n];
		arr->pointers[ --(arr->numPointersInUse) ] = NULL;

		// if array is getting small, shrink it
		if (getNumPointersInArray(arr) == arr->numPointersTotal / POINTERARRAY_SCALING_FACTOR)
			shrinkPointerArray(arr);
	}
	
	#ifdef SBOL_DEBUG_STATEMENTS
	else if (!arr)
		printf("Tried to remove pointer from NULL array\n");
	else
		printf("Tried to remove pointer from invalid array index\n");
	#endif
}

void insertPointerIntoArray(PointerArray* arr, void* ptr) {
	if (arr && ptr) {
	
		// if array is full, expand it
		if (getNumPointersInArray(arr) == arr->numPointersTotal)
			expandPointerArray(arr);
		
		// insert ptr
		arr->pointers[ getNumPointersInArray(arr) ] = ptr;
		arr->numPointersInUse++;
	}
	
	#ifdef SBOL_DEBUG_STATEMENTS
	else if (!arr)
		printf("Tried to insert pointer into NULL array\n");
	else
		printf("Tried to insert NULL pointer into array\n");
	#endif
}

void* getNthPointerInArray(const PointerArray* arr, int n) {
	if (arr && getNumPointersInArray(arr) > n && n >= 0)
		return arr->pointers[n];
	else {
		#ifdef SBOL_DEBUG_STATEMENTS
		if (!arr)
			printf("Tried to get pointer from NULL array\n");
		else
			printf("Tried to get pointer from invalid array index\n");
		#endif
		return NULL;
	}
}
