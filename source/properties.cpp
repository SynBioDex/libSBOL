#include "object.h"

#include <vector>

using namespace sbol;
using namespace std;



void VersionProperty::incrementMinor()
{};
void VersionProperty::incrementMajor()
{};
void VersionProperty::incrementPatch()
{};
void VersionProperty::decrementMinor()
{};
void VersionProperty::decrementMajor()
{};
void VersionProperty::decrementPatch()
{};
int VersionProperty::major()
{
    vector<string> v = this->split('.');
    return stoi(v[0]);
};

int VersionProperty::minor()
{
    return 0;
};

int VersionProperty::patch()
{
    return 0;
};


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

vector<string> VersionProperty::split(const char c)
{
      // Adapted from C++ cookbook
    const string& s = this->get();
    vector<string> v;

    string::size_type i = 0;
    string::size_type j = s.find(c);

    while (j != string::npos)
    {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);
        if (j == string::npos)
            v.push_back(s.substr(i, s.length()));
    }
    return v;
}

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


