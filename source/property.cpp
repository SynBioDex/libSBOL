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
