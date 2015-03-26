#ifndef PROPERTY_INCLUDED
#define PROPERTY_INCLUDED

#include <string>
#include <vector>

namespace sbol 
{	
	enum sbol_type
	{
		SBOL_IDENTIFIED,  // Listed in order of abstract -> concrete classes and depedence
		SBOL_DOCUMENTED,
		SBOL_TOP_LEVEL,
		SBOL_GENERIC_TOP_LEVEL,
		SBOL_COMPONENT_DEFINITION,
		SBOL_DOCUMENT
	};

	class TextProperty 
	{
		std::string value;
	public:
		//Identified(std::string uri_prefix, std::string id);
		TextProperty(std::string arg = "") :
			value(arg)
			{
			}
		std::string get();
		void set(std::string arg);
		std::vector<std::string> split(const char c);
	};

	class IntProperty 
	{
		int value;
	public:
		//Identified(std::string uri_prefix, std::string id);
		IntProperty(int arg = 0) :
			value(arg)
		{
		}
		int get();
		void set(int arg);
	};

}

#endif 
