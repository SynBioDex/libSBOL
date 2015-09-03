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

OwnedObjects::OwnedObjects(sbol_type type_uri, void *property_owner)
{
	type = type_uri;
	sbol_owner = ((SBOLObject *)property_owner);

	// Register Property in owner Object
	if (sbol_owner != NULL)
	{
		std::vector<sbol::SBOLObject*> object_store;
		sbol_owner->owned_objects.insert({ type_uri, object_store });
	}
};

OwnedObjects::OwnedObjects(SBOLObject& first_object, sbol_type type_uri, void *property_owner)
{
};

void OwnedObjects::add(SBOLObject& sbol_obj)
{
	sbol_owner->owned_objects[type].push_back(&sbol_obj);
};

SBOLObject& OwnedObjects::get(std::string uri)
{
	// Iterate through each SBOLObject in list until the object matching the uri is found
	return *sbol_owner->owned_objects[type].front();
};

//SBOLObject& OwnedObjects::get(int index)
//{
//	sbol_owner->owned_objects[index].front();
//};

void OwnedObjects::remove(std::string uri)
{
};
