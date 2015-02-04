#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>

#include "utilities.h"

void indent(int tabs) {
    if (tabs<0)
        tabs = 0;
    int i;
    for (i=0; i<tabs; i++)
        printf("\t");
}

char* intToStr(int input) {
	int i;
	int digits;
	int lastDigit;
	char* output;
	// determine number of digits
	digits = 0;
	i = input;
	while (i>0) {
		i /= 10;
		digits++;
	}
	if (digits==0) {
		// create a single-char string
		output = malloc(sizeof(char)*2);
		output[0] = (char) (((int)'0')+input);
		output[1] = '\0';
	} else {
		// create string to hold that many chars
		output = malloc(sizeof(char) * (digits+1));
		// copy over each digit as a char
		for (i=digits-1; i>=0; i--) {
			lastDigit = input%10;
			output[i] = (char) (((int)'0')+lastDigit);
			input /= 10;
		}
		output[digits] = '\0';
	}
	return output;
}

int strToInt(const char *input) {
	return atoi(input);
}

// TODO move to polarityproperty
int strToPolarity(const char *input) {
	if (!input)
		return -1; /// @todo better null value?
	else if (input[0] == '+')
		return STRAND_FORWARD;
	else
		return STRAND_REVERSE;
}

// TODO move to polarityproperty
char polarityToChar(int polarity) {
	if (polarity == STRAND_FORWARD)
		return '+';
    else if (polarity == STRAND_BIDIRECTIONAL)
        return '*'; /// @todo better char for that?
	else if (polarity == STRAND_REVERSE)
		return '-';
    else
        return '?';
}

void safeXmlInitParser() {
	xmlInitParser();
	
	// This is a workaround for a problem with libxml2 and MinGW
	// google: "using libxml2 on MinGW - xmlFree crashes"
	if (!xmlFree)
		xmlMemGet( &xmlFree, &xmlMalloc, &xmlRealloc, NULL );

	// This initializes the library and checks potential ABI mismatches
	// between the version it was compiled for and the actual shared
	// library used.
	/// @todo Find out if this really helps anything.
	LIBXML_TEST_VERSION	
}

