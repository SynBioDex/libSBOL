#ifndef PROPERTY_INCLUDED
#define PROPERTY_INCLUDED

// The URIs defined here determine the appearance of serialized RDF/XML nodes.  Change these URIs to change the appearance of an SBOL class or property name
#define SBOL_URI "http://sbolstandard.org/v2"
#define SBOL_IDENTIFIED "Identified"
#define SBOL_DOCUMENTED "Documented"
#define SBOL_TOP_LEVEL "TopLevel"
#define SBOL_GENERIC_TOP_LEVEL "GenericTopLevel"
#define SBOL_COMPONENT_DEFINITION "ComponentDefinition"
#define SBOL_SEQUENCE_ANNOTATION "SequenceAnnotation"
#define SBOL_DOCUMENT "Document"

#define SO_UNDEFINED "SO_0000001"

#define SBOL_IDENTITY "identity"
#define SBOL_PERSISTENT_IDENTITY "persistentIdentity"
#define SBOL_VERSION "version"
#define SBOL_DISPLAY_ID  "displayId"
#define SBOL_NAME "name"
#define SBOL_DESCRIPTION "description"
#define SBOL_TYPE "type"
#define UNDEFINED "Undefined"

#include "sbolerror.h"

#include <raptor2.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>

namespace sbol
{
	/* Contains URI strings used for constructing RDF triples */
	typedef std::string sbol_type;


	/* All SBOLProperties have a pointer back to the owning object (whose URI is the subject of an RDF triple).  This requires forward declaration of the SBOLObject class */
	class SBOLObject;

	//class PropertyBase
	//{
	//
	//	friend class SBOLObject;

	//protected:
	//	sbol_type type;
	//	SBOLObject *sbol_owner;  // pointer to the owning SBOLObject to which this Property belongs

	//public:
	//	PropertyBase() :
	//		type(UNDEFINED),
	//		sbol_owner(NULL)
	//	{
	//	}

	//	//PropertyBase(sbol_type type_uri, void *property_owner) :
	//	//	type(type_uri),
	//	//	sbol_owner((SBOLObject *)property_owner)
	//	//{
	//	//}
	//	PropertyBase(sbol_type type_uri, void *property_owner, void *self);

	//};


	template <typename LiteralType>
	class Property
	{
	protected:
		sbol_type type;
		SBOLObject *sbol_owner;  // pointer to the owning SBOLObject to which this Property belongs

	public:
		Property(std::string initial_value, sbol_type type_uri = UNDEFINED, void *property_owner = NULL);
		Property(int initial_value, sbol_type type_uri = UNDEFINED, void *property_owner = NULL);
		Property(sbol_type type_uri = UNDEFINED, void *property_owner = NULL) :
			type(type_uri),
			sbol_owner((SBOLObject *)property_owner)
		{
		}
		virtual sbol_type getTypeURI();
		virtual SBOLObject& getOwner();
		std::string get();
		virtual void set(std::string new_value);
		virtual void set(int new_value);
		virtual void write();
	};

	template <typename LiteralType>
	Property<LiteralType>::Property(std::string initial_value, sbol_type type_uri, void *property_owner) : Property(type_uri, property_owner)
	{
		// Register Property in owner Object
		if (sbol_owner != NULL)
		{
			std::vector<std::string> property_store;
			property_store.push_back(initial_value);
			sbol_owner->properties.insert({ type_uri, property_store });
		}
	}

	template <typename LiteralType>
	Property<LiteralType>::Property(int initial_value, sbol_type type_uri, void *property_owner) : Property(type_uri, property_owner)
	{
		// Register Property in owner Object
		if (sbol_owner != NULL)
		{
			std::vector<std::string> property_store;
			property_store.push_back("");
			sbol_owner->properties.insert({ type_uri, property_store });
		}
	}

	template <typename LiteralType>
	sbol_type Property<LiteralType>::getTypeURI()
	{
		return type;
	}

	template <typename LiteralType>
	SBOLObject& Property<LiteralType>::getOwner()
	{
		return *sbol_owner;
	}
	
	template <typename LiteralType>
	std::string Property<LiteralType>::get()
	{
		if (sbol_owner)
		{
			if (sbol_owner->properties.find(type) == sbol_owner->properties.end()) 
			{
				// not found
				return "";
			}
			else 
			{
				// found
				return sbol_owner->properties[type].front();
			}
		}	else
		{
			return "";
		}
	};

	template <typename LiteralType>
	void Property<LiteralType>::set(std::string new_value)
	{
		if (sbol_owner)
		{
			sbol_owner->properties[type].push_back( new_value );
		}
	};

	template <typename LiteralType>
	void Property<LiteralType>::set(int new_value)
	{
		if (new_value)
		{
			sbol_owner->properties[type].push_back( "98" );
		}
	};

	template <typename LiteralType>
	void Property<LiteralType>::write()
	{
		std::string subject = (*sbol_owner).identity.get();
		sbol_type predicate = type;
		std::string object = sbol_owner->properties[type].front();

		cout << "Subject:  " << subject << endl;
		cout << "Predicate: " << predicate << endl;
		cout << "Object: "  << endl;
	};

	/* Corresponding to black diamonds in UML diagrams.  Creates a composite out of two or more classes */
	template <class SBOLClass>
	class OwnedObjects
	{
	protected:
		sbol_type type;
		SBOLObject *sbol_owner;  // pointer to the owning SBOLObject to which this Property belongs
		
	public:
		OwnedObjects<SBOLClass>() :
			type(UNDEFINED),
			sbol_owner(NULL)
		{
		}
		OwnedObjects(sbol_type type_uri, void *property_owner);
		OwnedObjects(SBOLObject& first_object, sbol_type type_uri, void *property_owner);
		std::vector<SBOLClass> get();
		void add(SBOLClass& sbol_obj);
		void remove(std::string uri);
	};

	template <class SBOLClass >
	OwnedObjects< SBOLClass >::OwnedObjects(sbol_type type_uri, void *property_owner)
	{
		type = type_uri;
		sbol_owner = ((SBOLObject *)property_owner);

		// Register Property in owner Object
		if (sbol_owner != NULL)
		{
			std::vector<sbol::SBOLObject*> object_store;
			sbol_owner->owned_objects.insert({ type_uri, object_store });
		}
	};

	template <class SBOLClass>
	OwnedObjects< SBOLClass >::OwnedObjects(SBOLObject& first_object, sbol_type type_uri, void *property_owner)
	{
	};

	template < class SBOLClass >
	void OwnedObjects<SBOLClass>::add(SBOLClass& sbol_obj)
	{
		sbol_owner->owned_objects[type].push_back((SBOLObject *)&sbol_obj);
	};

	template < class SBOLClass >
	std::vector<SBOLClass> OwnedObjects<SBOLClass>::get()
	{
		std::vector<SBOLClass> vector_copy;
		for (auto o = sbol_owner->owned_objects[type].begin(); o != sbol_owner->owned_objects[type].end(); o++)
		{
			vector_copy.push_back(**o);
		}
		//vector_copy = sbol_owner->owned_objects[type];
		return vector_copy;
	};



	template <typename LiteralType>
	class ListProperty : public Property<LiteralType> 
	{
	protected:
		std::vector<LiteralType> value;
		int index;
	public:
		ListProperty(LiteralType initial_value, sbol_type type_uri = UNDEFINED, void *property_owner = NULL) :
			Property(initial_value, type_uri, property_owner),
			value(1, initial_value),
			index(0)
		{
		}
		void add(LiteralType new_value);
		LiteralType get();
		bool end();
		void write();
	};

	template < typename LiteralType >
	void ListProperty<LiteralType>::add(LiteralType new_value)
	{
		value.push_back(new_value);
	};

	template < typename LiteralType >
	LiteralType ListProperty<LiteralType>::get()
	{
		// TODO Throw error if list has no elements
		LiteralType current_val = value[index];
		if (end())
			index = 0;
		else 
			index++;
		return current_val;
	};

	template < typename LiteralType >
	bool ListProperty<LiteralType>::end()
	{
		return (index == value.size());
	};

	template < typename LiteralType >
	void ListProperty<LiteralType>::write()
	{
		std::string subject;
		sbol_type predicate;
		LiteralType object;

		while (!end())
		{
			subject = (*sbol_owner).identity.get();
			predicate = type;
			object = get();

			cout << "Subject:  " << subject << endl;
			cout << "Predicate: " << predicate << endl;
			cout << "Object: " << object << endl;
		}
	};

	///* Corresponding to black diamonds in UML diagrams.  Creates a composite out of two or more classes */
	//template <class SBOLClass>
	//class ContainedObjects : public Property<SBOLClass>
	//{
	//protected:
	//	std::map<std::string, SBOLClass*> constituent_objects;
	//public:
	//	void add(SBOLClass& sbol_obj);
	//	SBOLClass& get(std::string uri);
	//	void write();
	//};

	//template < class SBOLClass >
	//void ContainedObjects<SBOLClass>::add(SBOLClass& sbol_obj)
	//{
	//	constituent_objects[sbol_obj.identity.get()] = &sbol_obj;
	//};

	//template < class SBOLClass >
	//SBOLClass& ContainedObjects<SBOLClass>::get(std::string uri)
	//{
	//	return *constituent_objects[uri];
	//};

	//template < class SBOLClass >
	//void ContainedObjects<SBOLClass>::write()
	//{
	//	cout << "Testing object container" << endl;
	//	for (std::map<std::string, SBOLClass*>::iterator obj_i = constituent_objects.begin(); obj_i != constituent_objects.end(); obj_i++) 
	//	{
	//		cout << obj_i->first << endl;
	//	}
	//};

	/* A list of URIs corresponding to the referenced objects.  Corresponding to white diamonds in UML diagrams */
	//class ReferencedObjects : public ContainedObjects < std::string >
	//{

	//};

	/* All SBOLObjects have a pointer back to their Document.  This requires forward declaration of SBOL Document class here */
	class Document;

	//typedef std::map<sbol_type, PropertyBase> PropertyStore;

	//extern PropertyStore* global_property_buffer;
	

	class SBOLObject
	{
	friend class Document;

	private:


		Document *doc = NULL;
	protected:
		//protected:
		//	sbol_type type;

	public:
		//std::unordered_map<sbol::sbol_type, sbol::PropertyBase> properties;
		std::unordered_map<sbol::sbol_type, std::vector< std::string > > properties;
		std::unordered_map<sbol::sbol_type, std::vector< std::string > > list_properties;
		std::map<sbol::sbol_type, std::vector< sbol::SBOLObject* > > owned_objects;

		SBOLObject(sbol_type type = UNDEFINED, std::string uri_prefix = SBOL_URI "/Undefined", std::string id = "example") :
			type(type),
			identity(Property<std::string>(uri_prefix + "/" + id, SBOL_IDENTITY, this))
		{
		}
		sbol_type type;
		Property<std::string> identity;
	
		virtual sbol_type getTypeURI();
		void serialize(raptor_serializer* sbol_serializer);
	};

		
}

#endif 
