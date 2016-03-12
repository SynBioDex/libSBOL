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
    reference_type_uri(reference_type_uri)
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


// For compliant URIs
void ReferencedObject::setReference(const std::string uri_prefix, const std::string display_id)
{
    std::string sbol_class_name = getClassName(this->reference_type_uri);
    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, sbol_class_name, "1.0.0");
    this->set(compliant_uri);
};

// For compliant URIs
void ReferencedObject::setReference(const std::string uri_prefix, const std::string display_id, const std::string version)
{
    std::string sbol_class_name = getClassName(this->reference_type_uri);
    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, sbol_class_name, version);
    this->set(compliant_uri);
};

// For compliant URIs
void ReferencedObject::addReference(const std::string uri_prefix, const std::string display_id)
{
    std::string sbol_class_name = getClassName(this->reference_type_uri);
    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, sbol_class_name, "1.0.0");
    this->addReference(compliant_uri);
};

// For compliant URI's
void ReferencedObject::addReference(const std::string uri_prefix, const std::string display_id, const std::string version)
{
    std::string sbol_class_name = getClassName(this->reference_type_uri);
    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, sbol_class_name, version);
    this->addReference(compliant_uri);
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


