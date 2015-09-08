#ifndef TOP_LEVEL_INCLUDED
#define TOP_LEVEL_INCLUDED

#include "documented.h"

#include <string>

namespace sbol 
{
	class TopLevel : public Documented
	{

	// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
	protected:
		TopLevel(sbol_type type, std::string uri_prefix, std::string display_id, std::string name, std::string description) :
			Documented(type, uri_prefix, display_id, name, description)
		{
		}	
	public:
		TopLevel(std::string uri_prefix = SBOL_URI "/TopLevel", std::string display_id = "example") : TopLevel(SBOL_TOP_LEVEL, uri_prefix, display_id, "", "")
			{
			}
		void addToDocument(sbol::Document&);

	};
}

#endif