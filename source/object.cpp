#include "object.h"
#include <raptor2.h>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;
using namespace sbol;

//template <class LiteralType>
//Property<LiteralType>::~Property()
//{
//};

//void URIProperty::set(std::string new_value)
//{
//	if (sbol_owner && !new_value.empty())
//	{
//		sbol_owner->properties[type][0] = "<" + new_value + ">";
//	}
//	validate((void *)&new_value);
//};

SBOLObject::~SBOLObject()
{
}

/// Use this method to destroy an SBOL object that is not contained by a parent Document.  If the object does have a parent Document, instead use doc.close() with the object's URI identity as an argument.
/// @TODO Recurse through child objects and delete them.
void SBOLObject::close()
{
    delete this;
};

sbol_type SBOLObject::getTypeURI() 
{
	return type;
};

std::string SBOLObject::getClassName(string type)
{
    std::size_t uri_subordinate_pos = type.find("#") + 1;
    if (uri_subordinate_pos != std::string::npos)
    {
        std::string sbol_class = type.substr(uri_subordinate_pos, type.size() - uri_subordinate_pos);
        return sbol_class;
    }
    else
        return type;
};

int SBOLObject::find(string uri)
{
    if (identity.get() == uri)
        return 1;
    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
    {
        vector<SBOLObject*>& store = i_store->second;
        for (auto i_obj = store.begin(); i_obj != store.end(); ++i_obj)
        {
            SBOLObject& obj = **i_obj;
            if (obj.find(uri))
                return 1;
        }
    }
    return 0;
};


//SBOLObject& OwnedObjects::get(int index)
//{
//	sbol_owner->owned_objects[index].front();
//};

//void OwnedObject< class SBOLClass >::remove(std::string uri)
//{
//};
