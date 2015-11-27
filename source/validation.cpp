#include "sbol.h"
#include <iostream>

using namespace sbol;
using namespace std;

void sbol::validation_rule_10202(void *sbol_obj, void *arg)
{
	cout << "Testing validation_rule_10202" << endl;

	// The identity property of an Identified object MUST be globally unique.
	Identified *identified_obj = (Identified *)sbol_obj;
	string new_id;

	if (arg != NULL)
	{
		new_id = *static_cast<std::string*>(arg);
	}
	if (identified_obj->doc)
	{
		if (identified_obj->doc->SBOLObjects.find(new_id) != identified_obj->doc->SBOLObjects.end())  // If the new identity is already in the document throw an error
		{
			throw SBOLError(DUPLICATE_URI_ERROR, "Duplicate URI");
		}
	}
};