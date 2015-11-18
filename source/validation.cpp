#include "validation.h"
#include "sbol.h"
#include <iostream>

using namespace sbol;
using namespace std;

void sbol::validation_rule_10202(void *sbol_obj)
{
	Identified *identified_obj = (Identified *)sbol_obj;
	if (identified_obj->doc->SBOLObjects.find("f") == identified_obj->doc->SBOLObjects.end()) {
		// not found
	}
	else {
		// found
	}
	cout << "Testing validation_rule_10202" << endl;
	//SBOLObject &owner_obj = (SBOLObject &)validation_target;
	//cout << "Testing validation rule on " << owner_obj.identity.get() << endl;
};