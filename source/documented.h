#include "identified.h"

#include <string>


namespace sbol {
	class TextProperty;

	class Documented : public Identified {


	public:
		Documented(std::string displayID = "displayID goes here", std::string name = "name goes here", std::string description = "description goes here") :
			displayID(TextProperty(displayID)),
			name(TextProperty(name)),
			description(TextProperty(description))
			{
			}
		TextProperty displayID;
		TextProperty name;
		TextProperty description;
	};
}