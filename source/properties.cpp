#include "object.h"

#include <vector>

using namespace sbol;

ReferencedObject::ReferencedObject(sbol_type type_uri, SBOLObject *property_owner, std::string initial_value) :
URIProperty(type_uri, property_owner, initial_value)
{
    // Register Property in owner Object
    if (this->sbol_owner != NULL)
    {
        std::vector<std::string> property_store;
        this->sbol_owner->properties.insert({ type_uri, property_store });
    }
};

ReferencedObject::ReferencedObject(sbol_type type_uri, sbol_type reference_type_uri, SBOLObject *property_owner, std::string initial_value) :
    URIProperty(type_uri, property_owner, initial_value),
    reference_type(reference_type_uri)
{
    // Register Property in owner Object
    if (this->sbol_owner != NULL)
    {
        std::vector<std::string> property_store;
        this->sbol_owner->properties.insert({ type_uri, property_store });
    }
};

void ReferencedObject::set(std::string uri)
{
    if (this->sbol_owner)
    {
        //sbol_owner->properties[type].push_back( new_value );
        std::string current_value = this->sbol_owner->properties[this->type][0];
        if (current_value[0] == '<')  //  this property is a uri
        {
            this->sbol_owner->properties[this->type][0] = "<" + uri + ">";
        }
        else if (current_value[0] == '"') // this property is a literal
        {
            throw;
        }
        
    }
    //validate((void *)&uri);
};

void ReferencedObject::setReference(const std::string uri)
{
    this->set(uri);
};

std::string ReferencedObject::operator[] (const int nIndex)
{
    std::vector<std::string> *reference_store = &this->sbol_owner->properties[this->type];
    return reference_store->at(nIndex);
};


void ReferencedObject::addReference(const std::string uri)
{
    this->sbol_owner->properties[this->type].push_back("<" + uri + ">");
};


