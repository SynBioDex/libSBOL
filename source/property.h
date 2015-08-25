#ifndef PROPERTY_INCLUDED
#define PROPERTY_INCLUDED

// The URIs defined here determine the appearance of serialized RDF/XML nodes.  Change these URIs to change the appearance of an SBOL class or property name
#define SBOL_URI "http://sbolstandard.org/v2"
#define SBOL_IDENTIFIED SBOL_URI "#Identified"
#define SBOL_DOCUMENTED SBOL_URI "#Documented"
#define SBOL_TOP_LEVEL SBOL_URI "#TopLevel"
#define SBOL_GENERIC_TOP_LEVEL SBOL_URI "#GenericTopLevel"
#define SBOL_COMPONENT_DEFINITION SBOL_URI "#ComponentDefinition"
#define SBOL_DOCUMENT SBOL_URI "#Document"

#define SO_UNDEFINED "#SO_0000001"

#define SBOL_IDENTITY SBOL_URI "#identity"
#define SBOL_PERSISTENT_IDENTITY SBOL_URI "#persistentIdentity"
#define SBOL_VERSION SBOL_URI "#version"
#define SBOL_DISPLAY_ID SBOL_URI "#displayId"
#define SBOL_NAME SBOL_URI "#name"
#define SBOL_DESCRIPTION SBOL_URI "#description"
#define SBOL_TYPE "#type"
#define UNDEFINED SBOL_URI "#Undefined"

#include "sbolerror.h"

#include <string>
#include <vector>
#include <iostream>
#include <map>


namespace sbol
{
	/* Contains URI strings used for constructing RDF triples */
	typedef std::string sbol_type;

	/* All SBOLProperties have a pointer back to the owning object (whose URI is the subject of an RDF triple).  This requires forward declaration of the SBOLObject class */
	class SBOLObject;

	class PropertyBase
	{
	protected:
		sbol_type type;
		SBOLObject *sbol_owner;  // pointer to the owning SBOLObject to which this Property belongs

	public:
		PropertyBase() :
			type(UNDEFINED),
			sbol_owner(NULL)
		{
		}

		PropertyBase(sbol_type type_uri, void *property_owner) :
			type(type_uri),
			sbol_owner((SBOLObject *)property_owner)
		{
		}
		virtual sbol_type getTypeURI();
		virtual SBOLObject& getOwner();
		void write();
	};





	template <typename LiteralType>
	class SBOLProperty : public PropertyBase
	{
	protected:
		LiteralType value;

	public:
		SBOLProperty(sbol_type type_uri = UNDEFINED, void *property_owner = NULL) :
			PropertyBase(type_uri, property_owner),
			value()
		{
		}

		SBOLProperty(LiteralType initial_value, sbol_type type_uri = UNDEFINED, void *property_owner = NULL) :
			PropertyBase(type_uri, property_owner),
			value(initial_value)
		{
		}
		LiteralType get();
		void set(LiteralType new_value);
		void write();
	};


	template <typename LiteralType>
	LiteralType SBOLProperty<LiteralType>::get()
	{
		return value;
	};

	template <typename LiteralType>
	void SBOLProperty<LiteralType>::set(LiteralType new_value)
	{
		value = new_value;
	};

	template <typename LiteralType>
	void SBOLProperty<LiteralType>::write()
	{
		std::string subject = (*sbol_owner).identity.get();
		sbol_type predicate = type;
		LiteralType object = value;

		cout << "Subject:  " << subject << endl;
		cout << "Predicate: " << predicate << endl;
		cout << "Object: " << object << endl;

		//triple = raptor_new_statement(world);
		//triple->subject = parent_serialization_object;
		//triple->predicate = raptor_new_term_from_uri(world, raptor_new_uri(world, (const unsigned char *)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type"));
		//triple->object = raptor_new_term_from_uri_string(world, (const unsigned char *)SBOL_URI "Sequence");
	}


	//class TextProperty : public SBOLProperty
	//{
	//	std::string value;
	//public:
	//	//Identified(std::string uri_prefix, std::string id);
	//	TextProperty(sbol_type type_uri = UNDEFINED, SBOLObject *owner_obj = NULL, std::string val = "") :
	//		SBOLProperty(type_uri, owner_obj),
	//		value(val)
	//		{
	//		}
	//	std::string get();
	//	void set(std::string arg);
	//	std::vector<std::string> split(const char c);
	//	sbol_type getTypeURI();
	//	SBOLObject& getOwner();
	//};

	//class IntProperty 
	//{
	//	sbol_type type;
	//	int value;
	//public:
	//	//Identified(std::string uri_prefix, std::string id);
	//	IntProperty(int arg = 0) :
	//		type(),
	//		value(arg)
	//		{
	//		}
	//	int get();
	//	void set(int arg);
	//};

	class VersionProperty : public SBOLProperty < std::string >
		// based on Maven version strings
	{
		void update();
	public:
		SBOLProperty<int> major;
		SBOLProperty<int> minor;
		SBOLProperty<int> incremental;
		SBOLProperty<std::string> qualifier;

		VersionProperty() :
			SBOLProperty<std::string>("1.0.0", SBOL_VERSION, NULL),
			major(SBOLProperty<int>(1)),
			minor(SBOLProperty<int>(0)),
			incremental(SBOLProperty<int>(0)),
			qualifier(SBOLProperty<std::string>("", UNDEFINED, NULL))
		{
		}
		VersionProperty(std::string version_arg);
		void set(std::string maven_version);
	};

	template <typename LiteralType>
	class ListProperty : public SBOLProperty<LiteralType> 
	{
	protected:
		std::vector<LiteralType> value;
		int index;
	public:
		ListProperty(LiteralType initial_value, sbol_type type_uri = UNDEFINED, void *property_owner = NULL) :
			SBOLProperty(initial_value, type_uri, property_owner),
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

	/* Corresponding to black diamonds in UML diagrams.  Creates a composite out of two or more classes */
	template <class SBOLClass>
	class ContainedObjects : public SBOLProperty<SBOLClass>
	{
	protected:
		std::map<std::string, SBOLClass*> constituent_objects;
	public:
		void add(SBOLClass& sbol_obj);
		SBOLClass& get(std::string uri);
		void write();
	};

	template < class SBOLClass >
	void ContainedObjects<SBOLClass>::add(SBOLClass& sbol_obj)
	{
		constituent_objects[sbol_obj.identity.get()] = &sbol_obj;
	};

	template < class SBOLClass >
	SBOLClass& ContainedObjects<SBOLClass>::get(std::string uri)
	{
		return *constituent_objects[uri];
	};

	template < class SBOLClass >
	void ContainedObjects<SBOLClass>::write()
	{
		cout << "Testing object container" << endl;
		for (std::map<std::string, SBOLClass*>::iterator obj_i = constituent_objects.begin(); obj_i != constituent_objects.end(); obj_i++) 
		{
			cout << obj_i->first << endl;
		}
	};

	/* A list of URIs corresponding to the referenced objects.  Corresponding to white diamonds in UML diagrams */
	//class ReferencedObjects : public ContainedObjects < std::string >
	//{

	//};


	/* All SBOLObjects have a pointer back to their Document.  This requires forward declaration of SBOL Document class here */
	class Document;

	class SBOLObject
	{
	private:
		Document *doc = NULL;
		//protected:
		//	sbol_type type;

	public:
		SBOLObject(sbol_type type = UNDEFINED, std::string uri_prefix = SBOL_URI "/Undefined", std::string id = "example") :
			type(type),
			identity(SBOLProperty<std::string>(uri_prefix + "/" + id, SBOL_IDENTITY, this))
		{
		}
		sbol_type type;
		SBOLProperty<std::string> identity;

		virtual sbol_type getTypeURI();
	};

	
}

#endif 
