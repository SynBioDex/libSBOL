#include "identified.h"

#include <string>


namespace sbol {
	class TextProperty;

	class Documented : public Identified {

	public:
		Documented(std::string uri_prefix, std::string display_id) :
			Identified(uri_prefix, display_id),
			displayID(TextProperty(display_id)),
			name(TextProperty()),
			description(TextProperty())
			{
			}
		TextProperty displayID;
		TextProperty name;
		TextProperty description;
	};
}