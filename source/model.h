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

        Model(std::string uri = DEFAULT_NS "/Model/example", std::string source = "", std::string language = EDAM_SBML, std::string framework = SBO_CONTINUOUS, std::string version = "1.0.0") : Model(SBOL_MODEL, uri, source, language, framework, version) {};

//        Model(std::string uri_prefix, std::string display_id, std::string version, std::string source, std::string language, std::string framework) : Model(SBOL_MODEL, uri_prefix, display_id, version, source, language, framework) {};

        ~Model() {};
	protected:
		// This protected constructor is a delegate constructor.  It initializes Models with the corresponding sbol_type_uri 
        Model(sbol_type type, std::string uri, std::string source, std::string language, std::string framework, std::string version) :
            TopLevel(type, uri, version),
            source(SBOL_SOURCE, this, source),
            language(SBOL_LANGUAGE, this, language),
            framework(SBOL_FRAMEWORK, this, framework)
            {
            };
//        Model(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string source, std::string language, std::string framework) :
//			TopLevel(type, uri_prefix, display_id, version),
//			source(SBOL_SOURCE, this, source),
//			language(SBOL_LANGUAGE, this, language),
//			framework(SBOL_FRAMEWORK, this, framework)
//			{
//            };
	};
}

#endif