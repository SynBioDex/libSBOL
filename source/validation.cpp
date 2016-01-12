#include "sbol.h"
#include <iostream>

using namespace sbol;
using namespace std;

/* The identity property of an Identified object MUST be globally unique. */
void sbol::sbol_rule_10202(void *sbol_obj, void *arg)
{
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

/*	The definition property MUST NOT refer to the same ComponentDefinition as the one that contains the
ComponentInstance.Furthermore, ComponentInstance objects MUST NOT form a cyclical chain of references
via their definition properties and the ComponentDefinition objects that contain them.For example, consider
the ComponentInstance objects A and B and the ComponentDefinition objects X and Y.The reference chain “X
contains A, A is defined by Y, Y contains B, and B is defined by X” is cyclical. */
void sbol::libsbol_rule_1(void *sbol_obj, void *arg)
{
	cout << "Testing internal validation rules" << endl;
};