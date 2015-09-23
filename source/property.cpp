#include "property.h"

#include <raptor2.h>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;
using namespace sbol;




sbol_type SBOLObject::getTypeURI() 
{
	return type;
}




//SBOLObject& OwnedObjects::get(int index)
//{
//	sbol_owner->owned_objects[index].front();
//};

void OwnedObjects< class SBOLClass >::remove(std::string uri)
{
};
