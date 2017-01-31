/**
 * @file    config.h
 * @brief   Global library options and configuration methods
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

#if defined(SBOL_WIN)
#if defined(SBOL_SHAREDLIB)
#    define SBOL_DECLSPEC  __declspec(dllexport)
#else
#    define SBOL_DECLSPEC
#endif
#else
#    define SBOL_DECLSPEC
#endif

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#include "sbolerror.h"
#include <string>
#include <map>
#include <vector>

namespace sbol
{
    /// A class which contains global configuration variables for the libSBOL environment. Intended to be used like a static class, configuration variables are accessed through the `config' object.
    class SBOL_DECLSPEC Config
    {
    private:
        static std::map<std::string, std::string> options;
        static std::map<std::string, std::vector<std::string>> valid_options;
        std::string home; ///< The authoritative namespace for the Document. Setting the home namespace is like     signing a piece of paper.
        int SBOLCompliant; ///< Flag indicating whether to autoconstruct URI's consistent with SBOL's versioning scheme
        int SBOLCompliantTypes; ///< Flag indicating whether an object's type is included in SBOL-compliant URIs
        int catch_exceptions = 0;
        std::string format = "rdfxml";
    public:
        Config() :
        home(""),
        SBOLCompliant(1),
        SBOLCompliantTypes(1)
            {
            };
        /// @cond
        void setHomespace(std::string ns);  
        std::string getHomespace();
        int hasHomespace();
        void toggleSBOLCompliantTypes();
        int compliantTypesEnabled();
        void toggleExceptions();
        int exceptionsEnabled();
        void setFileFormat(std::string file_format);
        std::string getFileFormat();
        /// @endcond
        
        /// Configure options for online validation and conversion
        /// | Option                     | Description                                                              | Values          |
        /// | :------------------------- | :----------------------------------------------------------------------- | :-------------- |
        /// | validate                   | Enable validation and conversion requests through the online validator   | True or False
        /// | validatorURL               | The http request endpoint for validation                                 | A valid URL, set to<br>http://www.async.ece.utah.edu/sbol-validator/endpoint.php by default |
        /// | output                     | File format for conversion                                               | SBOL2, SBOL1, FASTA, GenBank |
        /// | diff                       | Report differences between two files                                     | True or False |
        /// | noncompliantUrisAllowed    | If set to false, URIs in the file will not be checked for compliance<br>with the SBOL specification | True or False |
        /// | incompleteDocumentsAllowed | If set to false, not all referenced objects must be described within<br>the given main_file | True or False |
        /// | bestPracticesCheck         | If set to true, the file is checked for the best practice rules set<br>in the SBOL specification | True or False |
        /// | failOnFirstError           | If set to true, the validator will fail at the first error               | True or False |
        /// | displayFullErrorStackTrace | If set to true (and failOnFirstError is true) the validator will<br>provide a stack trace for the first validation error | True or False |
        /// | topLevelToConvert          |                                                                          | |
        /// | uriPrefix                  | Required for conversion from FASTA and GenBank to SBOL1 or SBOL2,<br>used to generate URIs  | True or False |
        /// | version                    | Adds the version to all URIs and to the document                         | A valid Maven version string |
        /// | wantFileBack               | Whether or not to return the file contents as a string                   | True or False |
        /// @param option The option key
        /// @param value The option value
        static void setOption(std::string option, std::string value);
        
        /// Get current option value for online validation and conversion
        /// @param option The option key
        static std::string getOption(std::string option);
    };

	SBOL_DECLSPEC void setHomespace(std::string ns); ///< Set the default namespace for autocreation of URIs when a new SBOL object is created
	SBOL_DECLSPEC extern std::string getHomespace(); ///< Get the current default namespace for autocreation of URIs when a new SBOL object is created
	SBOL_DECLSPEC int hasHomespace();                ///< Checks if a valid default namespace has been defined
	SBOL_DECLSPEC void toggleSBOLCompliantTypes();   ///< Turns option to include types in SBOL-compliant URIs on or off
	SBOL_DECLSPEC int compliantTypesEnabled();       ///< Checks if an object's type is included in SBOL-compliant URIs
	SBOL_DECLSPEC void setFileFormat(std::string file_format);
    std::string SBOL_DECLSPEC getFileFormat();
	SBOL_DECLSPEC void toggleExceptions();
	SBOL_DECLSPEC int exceptionsEnabled();
    
    /// <!--------- Utility methods for parsing URIs ------\>
    /// @cond
    std::string SBOL_DECLSPEC randomIdentifier();
    std::string SBOL_DECLSPEC autoconstructURI();
    std::string SBOL_DECLSPEC constructNonCompliantURI(std::string uri);
    std::string SBOL_DECLSPEC constructCompliantURI(std::string sbol_type, std::string display_id, std::string version);
    std::string SBOL_DECLSPEC constructCompliantURI(std::string parent_type, std::string child_type, std::string display_id, std::string version);
    std::string SBOL_DECLSPEC getCompliantURI(std::string uri_prefix, std::string sbol_class_name, std::string display_id, std::string version);
    std::string SBOL_DECLSPEC parseClassName(std::string uri);
    std::string SBOL_DECLSPEC parsePropertyName(std::string uri);
    std::string SBOL_DECLSPEC parseNamespace(std::string uri);
    /// @endcond
}

#endif /* CONFIG_INCLUDED */
