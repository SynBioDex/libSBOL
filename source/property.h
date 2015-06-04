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

	class TextProperty 
	{
		sbol_type type;  // The type holds the URI that names the SBOL property and determines how it will appear when serialized
		std::string value;
	public:
		//Identified(std::string uri_prefix, std::string id);
		TextProperty(sbol_type arg1 = UNDEFINED, std::string arg2 = "") :
			type(arg1),
			value(arg2)
			{
			}
		std::string get();
		void set(std::string arg);
		std::vector<std::string> split(const char c);
		void getType();
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
			TextProperty(SBOL_VERSION, "1.0.0"),
			major(IntProperty(1)),
			minor(IntProperty(0)),
			incremental(IntProperty(0)),
			qualifier(TextProperty(UNDEFINED, ""))
		{
		}
		VersionProperty(std::string version_arg);
		void set(std::string maven_version);

	};

}

#endif 
