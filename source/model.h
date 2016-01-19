#ifndef MODEL_INCLUDED
#define MODEL_INCLUDED

#include "toplevel.h"

namespace sbol
{
	class Model : public TopLevel
	{
	public:
		URIProperty source;
		URIProperty language;
		URIProperty framework;

		Model(std::string uri_prefix = SBOL_URI "/Model",
			std::string display_id = "example",
			std::string source = UNDEFINED,
			std::string language = UNDEFINED,
			std::string framework = UNDEFINED ) :
			Model(SBOL_MODEL, uri_prefix, display_id, source, language, framework)
			{
			}
		~Model();
	protected:
		// This protected constructor is a delegate constructor.  It initializes Models with the corresponding sbol_type_uri 
		Model(sbol_type sbol_type_uri, std::string uri_prefix, std::string display_id, std::string source, std::string language, std::string framework) :
			TopLevel(sbol_type_uri, uri_prefix, display_id, "", "", ""),
			source(SBOL_SOURCE, this, source),
			language(SBOL_LANGUAGE, this, language),
			framework(SBOL_FRAMEWORK, this, framework)
			{
			}
	};
}

#endif