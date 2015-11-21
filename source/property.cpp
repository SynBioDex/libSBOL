#include "property.h"
#include <raptor2.h>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;
using namespace sbol;

template <typename LiteralType>
Property<LiteralType>::~Property()
{
};

void URIProperty::set(std::string new_value)
{
	if (sbol_owner && !new_value.empty())
	{
		sbol_owner->properties[type][0] = "<" + new_value + ">";
	}
	validate((void *)&new_value);
};

SBOLObject::~SBOLObject()
{
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
