#include "sboldocument.h"

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

using namespace sbol;
using namespace std;

void TopLevel::addToDocument(SBOLDocument& doc)
{
	doc.SBOLObjects[this->identity.get()] = this;
};

TopLevel& SBOLDocument::getTopLevel(string uri)
{
    // @TODO validate if object is TopLevel or else trigget a libSBOL error
	// @TODO return libSBOL error if URI not found
	return *(this->SBOLObjects[uri]);
};