#ifndef TOP_LEVEL_INCLUDED
#define TOP_LEVEL_INCLUDED

#include "identified.h"

#include <string>

namespace sbol 
{
	class TopLevel : public Identified
	{

	// The public constructor delegates to this protected constructor in order to initialize the object with an SBOL type URI 
	protected:
		TopLevel(sbol_type type_uri, std::string uri_prefix, std::string display_id, std::string name, std::string description, std::string version) :
			Identified(type_uri, uri_prefix, display_id, name, description, version)
		{
		}	
	public:
		TopLevel(std::string uri_prefix = SBOL_URI "/TopLevel", std::string display_id = "example", std::string name = "", std::string description = "", std::string version = "") : TopLevel(SBOL_TOP_LEVEL, uri_prefix, display_id, name, description, version)
			{
			}
		void addToDocument(sbol::Document&);

	};
}

#endif