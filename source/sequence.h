#include "toplevel.h"

#include <string>

namespace sbol
{
	class Sequence : public TopLevel
	{
	public:
		TextProperty elements;
		URIProperty encoding;

		Sequence(std::string uri_prefix = SBOL_URI "/Sequence", std::string id = "example", std::string elements = "", uri encoding = "") : Sequence(SBOL_SEQUENCE, uri_prefix, id, start)
		{
		}
		~Sequence() {};
	protected:
		// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 

		Sequence(uri type, std::string uri_prefix, std::string id, int start) :
			Identified(type, uri_prefix, id)
		{
		}

	};
}