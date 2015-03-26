#include <string>
#include <vector>

namespace sbol 
{	
	enum sbol_type
	{
		SBOL_IDENTIFIED,
		SBOL_DOCUMENTED,
		SBOL_TOP_LEVEL,
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