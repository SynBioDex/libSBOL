#ifndef PROPERTY_INCLUDED
#define PROPERTY_INCLUDED

#define SBOL_IDENTIFIED "sbol::Identified"
#define SBOL_DOCUMENTED "sbol::Documented"
#define SBOL_TOP_LEVEL "sbol::TopLevel"
#define SBOL_GENERIC_TOP_LEVEL "sbol::GenericTopLevel"
#define SBOL_COMPONENT_DEFINITION "sbol::ComponentDefinition"
#define SBOL_DOCUMENT "sbol::Document"

#define SBOL_IDENTITY "sbol::identity"
#define SBOL_PERSISTENT_IDENTITY "sbol::persistentIdentity"
#define SBOL_VERSION "sbol::version"
#define UNDEFINED "undefined"

#include "sbolerror.h"

#include <string>
#include <vector>
#include <iostream>

namespace sbol 
{	
	typedef std::string sbol_type;

	class SBOLObject
	{
	private:
		sbol_type type = UNDEFINED;
	public:
		SBOLObject()
		{
		}
		virtual sbol_type getTypeURI();
	};

	class SBOLProperty
	{
	protected:
		sbol_type type;
		SBOLObject *sbol_owner;
	public:
		SBOLProperty(sbol_type type_uri = UNDEFINED, void *property_owner = NULL) :
			type(type_uri),
			sbol_owner((SBOLObject *)property_owner)
		{
		}
		virtual sbol_type getTypeURI();
		virtual SBOLObject& getOwner();
	};

	class TextProperty : public SBOLProperty
	{
		std::string value;
	public:
		//Identified(std::string uri_prefix, std::string id);
		TextProperty(sbol_type type_uri = UNDEFINED, SBOLObject *owner_obj = NULL, std::string val = "") :
			SBOLProperty(type_uri, owner_obj),
			value(val)
			{
			}
		std::string get();
		void set(std::string arg);
		std::vector<std::string> split(const char c);
		sbol_type getTypeURI();
		SBOLObject& getOwner();
	};

	class IntProperty 
	{
		sbol_type type;
		int value;
	public:
		//Identified(std::string uri_prefix, std::string id);
		IntProperty(int arg = 0) :
			type(),
			value(arg)
			{
			}
		int get();
		void set(int arg);
	};

	class VersionProperty : public TextProperty
	// based on Maven version strings
	{
		void update();
	public:
		IntProperty major;
		IntProperty minor;
		IntProperty incremental;
		TextProperty qualifier;

		VersionProperty() :
			TextProperty(SBOL_VERSION, NULL, "1.0.0"),
			major(IntProperty(1)),
			minor(IntProperty(0)),
			incremental(IntProperty(0)),
			qualifier(TextProperty(UNDEFINED, NULL, ""))
		{
		}
		VersionProperty(std::string version_arg);
		void set(std::string maven_version);

	};

}

#endif 
