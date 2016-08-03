#ifndef MODEL_INCLUDED
#define MODEL_INCLUDED

#include "toplevel.h"

namespace sbol
{
    /// The purpose of the Model class is to serve as a placeholder for an external computational model and provide additional meta-data to enable better reasoning about the contents of this model. In this way, there is minimal duplication of standardization efforts and users of SBOL can formalize the function of a ModuleDefinition in the language of their choice.
    /// @ingroup sbol_core_data_model
	class Model : public TopLevel
	{
	public:
        /// The source property is REQUIRED and MUST contain a URI reference to the source file for a model.
		URIProperty source;
        
        /// The language property is REQUIRED and MUST contain a URI that specifies the language in which the model is implemented. It is RECOMMENDED that this URI refer to a term from the EMBRACE Data and Methods (EDAM) ontology. The Table below provides a list of terms from this ontology and their URIs. If the language property of a Model is well-described by one these terms, then it MUST contain the URI for this term as its value.
        /// | Model Language | URI for EDAM Term                       | libSBOL Symbol |
        /// | :------------- | :-------------------------------------- | :------------- |
        /// | SBML           | http://identifiers.org/edam/format_2585 | EDAM_SBML      |
        /// | CellML         | http://identifiers.org/edam/format_3240 | EDAM_CELLML    |
        /// | BioPAX         | http://identifiers.org/edam/format_3156 | EDAM_BIOPAX    |
		URIProperty language;
        
        // The framework property is REQUIRED and MUST contain a URI that specifies the framework in which the model is implemented. It is RECOMMENDED this URI refer to a term from the modeling framework branch of the Systems Biology Ontology when possible. A few suggested modeling frameworks and their corresponding URIs are shown in the table below If the framework property of a Model is well-described by one these terms, then it MUST contain the URI for this term as its value.
        /// | Model Language | URI for SBO Term                                 | libSBOL Symbol |
        /// | :------------- | :------------------------------------------------| :------------- |
        /// | Continuous     | http://identifiers.org/biomodels.sbo/SBO:0000062 | SBO_CONTINUOUS |
        /// | Discrete       | http://identifiers.org/biomodels.sbo/SBO:0000063 | SBO_DISCRETE   |
        URIProperty framework;

        Model(std::string uri = DEFAULT_NS "/Model/example", std::string source = "", std::string language = EDAM_SBML, std::string framework = SBO_CONTINUOUS, std::string version = "1.0.0") : Model(SBOL_MODEL, uri, source, language, framework, version) {};

//        Model(std::string uri_prefix, std::string display_id, std::string version, std::string source, std::string language, std::string framework) : Model(SBOL_MODEL, uri_prefix, display_id, version, source, language, framework) {};

        virtual ~Model() {};
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