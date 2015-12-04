#include "toplevel.h"

#include <string>

namespace sbol
{
	class Sequence : public TopLevel
	{
	public:
		TextProperty elements;
		URIProperty encoding;

		Sequence(std::string uri_prefix = SBOL_URI "/Sequence", std::string display_id = "example", std::string elements = "", std::string encoding = SBOL_ENCODING_IUPAC, std::string name = "", std::string description = "", std::string version = "1.0.0") : Sequence(SBOL_SEQUENCE, uri_prefix, display_id, elements, encoding, name, description, version)
		{
		}
		~Sequence() {};
	protected:
		// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 

		Sequence(sbol_type type_uri, std::string uri_prefix, std::string display_id, std::string elements, std::string encoding, std::string name, std::string description, std::string version) :
			TopLevel(type_uri, uri_prefix, display_id, name, description, version),
			elements(SBOL_ELEMENTS, this, elements),
			encoding(SBOL_ENCODING, this, encoding)
		{
		}
	};
}