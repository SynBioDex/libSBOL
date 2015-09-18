#include "property.h"

#include <raptor2.h>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;
using namespace sbol;


extern unordered_map<string, SBOLObject&(*)()> SBOL_DATA_MODEL_REGISTER =
{
	std::make_pair("test", &create<SBOLObject>)
};

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
