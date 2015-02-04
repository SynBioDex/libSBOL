#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sbol.h"

/************
 * Property
 ************/

Property *createProperty() {
	Property *pro = malloc(sizeof(Property));
	pro->letters = NULL;
	return pro;
}

void deleteProperty(Property *pro) {
	if (pro) {
		pro->letters = NULL;
		free(pro);
		pro = NULL;
	}
}

void setNumber(Property *pro, int num) {
	if (pro) {
		pro->number = num;
	}
}

void setLetters(Property *pro, const char *str) {
	if (pro) {
		pro->letters = realloc(pro->letters, sizeof(char) * (strlen(str)+1));
		strcpy(pro->letters, str);
	}
}

int getNumber(const Property *pro) {
	if (pro)
		return pro->number;
	else
		return -1; /// @todo decide if -1 is a good default
}

char *getLetters(const Property *pro) {
	if (!pro)
		return NULL;
	else
		return pro->letters;
}

/****************
 * TextProperty
 ****************/

TextProperty* createTextProperty() {
	TextProperty* pro = malloc(sizeof(TextProperty));
	pro->text = createProperty();
	return pro;
}

void deleteTextProperty(TextProperty* pro) {
	if (pro) {
		if (pro->text) {
			deleteProperty(pro->text);
			pro->text = NULL;
		}
		free(pro);
	}
}

int compareTextProperty(const TextProperty* pro1,
						const TextProperty* pro2) {
	if ((!pro1 && !pro2) || (!pro1->text && !pro2->text))
		return 1;
	else {
		char *text1 = (char *) getLetters(pro1->text);
		char *text2 = (char *) getLetters(pro2->text);
		if (!text1 && !text2)
			return 1;
		else if (!text1 || !text2)
			return 0;
		else {
			int result = strcmp(text1, text2);
			free(text1);
			free(text2);
			return result;
		}
	}
}

char* getTextProperty(const TextProperty* pro) {
	if (!pro || !pro->text)
		return NULL;
	char *data = (char *) getLetters(pro->text);
	if (!data)
		return NULL;
	char *output = malloc(sizeof(char) * strlen(data)+1);
	strcpy(output, data);
	return output;
}

/// @todo remove the pro->text != NULL restriction?
/// @todo warn that you need to free() anything from a Property
void setTextProperty(TextProperty* pro, const char* text) {
	if (!pro)
		return;
	else if (!text) {
		deleteProperty(pro->text);
		pro->text = createProperty();
	} else {
		setLetters(pro->text, text);
	}
}

void printTextProperty(const TextProperty* pro) {
	if (pro)
		printf("%s", (char *)pro->text);
}

/***************
 * URIProperty
 ***************/

int ENFORCE_URI_RULES = 0;


URIProperty* createURIProperty(SBOLDocument* doc) {
	if (!doc)
		return NULL;
	URIProperty* pro = malloc(sizeof(URIProperty));
	pro->doc = doc;
	pro->uri = createTextProperty();
	return pro;
}

void deleteURIProperty(URIProperty* pro) {
	if (pro) {
		if (pro->uri)
			deleteTextProperty(pro->uri);
		if (pro->doc)
			pro->doc = NULL;
		free(pro);
		pro = NULL;
	}
}

void setURIProperty(URIProperty* pro, const char* uri) {
	if (pro && pro->doc && uri)
		setTextProperty(pro->uri, uri);
}

char* getURIProperty(const URIProperty* pro) {
	if (pro)
		return (char *)getTextProperty(pro->uri);
	else
		return NULL;
}

char* augmentURI(char* uri, char* identifier) {
	char* augmented_uri;
	augmented_uri = malloc(strlen(uri) + strlen(identifier) + 2);
	sprintf(augmented_uri, "%s%s\0", uri, identifier); // append identifier to URI
	return (char *)augmented_uri;
}

char* trimURI(char* uri, char delimiter) {
	char* trimmed_uri;
	char current_char;
	int i;
	for (i = strlen(uri); i > -1; i--) {
		current_char = uri[i];
		if (current_char == delimiter) {
			trimmed_uri = malloc(i + 1);
			strncpy(trimmed_uri, uri, i);
			trimmed_uri[i + 1] = '\0';
		}
	}
	return trimmed_uri;
}

int compareURIProperty(const URIProperty* pro1,
					   const URIProperty* pro2) {
	if ((!pro1 && !pro2) || (!pro1->uri && !pro2->uri))
		return 0;
	else if (!pro1 || !pro2 || !pro1->uri || !pro2->uri)
		return -1;
	return compareTextProperty(pro1->uri, pro2->uri);
}

void activateURIRules() {
	ENFORCE_URI_RULES = 1;
}

void disableURIRules() {
	ENFORCE_URI_RULES = 0;
}

void printURIProperty(const URIProperty* pro) {
	if (pro)
		printTextProperty(pro->uri);
}

/***********************
 * NucleotidesProperty
 ***********************/

NucleotidesProperty *createNucleotidesProperty() {
	NucleotidesProperty *pro = malloc(sizeof(NucleotidesProperty));
	pro->nucleotides = createTextProperty();
	return pro;
}

void deleteNucleotidesProperty(NucleotidesProperty *pro) {
	if (pro) {
		if (pro->nucleotides)
			deleteTextProperty(pro->nucleotides);
		free(pro);
		pro = NULL;
	}
}

/// @todo restrict to setting valid nucleotides
void  setNucleotidesProperty(NucleotidesProperty *pro, const char *nucleotides) {
	if (pro)
		setTextProperty(pro->nucleotides, nucleotides);
}

char *getNucleotidesProperty(const NucleotidesProperty *pro) {
	if (pro)
		return getTextProperty(pro->nucleotides);
	else
		return NULL;
}

int compareNucleotidesProperty(const NucleotidesProperty *pro1,
							   const NucleotidesProperty *pro2) {
	if ((!pro1 && !pro2) || (!pro1->nucleotides && !pro2->nucleotides))
		return 0;
	if (!pro1 || !pro2 || !pro1->nucleotides || !pro2->nucleotides)
		return -1;
	return compareTextProperty(pro1->nucleotides, pro2->nucleotides);
}

/// @todo cut off printing of long sequnces at 50 chars or so?
void printNucleotidesProperty(const NucleotidesProperty *pro) {
	if (pro)
		printTextProperty(pro->nucleotides);
}

/********************
 * PositionProperty
 ********************/

PositionProperty* createPositionProperty() {
	PositionProperty* pro = malloc(sizeof(PositionProperty));
	pro->position = createProperty();
	setNumber(pro->position, -1);
	return pro;
}

void deletePositionProperty(PositionProperty* pro) {
	if (pro) {
		if (pro->position)
			deleteProperty(pro->position);
		free(pro);
	}
}

void setPositionProperty(PositionProperty* pro, int pos) {
	if (pro && pos >= -1)
		setNumber(pro->position, pos);
}

int getPositionProperty(const PositionProperty* pro) {
	if (pro)
		return getNumber(pro->position);
	else
		return -1; /// @todo good error value?
}

int comparePositionProperty(const PositionProperty* pro1,
							const PositionProperty* pro2) {
	if (!pro1 || !pro2) /// @todo check numbers too?
		return (pro1->position - pro2->position);
	else
		return -1;
}

void printPositionProperty(const PositionProperty* pro) {
	if (pro)
		printf("%i", getNumber(pro->position));
}

/********************
 * PolarityProperty
 ********************/

PolarityProperty* createPolarityProperty() {
	PolarityProperty* pro = malloc(sizeof(PolarityProperty));
	pro->polarity = createProperty();
	setPolarityProperty(pro, STRAND_FORWARD);
	return pro;
}

void deletePolarityProperty(PolarityProperty* pro) {
	if (pro) {
		if (pro->polarity)
			deleteProperty(pro->polarity);
		free(pro);
		pro = NULL;
	}
}

void setPolarityProperty(PolarityProperty* pro, int pol) {
	if (pro && pol >= STRAND_FORWARD && pol <= STRAND_REVERSE) {
			setNumber(pro->polarity, pol);
	}
}

int getPolarityProperty(const PolarityProperty* pro) {
	if (pro)
		return getNumber(pro->polarity);
	else
		return -1;
}

int comparePolarityProperty(const PolarityProperty* pro1,
							const PolarityProperty* pro2) {
	if (pro1 && pro2)
		return (pro1->polarity - pro2->polarity);
	else
		return -1;
}

void printPolarityProperty(const PolarityProperty* pro) {
	if (pro) {
		switch( getNumber(pro->polarity) ) {
			case STRAND_FORWARD:
				printf("+");
			case STRAND_BIDIRECTIONAL:
				printf("+-");
			case STRAND_REVERSE:
				printf("-");
			default:
				printf("?");
		}
	}
}

/********************
 * TypeProperty
 ********************/

TypeProperty* createTypeProperty(SBOLDocument* doc) {
    if (!doc)
        return NULL;
    TypeProperty* pro = malloc(sizeof(TypeProperty));
    pro->doc = doc;
    pro->uri = createURIProperty(doc);
    return pro;
}

void deleteTypeProperty(TypeProperty* pro) {
    if (pro) {
        if (pro->uri)
            deleteURIProperty(pro->uri);
        if (pro->doc)
            pro->doc = NULL;
    }
}

void setTypeProperty(TypeProperty* pro, const char* uri) {
    if (pro && uri)
        setURIProperty(pro->uri, uri);
}

char* getTypeProperty(const TypeProperty* pro) {
    if (pro)
        return getURIProperty(pro->uri);
    else
        return NULL;
}

int compareTypeProperty(const TypeProperty* pro1, const TypeProperty* pro2) {
    if ((!pro1 && !pro2) || (!pro1->uri && !pro2->uri))
        return 0;
    else if (!pro1 || !pro2 || !pro1->uri || !pro2->uri)
        return -1;
    return compareURIProperty(pro1->uri, pro2->uri);
}

void printTypeProperty(const TypeProperty* pro) {
    if (pro)
        printURIProperty(pro->uri);
}

