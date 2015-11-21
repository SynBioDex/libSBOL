#ifndef PROPERTY_INCLUDED
#define PROPERTY_INCLUDED

// The URIs defined here determine the appearance of serialized RDF/XML nodes.  Change these URIs to change the appearance of an SBOL class or property name
#define SBOL_URI "http://sbols.org/v2"
#define RDF_URI "http://www.w3.org/1999/02/22-rdf-syntax-ns#" 
#define PURL_URI "http://purl.org/dc/terms/"

#define SBOL_IDENTIFIED SBOL_URI "#Identified"
#define SBOL_DOCUMENTED SBOL_URI "#Documented"
#define SBOL_TOP_LEVEL SBOL_URI "#TopLevel"
#define SBOL_GENERIC_TOP_LEVEL SBOL_URI "#GenericTopLevel"
#define SBOL_COMPONENT_DEFINITION SBOL_URI "#ComponentDefinition"
#define SBOL_SEQUENCE_ANNOTATION SBOL_URI "#SequenceAnnotation"
#define SBOL_DOCUMENT SBOL_URI "#Document"
#define UNDEFINED SBOL_URI "#Undefined"

#define SO_UNDEFINED "SO_0000001"

#define SBOL_IDENTITY SBOL_URI "#identity"
#define SBOL_PERSISTENT_IDENTITY SBOL_URI "#persistentIdentity"
#define SBOL_VERSION SBOL_URI "#version"
#define SBOL_DISPLAY_ID  SBOL_URI "#displayId"
#define SBOL_NAME PURL_URI "#title"
#define SBOL_DESCRIPTION PURL_URI "#description"
#define SBOL_TYPE SBOL_URI "#type"
#define SBOL_START SBOL_URI "#start"
#define SBOL_SEQUENCE_ANNOTATIONS SBOL_URI "#sequenceAnnotation"
#define SBOL_ROLE SBOL_URI "#role"

#include "sbolerror.h"
#include "validation.h"

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

	template <typename LiteralType>
	class Property
	{

	protected:
		sbol_type type;
		SBOLObject *sbol_owner;  // back pointer to the SBOLObject to which this Property belongs
		ValidationRules validationRules;

	public:
		Property(sbol_type type_uri, void *property_owner, std::string initial_value, ValidationRules rules = {} );
		Property(sbol_type type_uri, void *property_owner, int initial_value, ValidationRules rules = {} );

		Property(sbol_type type_uri = UNDEFINED, void *property_owner = NULL, ValidationRules rules = {} ) :
			type(type_uri),
			sbol_owner((SBOLObject *)property_owner),
			validationRules(rules)
		{
		}
		~Property();
		virtual sbol_type getTypeURI();
		virtual SBOLObject& getOwner();
		virtual std::string get();
		virtual void set(std::string new_value);
		virtual void set(int new_value);
		virtual void write();
		virtual void validate(void * arg = NULL);
	};

	class URIProperty : public Property<std::string>
	{
	public:
		URIProperty(sbol_type type_uri, void *property_owner, std::string initial_value, ValidationRules rules = {}) :
			Property(type_uri, property_owner, initial_value, rules = {})
		{
		}
		void set(std::string new_value);
	};

	class TextProperty : public Property<std::string>
	{
	public:
		TextProperty(sbol_type type_uri, void *property_owner, std::string initial_value = "", ValidationRules rules = {}) :
			Property(type_uri, property_owner, "\"" + initial_value + "\"", rules = {})
		{
		}
		void set(std::string new_value);
	};

	/* Constructor for string Property */
	template <typename LiteralType>
	Property<LiteralType>::Property(sbol_type type_uri, void *property_owner, std::string initial_value, ValidationRules rules) : Property(type_uri, property_owner, rules)
	{
		// Register Property in owner Object
		if (sbol_owner != NULL)
		{
			std::vector<std::string> property_store;
			property_store.push_back(initial_value);
			sbol_owner->properties.insert({ type_uri, property_store });
		}
	}

	/* Constructor for int Property */
	template <typename LiteralType>
	Property<LiteralType>::Property(sbol_type type_uri, void *property_owner, int initial_value, ValidationRules rules) : Property(type_uri, property_owner, rules)
	{
		// Register Property in owner Object
		if (sbol_owner != NULL)
		{
			std::vector<std::string> property_store;
			property_store.push_back(std::to_string(initial_value));
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
			//sbol_owner->properties[type].push_back( new_value );
			sbol_owner->properties[type][0] = new_value;
		}
		validate((void *)&new_value);
	};

	template <typename LiteralType>
	void Property<LiteralType>::set(int new_value)
	{
		if (new_value)
		{
			// TODO:  need to convert new_value to string
			sbol_owner->properties[type].push_back(std::to_string(new_value) );
		}
		validate((void *)&new_value);  //  Call validation rules associated with this Property
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

	template <typename LiteralType>
	void Property<LiteralType>::validate(void * arg)
	{
		for (ValidationRules::iterator i_rule = validationRules.begin(); i_rule != validationRules.end(); ++i_rule)
		{
			cout << "Iterating through validation rules" << endl;
			ValidationRule& validate_fx = *i_rule;
			validate_fx(sbol_owner, arg);
		}
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
		OwnedObjects(sbol_type type_uri, void *property_owner, SBOLObject& first_object);
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
	OwnedObjects< SBOLClass >::OwnedObjects(sbol_type type_uri, void *property_owner, SBOLObject& first_object)
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
		return vector_copy;
	};

	class ReferencedObjects : public Property<std::string>
	{
	public:
		ReferencedObjects(sbol_type type_uri, void *property_owner, std::string initial_value) : Property<std::string>::Property(type_uri, property_owner, initial_value)
		{
		}
	};

	template <typename LiteralType>
	class ListProperty : public Property<LiteralType> 
	{
	public:
		ListProperty(sbol_type type_uri, void *property_owner, LiteralType initial_value) :
			Property(type_uri, property_owner, initial_value)
		{
		}
	void add(std::string new_value);
	std::string get(int index);
	void remove(int index);
	};

	template <typename LiteralType>
	std::string ListProperty<LiteralType>::get(int index)
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
				return sbol_owner->properties[type].at(index);
			}
		}
		else
		{
			return "";
		}
	};

	template <typename LiteralType>
	void ListProperty<LiteralType>::add(std::string new_value)
	{
		if (sbol_owner)
		{
			sbol_owner->properties[type].push_back(new_value);
		}
	};


	template <typename LiteralType>
	void ListProperty<LiteralType>::remove(int index)
	{
		if (sbol_owner)
		{
			sbol_owner->properties[type].erase( sbol_owner->properties[type].begin() + index - 1);
		}
	};


	//template < typename LiteralType >
	//void ListProperty<LiteralType>::add(LiteralType new_value)
	//{
	//	value.push_back(new_value);
	//};

	//template < typename LiteralType >
	//LiteralType ListProperty<LiteralType>::get()
	//{
	//	// TODO Throw error if list has no elements
	//	LiteralType current_val = value[index];
	//	if (end())
	//		index = 0;
	//	else 
	//		index++;
	//	return current_val;
	//};

	//template < typename LiteralType >
	//bool ListProperty<LiteralType>::end()
	//{
	//	return (index == value.size());
	//};

	//template < typename LiteralType >
	//void ListProperty<LiteralType>::write()
	//{
	//	std::string subject;
	//	sbol_type predicate;
	//	LiteralType object;

	//	while (!end())
	//	{
	//		subject = (*sbol_owner).identity.get();
	//		predicate = type;
	//		object = get();

	//		cout << "Subject:  " << subject << endl;
	//		cout << "Predicate: " << predicate << endl;
	//		cout << "Object: " << object << endl;
	//	}
	//};

	

	/* All SBOLObjects have a pointer back to their Document.  This requires forward declaration of SBOL Document class here */
	class Document;

	//typedef std::map<sbol_type, PropertyBase> PropertyStore;

	//extern PropertyStore* global_property_buffer;
	

	class SBOLObject
	{
	friend class Document;
	

	protected:
		//protected:
		//	sbol_type type;

	public:
		Document *doc = NULL;

		//std::unordered_map<sbol::sbol_type, sbol::PropertyBase> properties;
		std::unordered_map<sbol::sbol_type, std::vector< std::string > > properties;
		std::unordered_map<sbol::sbol_type, std::vector< std::string > > list_properties;
		std::map<sbol::sbol_type, std::vector< sbol::SBOLObject* > > owned_objects;

		SBOLObject(sbol_type type = UNDEFINED, std::string uri_prefix = SBOL_URI, std::string id = "example") :
			type(type),
			identity(Property<std::string>(SBOL_IDENTITY, this, uri_prefix + "/" + id, { validation_rule_10202 }))
		{
		}
		~SBOLObject();
		sbol_type type;
		Property<std::string> identity;
	
		virtual sbol_type getTypeURI();
		void serialize(raptor_serializer* sbol_serializer, raptor_world *sbol_world = NULL);
	};
}

// This is a wrapper function for constructors.  This allows us to construct an SBOL object using a function pointer (direct pointers to constructors are not supported by C++)
template <class SBOLClass>
sbol::SBOLObject& create()
{
	// Construct an SBOLObject with emplacement
	void* mem = malloc(sizeof(SBOLClass));
	SBOLClass* a = new (mem) SBOLClass;
	return (SBOLObject&)*a;
};






#endif 
