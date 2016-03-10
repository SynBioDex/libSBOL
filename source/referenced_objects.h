#ifndef REFERENCED_OBJECTS_INCLUDED
#define REFERENCED_OBJECTS_INCLUDED

template <class SBOLClass>
class ReferencedObject : public Property < SBOLClass >
{
    
public:
    ReferencedObject(sbol_type type_uri = UNDEFINED, SBOLObject *property_owner = NULL, std::string dummy = "");  // All sbol:::Properties (and therefore OwnedObjects which are derived from Properties) must match this signature in order to put them inside an sbol:List<> container.  In this case, the third argument is just a dummy variable
    ReferencedObject(sbol_type type_uri, void *property_owner, SBOLObject& first_object);
    
    void add(SBOLClass& sbol_obj);
    void set(std::string uri);
    void set(SBOLClass& sbol_obj);
    SBOLClass& get(std::string object_id);
    std::string operator[] (const int nIndex);
    void addReference(const std::string uri);
    void addReference(const std::string uri_prefix, const std::string display_id);
    void addReference(const std::string uri_prefix, const std::string display_id, const std::string version);
    void setReference(const std::string uri);
    void setReference(const std::string uri_prefix, const std::string display_id);
    void setReference(const std::string uri_prefix, const std::string display_id, const std::string version);
#ifdef SWIG
protected:
#endif
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

template <class SBOLClass >
ReferencedObject< SBOLClass >::ReferencedObject(sbol_type type_uri, SBOLObject *property_owner, std::string dummy) :
Property<SBOLClass>(type_uri, property_owner, "<>")
{
    // Register Property in owner Object
    if (this->sbol_owner != NULL)
    {
        std::vector<std::string> property_store;
        this->sbol_owner->properties.insert({ type_uri, property_store });
    }
};

//    template <class SBOLClass>
//    void ReferencedObject<SBOLClass>::set(const std::string uri)
//    {
//        if (sbol_owner)
//        {
//            std::string current_value = this->sbol_owner->properties[type][0];
//            if (current_value[0] == '<')  //  this property is a uri
//            {
//                this->sbol_owner->properties[this->type][0] = "<" + new_value + ">";
//            }
//            else if (current_value[0] == '"') // this property is a literal
//            {
//                this->sbol_owner->properties[this->type][0] = "\"" + new_value + "\"";
//            }
//
//        }
//        validate((void *)&new_value);
//    };


template < class SBOLClass>
void ReferencedObject<SBOLClass>::set(std::string uri)
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

template < class SBOLClass>
void ReferencedObject<SBOLClass>::setReference(const std::string uri)
{
    this->set(uri);
};

// For compliant URIs
template < class SBOLClass>
void ReferencedObject<SBOLClass>::setReference(const std::string uri_prefix, const std::string display_id)
{
    SBOLClass dummy_obj = SBOLClass();
    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, dummy_obj.getClassName(dummy_obj.type), "1.0.0");
    this->set(compliant_uri);
};

// For compliant URIs
template < class SBOLClass>
void ReferencedObject<SBOLClass>::setReference(const std::string uri_prefix, const std::string display_id, const std::string version)
{
    SBOLClass dummy_obj = SBOLClass();
    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, dummy_obj.getClassName(dummy_obj.type), version);
    this->set(compliant_uri);
};


// Look up object in Document registry
template <class SBOLClass>
SBOLClass& ReferencedObject<SBOLClass>::get(std::string object_id)
{
    SBOLObject* obj = this->sbol_owner->doc->SBOLObjects[object_id];
    return (SBOLClass &)*obj;
};

template <class SBOLClass>
std::string ReferencedObject<SBOLClass>::operator[] (const int nIndex)
{
    std::vector<std::string> *reference_store = &this->sbol_owner->properties[this->type];
    return reference_store->at(nIndex);
};



template < class SBOLClass >
void ReferencedObject<SBOLClass>::addReference(const std::string uri)
{
    this->sbol_owner->properties[this->type].push_back(uri);
};

// For compliant URI's
template < class SBOLClass >
void ReferencedObject<SBOLClass>::addReference(const std::string uri_prefix, const std::string display_id)
{
    SBOLClass dummy_obj = SBOLClass();
    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, dummy_obj.getClassName(dummy_obj.type), "1.0.0");
    this->addReference(compliant_uri);
};

// For compliant URI's
template < class SBOLClass >
void ReferencedObject<SBOLClass>::addReference(const std::string uri_prefix, const std::string display_id, const std::string version)
{
    SBOLClass dummy_obj = SBOLClass();
    std::string compliant_uri = getCompliantURI(uri_prefix, display_id, dummy_obj.getClassName(dummy_obj.type), version);
    this->addReference(compliant_uri);
};


#endif