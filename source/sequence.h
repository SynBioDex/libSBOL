#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include "toplevel.h"

#include <string>

namespace sbol
{
    /// The primary structure (eg, nucleotide or amino acid sequence) of a ComponentDefinition object
	class Sequence : public TopLevel
	{
	public:
		TextProperty elements;
		URIProperty encoding;

        Sequence(std::string uri = DEFAULT_NS "/Sequence/example", std::string elements = "", std::string encoding = SBOL_ENCODING_IUPAC, std::string version = "1.0.0") : Sequence(SBOL_SEQUENCE, uri, elements, encoding, version) {};
        
//        Sequence(std::string uri_prefix, std::string display_id, std::string version, std::string elements, std::string encoding) : Sequence(SBOL_SEQUENCE, uri_prefix, display_id, version, elements, encoding) {};

        virtual ~Sequence() {};
	protected:
		// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 

        Sequence(sbol_type type_uri, std::string uri, std::string elements, std::string encoding, std::string version) :
            TopLevel(type_uri, uri, version),
            elements(SBOL_ELEMENTS, this, elements),
            encoding(SBOL_ENCODING, this, encoding)
            {
            };
        
//        Sequence(sbol_type type_uri, std::string uri_prefix, std::string display_id, std::string version, std::string elements, std::string encoding) :
//			TopLevel(type_uri, uri_prefix, display_id, version),
//			elements(SBOL_ELEMENTS, this, elements),
//			encoding(SBOL_ENCODING, this, encoding)
//            {
//            };
	};
}

#endif