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

#define SBOL_IDENTITY SBOL_URI "#identity"
#define SBOL_PERSISTENT_IDENTITY SBOL_URI "#persistentIdentity"
#define SBOL_VERSION SBOL_URI "#version"
#define SBOL_DISPLAY_ID SBOL_URI "#displayId"
#define SBOL_NAME SBOL_URI "#name"
#define SBOL_DESCRIPTION SBOL_URI "#description"
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

	template <typename LiteralType>
	class SBOLProperty
	{
	protected:
		sbol_type type;
		SBOLObject *sbol_owner;  // pointer to the owning SBOLObject to which this Property belongs
		LiteralType value;

	public:
		SBOLProperty() :
			type(UNDEFINED),
			sbol_owner(NULL),
			value()
		{
		}

		SBOLProperty(LiteralType initial_value, sbol_type type_uri = UNDEFINED, void *property_owner = NULL) :
			type(type_uri),
			sbol_owner((SBOLObject *)property_owner),
			value(initial_value)
		{
		}
		virtual sbol_type getTypeURI();
		virtual SBOLObject& getOwner();
		LiteralType get();
		void set(LiteralType new_value);
		virtual void write();
	};

	template <typename LiteralType>
	sbol_type SBOLProperty<LiteralType>::getTypeURI()
	{
		return type;
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
	SBOLObject& SBOLProperty<LiteralType>::getOwner()
	{

		return *sbol_owner;
	}

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
	class ListProperty 
	{
	protected:
		std::vector<LiteralType> value;
	public:
		ListProperty(LiteralType initial_value) :
			value(1, initial_value)
		{
		}
		void add(LiteralType new_value);
		void write();
	};

	template < typename LiteralType >
	void ListProperty<LiteralType>::add(LiteralType new_value)
	{
		value.push_back(new_value);
	};

	template < typename LiteralType >
	void ListProperty<LiteralType>::write()
	{
		for (std::vector<LiteralType>::iterator value_i = value.begin(); value_i != value.end(); value_i++) 
		{
			cout << *value_i << endl;
		}
	};

	//template <typename LiteralType>
	//class ListProperty
	//{
	//protected:
	//	sbol_type type;
	//	SBOLObject *sbol_owner;  // pointer to the owning SBOLObject to which this Property belongs
	//	std::vector<LiteralType> value;

	//public:
	//	ListProperty() :
	//		type(UNDEFINED),
	//		sbol_owner(NULL)
	//		//value()
	//	{
	//	}

	//	ListProperty(LiteralType initial_value, sbol_type type_uri = UNDEFINED, void *property_owner = NULL) :
	//		type(type_uri),
	//		sbol_owner((SBOLObject *)property_owner)
	//		//value(1, initial_value)
	//	{
	//	}

	//	void add(LiteralType sbol_obj);
	//	void write();
	//};

	//template < typename LiteralType >
	//void ListProperty<LiteralType>::add(LiteralType new_value)
	//{
	//	value.push_back(new_value);
	//};

	//template < typename LiteralType >
	//void ListProperty<LiteralType>::write()
	//{
	//	for (value_i = value.begin(); value_i != value.end(); value_i++) {
	//		cout << value_i << endl;
	//};

	/* Corresponding to black diamonds in UML diagrams.  Creates a composite out of two or more classes */
	template <class SBOLClass>
	class ComposedOf
	{
		public:
			std::map<std::string, SBOLClass*> constituent_objects;
			void add(SBOLClass& sbol_obj);
			SBOLClass& get(std::string uri);
	};

	template < class SBOLClass >
	void ComposedOf<SBOLClass>::add(SBOLClass& sbol_obj)
	{
		constitutent_objects[sbol_obj.identity.get()] = &sbol_obj;
	};

	template < class SBOLClass >
	SBOLClass& ComposedOf<SBOLClass>::get(std::string uri)
	{
		return constitutent_objects[uri];
	};

	/* Placeholder for RefersTo class*/
	//template <typename LiteralType>
	//class RefersTo
	//{
	//}

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
