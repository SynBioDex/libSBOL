#ifndef PROPERTIES_INCLUDED
#define PROPERTIES_INCLUDED

#include "property.h"

#include <raptor2.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>

namespace sbol
{
    class URIProperty : public Property<std::string>
	{
	public:
		URIProperty(sbol_type type_uri = UNDEFINED, void *property_owner = NULL, std::string initial_value = "") :
			Property(type_uri, property_owner, "<" + initial_value + ">")
		{
		}
	};

	class TextProperty : public Property<std::string>
	{
	public:
		TextProperty(sbol_type type_uri, void *property_owner, std::string initial_value = "") :
			Property(type_uri, property_owner, "\"" + initial_value + "\"")
		{
		}
	};

	class IntProperty : public Property<int>
	{
	public:
		IntProperty(sbol_type type_uri, void *property_owner, int initial_value = 0) :
			Property(type_uri, property_owner, initial_value)
		{
		}
	};


	/* Corresponding to black diamonds in UML diagrams.  Creates a composite out of two or more classes */
	template <class SBOLClass>
	class OwnedObject : public Property<SBOLClass>
	{

	public:
        OwnedObject(sbol_type type_uri = UNDEFINED, SBOLObject *property_owner = NULL, std::string dummy = "");  // All sbol:::Properties (and therefore OwnedObjects which are derived from Properties) must match this signature in order to put them inside an sbol:List<> container.  In this case, the third argument is just a dummy variable
		OwnedObject(sbol_type type_uri, void *property_owner, SBOLObject& first_object);

		void add(SBOLClass& sbol_obj);
        void set(SBOLClass& sbol_obj);
		SBOLClass& get(const std::string object_id);
        std::vector<SBOLClass*> copy();
		void create(std::string prefix = SBOL_URI "/OwnedObject",
			std::string display_id = "example",
			std::string name = "",
			std::string description = "",
			std::string version = "1.0.0");
		SBOLClass& operator[] (const int nIndex);
		SBOLClass& operator[] (const std::string uri);
		//SBOLClass& __getitem__(const std::string uri);
#ifdef SWIG
	protected:
#endif
        class iterator : public std::vector<SBOLObject*>::iterator 
		{
        public:
            
            iterator(typename std::vector<SBOLObject*>::iterator i_object = std::vector<SBOLObject*>::iterator()) : std::vector<SBOLObject*>::iterator(i_object) 
			{
            }

            SBOLClass& operator*()
			{
                return (SBOLClass&) *std::vector<SBOLObject*>::iterator::operator *();
            }
        };
        
        iterator begin() 
		{
            std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
            return iterator(object_store->begin());
        };
        
        iterator end() 
		{
            std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
            return iterator(object_store->end());
        };

		std::vector<SBOLObject*>::iterator python_iter;
	};

	template <class SBOLClass>
	void OwnedObject<SBOLClass>::create(std::string prefix, std::string display_id, std::string name, std::string description, std::string version)
	{
		// Construct an SBOLObject with emplacement
		void* mem = malloc(sizeof(SBOLClass));
		SBOLClass* owned_obj = new (mem)SBOLClass;

		owned_obj->identity.set(prefix + "/" + display_id + "/" + version);
		owned_obj->displayId.set(display_id);
		owned_obj->name.set(name);
		owned_obj->description.set(description);
		owned_obj->version.set(version);
		add(*owned_obj);
	};

	template <class SBOLClass >
    OwnedObject< SBOLClass >::OwnedObject(sbol_type type_uri, SBOLObject *property_owner, std::string dummy) :
		Property<SBOLClass>(type_uri, property_owner)
		{
			// Register Property in owner Object
			if (this->sbol_owner != NULL)
			{
				std::vector<sbol::SBOLObject*> object_store;
				this->sbol_owner->owned_objects.insert({ type_uri, object_store });
			}
		};

	template <class SBOLClass>
	OwnedObject< SBOLClass >::OwnedObject(sbol_type type_uri, void *property_owner, SBOLObject& first_object)
	{
	};

    // Sets the first object in the container
    template < class SBOLClass>
    void OwnedObject<SBOLClass>::set(SBOLClass& sbol_obj)
    {
        // This could cause a memory leak if the overwritten object is not freed!
        this->sbol_owner->owned_objects[this->type][0] = ((SBOLObject *)&sbol_obj);
    };
    
    // Pushes an object into the container
	template < class SBOLClass>
	void OwnedObject<SBOLClass>::add(SBOLClass& sbol_obj)
	{
		this->sbol_owner->owned_objects[this->type].push_back((SBOLObject *)&sbol_obj);
	};

	template <class SBOLClass>
	SBOLClass& OwnedObject<SBOLClass>::operator[] (const int nIndex)
	{
		std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
		return (SBOLClass&)*object_store->at(nIndex);
	};

    
    // Moved to object.h
//	template <class SBOLClass>
//	SBOLClass& OwnedObject<SBOLClass>::operator[] (const std::string uri)
//	{
//		std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
//		for (auto i_obj = object_store->begin(); i_obj != object_store->end(); i_obj++)
//		{
//			SBOLObject* obj = *i_obj;
//			if (uri.compare(obj->identity.get()) == 0)
//			{
//				return (SBOLClass&)*obj;
//			}
//		}
//		SBOLError(NOT_FOUND_ERROR, "Object not found");
//	};

	
	//class ReferencedObject : public URIProperty
	//{
	//	public:
	//		ReferencedObject(sbol_type type_uri, void *property_owner, std::string initial_value) : URIProperty(type_uri, property_owner, initial_value)
	//		{
	//		}

	//		void reference(std::string uri) { add(uri); };
	//};


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
        this->set(uri_prefix + "/" + display_id + "/1.0.0");
    };
    
    // For compliant URIs
    template < class SBOLClass>
    void ReferencedObject<SBOLClass>::setReference(const std::string uri_prefix, const std::string display_id, const std::string version)
    {
        this->set(uri_prefix + "/" + display_id + "/" + version);
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
        this->addReference(uri_prefix + "/" + display_id + "/1.0.0");
    };
    
    // For compliant URI's
    template < class SBOLClass >
    void ReferencedObject<SBOLClass>::addReference(const std::string uri_prefix, const std::string display_id, const std::string version)
    {
        this->addReference(uri_prefix + "/" + display_id + "/" + version);
    };
    
	template <class PropertyType>
	class List : public PropertyType 
	{

	public:
        List(sbol_type type_uri, SBOLObject *property_owner, std::string initial_value = "");
		//std::string get(int index);
		//SBOLClass& get(std::string object_id);
		void remove(int index);

		//template <class SBOLClass>
		//SBOLClass& get(std::string object_id);

		//std::vector<PropertyType> copy();
		//void remove(std::string uri);
	};

    template <class PropertyType>
    List<PropertyType>::List(sbol_type type_uri, SBOLObject *property_owner, std::string initial_value) :
        PropertyType(type_uri, property_owner, initial_value)
    {
    };
    


	//template <class PropertyType>
	//template <class SBOLClass>
	//SBOLClass& List<PropertyType>::get(std::string object_id)
	//{
	//	vector<SBOLObject*> object_store = sbol_owner->owned_objects[type];
	//	cout << object_store.size() << endl;
	//	return (SBOLClass &)object_store.front();

	//};

	//template <class PropertyType>
	//std::string List<PropertyType>::get(int index)
	//{
	//	if (sbol_owner)
	//	{
	//		if (sbol_owner->properties.find(type) == sbol_owner->properties.end())
	//		{
	//			// TODO: trigger exception
	//			// not found
	//			return "";
	//		}
	//		else
	//		{
	//			// found
	//			std::string current_value = sbol_owner->properties[type].at(index);
	//			current_value = current_value.substr(1, current_value.length() - 2);
	//			return current_value;
	//		}
	//	}
	//	else
	//	{
	//		return "";
	//	}
	//};


//	template < class PropertyType >
//	std::vector<PropertyType> List<PropertyType>::copy()
//	{
//		std::vector<PropertyType> vector_copy;
//		for (auto o = this->sbol_owner->owned_objects[this->type].begin(); o != this->sbol_owner->owned_objects[this->type].end(); o++)
//		{
//			vector_copy.push_back(**o);
//		}
//		return vector_copy;
//	};



	template <class PropertyType>
	void List<PropertyType>::remove(int index)
	{
		if (this->sbol_owner)
		{
			this->sbol_owner->properties[this->type].erase( this->sbol_owner->properties[this->type].begin() + index - 1);
		}
	};
}

#endif