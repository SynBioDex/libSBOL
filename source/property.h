#include <string>

namespace sbol {
	class TextProperty {
		std::string text;
	public:
		//Identified(std::string uri_prefix, std::string id);
		TextProperty(std::string arg = "") :
			text(arg)
			{
			}
		std::string get();
		void set(std::string arg);

	};
}