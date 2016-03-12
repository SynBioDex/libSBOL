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
        template < class SBOLSubClass > void add(SBOLSubClass& sbol_obj);
        template < class SBOLSubClass > SBOLSubClass& get();
        SBOLClass& get(const std::string object_id);
        std::vector<SBOLClass*> copy();
        void create(std::string uri);
        void create(std::string uri_prefix, std::string display_id, std::string version);
		SBOLClass& operator[] (const int nIndex);
		SBOLClass& operator[] (const std::string uri);
		//SBOLClass& __getitem__(const std::string uri);

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
        
        int size()
        {
            std::size_t size = this->sbol_owner->owned_objects[this->type].size();
            return (int)size;
        }

		std::vector<SBOLObject*>::iterator python_iter;
	};

    template <class SBOLClass>
    void OwnedObject<SBOLClass>::create(std::string uri)
    {
        // Construct an SBOLObject with emplacement
        void* mem = malloc(sizeof(SBOLClass));
        SBOLClass* owned_obj = new (mem)SBOLClass;
        
        owned_obj->identity.set(uri);
        add(*owned_obj);
    };
    
    template <class SBOLClass>
    void OwnedObject<SBOLClass>::create(std::string uri_prefix, std::string display_id, std::string version)
    {
        // Construct an SBOLObject with emplacement
        void* mem = malloc(sizeof(SBOLClass));
        SBOLClass* owned_obj = new (mem)SBOLClass;
        
        std::string sbol_class_name = owned_obj->getClassName(owned_obj->type);
        std::string compliant_uri = getCompliantURI(uri_prefix, display_id, sbol_class_name, "1.0.0");
        
        owned_obj->identity.set(compliant_uri);
        owned_obj->displayId.set(display_id);
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
    
    template <class SBOLClass>
    template <class SBOLSubClass>
    void OwnedObject< SBOLClass >::add(SBOLSubClass& sbol_obj)
    {
        // This should use dynamic_cast instead of implicit casting.  Failure of dynamic_cast should validate if sbol_obj is a valid subclass
        this->sbol_owner->owned_objects[this->type].push_back((SBOLObject *)&sbol_obj);
    };

    template <class SBOLClass>
    template <class SBOLSubClass>
    SBOLSubClass& OwnedObject< SBOLClass >::get()
    {
        // This should use dynamic_cast instead of implicit casting
        SBOLObject* obj = this->sbol_owner->owned_objects[this->type][0];
        return (SBOLSubClass&)*obj;
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