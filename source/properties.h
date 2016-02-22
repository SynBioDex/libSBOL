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
		SBOLClass& get(std::string object_id);
		void create(std::string prefix = SBOL_URI "/OwnedObject",
			std::string display_id = "example",
			std::string name = "",
			std::string description = "",
			std::string version = "1.0.0");
	};

	template <class SBOLClass>
	void OwnedObject<SBOLClass>::create(std::string prefix, std::string display_id, std::string name, std::string description, std::string version)
	{
		// Construct an SBOLObject with emplacement
		void* mem = malloc(sizeof(SBOLClass));
		SBOLClass* owned_obj = new (mem)SBOLClass;

		owned_obj->identity.set(prefix + "/" + display_id);
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

	template < class SBOLClass>
	void OwnedObject<SBOLClass>::add(SBOLClass& sbol_obj)
	{
        std::cout << this->sbol_owner->owned_objects.size() << std::endl;  //Debugging code
		this->sbol_owner->owned_objects[this->type].push_back((SBOLObject *)&sbol_obj);
	};

	template <class SBOLClass>
	SBOLClass& OwnedObject<SBOLClass>::get(std::string object_id)
	{
        std::vector<SBOLObject*> *object_store = &this->sbol_owner->owned_objects[this->type];
		SBOLObject& obj = *object_store->front();
		return (SBOLClass &)*object_store->front();
	};

	class ReferencedObject : public URIProperty
	{
		public:
			ReferencedObject(sbol_type type_uri, void *property_owner, std::string initial_value) : URIProperty(type_uri, property_owner, initial_value)
			{
			}
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