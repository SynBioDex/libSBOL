#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include "toplevel.h"

#include <string>

namespace sbol
{
	class Sequence : public TopLevel
	{
	public:
		TextProperty elements;
		URIProperty encoding;

		Sequence(std::string uri = DEFAULT_NS "/Sequence/example", std::string elements = "", std::string encoding = SBOL_ENCODING_IUPAC) : Sequence(SBOL_SEQUENCE, uri, elements, encoding) {};
        
        Sequence(std::string uri_prefix, std::string display_id, std::string version, std::string elements, std::string encoding) : Sequence(SBOL_SEQUENCE, uri_prefix, display_id, version, elements, encoding) {};

        ~Sequence() {};
	protected:
		// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 

        Sequence(sbol_type type_uri, std::string uri, std::string elements, std::string encoding) :
            TopLevel(type_uri, uri),
            elements(SBOL_ELEMENTS, this, elements),
            encoding(SBOL_ENCODING, this, encoding)
            {
            };
        
        Sequence(sbol_type type_uri, std::string uri_prefix, std::string display_id, std::string version, std::string elements, std::string encoding) :
			TopLevel(type_uri, uri_prefix, display_id, version),
			elements(SBOL_ELEMENTS, this, elements),
			encoding(SBOL_ENCODING, this, encoding)
            {
            };
	};
}

#endif