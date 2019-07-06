/**
 * @file    model.h
 * @brief   Model class
 * @author  Bryan Bartley
 * @email   bartleyba@sbolstandard.org
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBOL.  Please visit http://sbolstandard.org for more
 * information about SBOL, and the latest version of libSBOL.
 *
 *  Copyright 2016 University of Washington, WA, USA
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ------------------------------------------------------------------------->*/

#ifndef MODEL_INCLUDED
#define MODEL_INCLUDED

#include "toplevel.h"

namespace sbol
{
    /// The purpose of the Model class is to serve as a placeholder for an external computational model and provide additional meta-data to enable better reasoning about the contents of this model. In this way, there is minimal duplication of standardization efforts and users of SBOL can formalize the function of a ModuleDefinition in the language of their choice.
    /// @ingroup sbol_core_data_model
	class SBOL_DECLSPEC Model : public TopLevel
	{
	public:
        /// Construct a Model
        /// @param source A URI reference to the model file
        /// @param An EDAM ontology term that specifies the language in which the model was implemented
        /// @param An SBOL ontology term that specifies whether the model is continuous, discrete, or other modeling technique
        Model(std::string uri = "example", std::string source = "", std::string language = EDAM_SBML, std::string framework = SBO_CONTINUOUS, std::string version = VERSION_STRING) : Model(SBOL_MODEL, uri, source, language, framework, version) {};

        /// Constructor used for defining extension classes
        /// @param type The RDF type for an extension class derived from this one
        Model(rdf_type type, std::string uri, std::string source, std::string language, std::string framework, std::string version) :
            TopLevel(type, uri, version),
            source(this, SBOL_SOURCE, '0', '1', ValidationRules({}), source),
            language(this, SBOL_LANGUAGE, '0', '1', ValidationRules({}), language),
            framework(this, SBOL_FRAMEWORK, '0', '1', ValidationRules({}), framework)
            {
            };
        
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
        
        virtual ~Model() {};
    };
}

#endif