#include "object.h"

#include <stdexcept>      // std::invalid_argument

#include <vector>

using namespace sbol;
using namespace std;

/// @TODO if the object is SBOL Compliant, update the identity
void VersionProperty::incrementMinor()
{
    int minor_version = this->minor();
    minor_version++;
    string new_version = to_string(this->major()) + "." + to_string(minor_version) + "." + to_string(this->patch());
    this->set(new_version);
};

/// @TODO if the object is SBOL Compliant, update the identity
void VersionProperty::incrementMajor()
{
    int major_version = this->major();
    major_version++;
    string new_version = to_string(major_version) + "." + to_string(this->minor()) + "." + to_string(this->patch());
    this->set(new_version);
};

/// @TODO if the object is SBOL Compliant, update the identity
void VersionProperty::incrementPatch()
{
    int patch_version = this->patch();
    patch_version++;
    string new_version = to_string(this->major()) + "." + to_string(this->minor()) + "." + to_string(patch_version);
    this->set(new_version);
};

void VersionProperty::decrementMinor()
{
};

void VersionProperty::decrementMajor()
{
};

void VersionProperty::decrementPatch()
{
};

/// @return The major version as an integer
/// Splits the version string by a delimiter and returns the major version number
int VersionProperty::major()
{
    vector<string> v = this->split('.');
    int major_version = stoi(v[0]);
    return major_version;
};

/// @return The minor version as an integer
/// Splits the version string by a delimiter and returns the minor version number
int VersionProperty::minor()
{
    vector<string> v = this->split('.');
    int minor_version;
    try
    {
        // bitset constructor throws an invalid_argument if initialized
        // with a string containing characters other than 0 and 1
        minor_version = stoi(v[1]);
    }
    catch (const std::invalid_argument& ia)
    {
        std::cerr << "Invalid minor version: " << ia.what() << "\nMinor version must be an int";
    }
    return minor_version;
};

/// @return The patch version as an integer
/// Splits the version string by a delimiter and returns the patch version
int VersionProperty::patch()
{
    vector<string> v = this->split('.');
    int patch_version;
    try
    {
        // bitset constructor throws an invalid_argument if initialized
        // with a string containing characters other than 0 and 1
        patch_version = stoi(v[2]);
    }
    catch (const std::invalid_argument& ia)
    {
        std::cerr << "Invalid patch version: " << ia.what() << "\nPatch number must be an int";
    }
    return patch_version;
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
    std::string compliant_uri = getCompliantURI(uri_prefix, sbol_class_name, display_id, "1.0.0");
    this->set(compliant_uri);
};

// For compliant URIs
void ReferencedObject::setReference(const std::string uri_prefix, const std::string display_id, const std::string version)
{
    std::string sbol_class_name = getClassName(this->reference_type_uri);
    std::string compliant_uri = getCompliantURI(uri_prefix, sbol_class_name, display_id, version);
    this->set(compliant_uri);
};

// For compliant URIs
void ReferencedObject::addReference(const std::string uri_prefix, const std::string display_id)
{
    std::string sbol_class_name = getClassName(this->reference_type_uri);
    std::string compliant_uri = getCompliantURI(uri_prefix, sbol_class_name, display_id, "1.0.0");
    this->addReference(compliant_uri);
};

// For compliant URI's
void ReferencedObject::addReference(const std::string uri_prefix, const std::string display_id, const std::string version)
{
    std::string sbol_class_name = getClassName(this->reference_type_uri);
    std::string compliant_uri = getCompliantURI(uri_prefix, sbol_class_name, display_id, version);
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


