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
	//std::hash<string> hash_fn;
	//std::size_t uri_hash = hash_fn(uri);
	//return *(this->SBOLObjects[uri_hash]);
	return *(this->SBOLObjects[uri]);
};