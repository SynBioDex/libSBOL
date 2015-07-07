#ifndef PROPERTY_INCLUDED
#define PROPERTY_INCLUDED

// The URIs defined here determine the appearance of serialized RDF/XML nodes.  Change these URIs to change the appearance of an SBOL class or property name
#define SBOL_URI "http://sbolstandard.org/v2#"
#define SBOL_IDENTIFIED SBOL_URI "Identified"
#define SBOL_DOCUMENTED SBOL_URI "Documented"
#define SBOL_TOP_LEVEL SBOL_URI "TopLevel"
#define SBOL_GENERIC_TOP_LEVEL SBOL_URI "GenericTopLevel"
#define SBOL_COMPONENT_DEFINITION SBOL_URI "ComponentDefinition"
#define SBOL_DOCUMENT SBOL_URI "Document"

#define SBOL_IDENTITY SBOL_URI "identity"
#define SBOL_PERSISTENT_IDENTITY SBOL_URI "persistentIdentity"
#define SBOL_VERSION SBOL_URI "version"
#define SBOL_DISPLAY_ID SBOL_URI "displayId"
#define SBOL_NAME SBOL_URI "name"
#define SBOL_DESCRIPTION SBOL_URI "description"
#define UNDEFINED SBOL_URI "undefined"

#include "sbolerror.h"

#include <string>
#include <vector>
#include <iostream>

namespace sbol 
{	
	typedef std::string sbol_type;
	/* All objects have a pointer back to their Document.  This requires forward declaration of SBOL Document class here */
	class Document;

	class SBOLObject
	{
	private:
		Document *doc = NULL;
	//protected:
	//	sbol_type type;

	public:
		SBOLObject(sbol_type type = UNDEFINED) :
			type(type)
			{
			}
		sbol_type type;

		virtual sbol_type getTypeURI();
	};

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

		//virtual void graph();

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

	//class VersionProperty : public TextProperty
	//// based on Maven version strings
	//{
	//	void update();
	//public:
	//	IntProperty major;
	//	IntProperty minor;
	//	IntProperty incremental;
	//	TextProperty qualifier;

	//	VersionProperty() :
	//		TextProperty(SBOL_VERSION, NULL, "1.0.0"),
	//		major(IntProperty(1)),
	//		minor(IntProperty(0)),
	//		incremental(IntProperty(0)),
	//		qualifier(TextProperty(UNDEFINED, NULL, ""))
	//	{
	//	}
	//	VersionProperty(std::string version_arg);
	//	void set(std::string maven_version);

	//};

}

#endif 
