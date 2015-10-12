#include "property.h"

#include <raptor2.h>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;
using namespace sbol;


SBOLObject::~SBOLObject()
{
	delete &properties;
	while (owned_objects.size() > 0)
	{
		if (!owned_objects.begin()->second.empty())
		{
			vector<SBOLObject*> *object_store = &owned_objects.begin()->second;
			while (object_store->size() > 0)
			{
				delete &object_store->begin();
			}
		}
		owned_objects.erase(owned_objects.begin());
	}
}

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
