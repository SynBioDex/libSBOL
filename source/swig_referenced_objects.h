#ifndef SWIG_REFERENCED_OBJECTS_INCLUDED
#define SWIG_REFERENCED_OBJECTS_INCLUDED

#ifdef SBOL_GENERATE_PY
#pragma message ("Including specialized SWIG interface for sbol::ReferencedObjects. Parts of the default code base will be disabled.")

#include "object.h"

using namespace sbol;

class ReferencedObject : public URIProperty
{
    
public:
    ReferencedObject(sbol_type type_uri = UNDEFINED, SBOLObject *property_owner = NULL, std::string initial_value = "");  // All sbol:::Properties (and therefore OwnedObjects which are derived from Properties) must match this signature in order to put them inside an sbol:List<> container.  In this case, the third argument is just a dummy variable
    //ReferencedObject(sbol_type type_uri, void *property_owner, SBOLObject& first_object);
    
    //void add(SBOLClass& sbol_obj);
    void set(std::string uri);
    //void set(SBOLClass& sbol_obj);
    //SBOLClass& get(std::string object_id);
    std::string operator[] (const int nIndex);
    void addReference(const std::string uri);
    //void addReference(const std::string uri_prefix, const std::string display_id);
    //void addReference(const std::string uri_prefix, const std::string display_id, const std::string version);
    void setReference(const std::string uri);
    //void setReference(const std::string uri_prefix, const std::string display_id);
    //void setReference(const std::string uri_prefix, const std::string display_id, const std::string version);
protected:
    class iterator : public std::vector<std::string>::iterator
    {
    public:
        iterator(typename std::vector<std::string>::iterator i_str = std::vector<std::string>::iterator()) : std::vector<std::string>::iterator(i_str)
        {
        }
    };
    
    iterator begin()
    {
        std::vector<std::string> *object_store = &this->sbol_owner->properties[this->type];
        return iterator(object_store->begin());
    };
    
    iterator end()
    {
        std::vector<std::string> *object_store = &this->sbol_owner->properties[this->type];
        return iterator(object_store->end());
    };
    
    std::vector<std::string>::iterator python_iter;
};


// For compliant URIs
//template < class SBOLClass>
//void ReferencedObject<SBOLClass>::setReference(const std::string uri_prefix, const std::string display_id)
//{
//    SBOLClass dummy_obj = SBOLClass();
//    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, dummy_obj.getClassName(dummy_obj.type), "1.0.0");
//    this->set(compliant_uri);
//};
//
//// For compliant URIs
//template < class SBOLClass>
//void ReferencedObject<SBOLClass>::setReference(const std::string uri_prefix, const std::string display_id, const std::string version)
//{
//    SBOLClass dummy_obj = SBOLClass();
//    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, dummy_obj.getClassName(dummy_obj.type), version);
//    this->set(compliant_uri);
//};
//
//
//// Look up object in Document registry
//template <class SBOLClass>
//SBOLClass& ReferencedObject<SBOLClass>::get(std::string object_id)
//{
//    SBOLObject* obj = this->sbol_owner->doc->SBOLObjects[object_id];
//    return (SBOLClass &)*obj;
//};


// For compliant URI's
//template < class SBOLClass >
//void ReferencedObject<SBOLClass>::addReference(const std::string uri_prefix, const std::string display_id)
//{
//    SBOLClass dummy_obj = SBOLClass();
//    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, dummy_obj.getClassName(dummy_obj.type), "1.0.0");
//    this->addReference(compliant_uri);
//};
//
//// For compliant URI's
//template < class SBOLClass >
//void ReferencedObject<SBOLClass>::addReference(const std::string uri_prefix, const std::string display_id, const std::string version)
//{
//    SBOLClass dummy_obj = SBOLClass();
//    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, dummy_obj.getClassName(dummy_obj.type), version);
//    this->addReference(compliant_uri);
//};
//
//

#endif
#endif