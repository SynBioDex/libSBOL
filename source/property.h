#include <string>

namespace sbol {
	class TextProperty {
		std::string text;
	public:
		//Identified(std::string uri_prefix, std::string id);
		TextProperty() :
			text("Hello sbol")
			{
			}
		std::string get();
		void set(std::string arg);

	};
}