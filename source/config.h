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
        void setHomespace(std::string ns);
        std::string getHomespace();
        int hasHomespace();
        void toggleSBOLCompliance();
        int isSBOLCompliant();
        void toggleSBOLCompliantTypes();
        int compliantTypesEnabled();
        void toggleExceptions();
        int exceptionsEnabled();
        void setFileFormat(std::string file_format);
        std::string getFileFormat();
        static void setOption(std::string option, std::string value);
        static std::string getOption(std::string option);
    };

	SBOL_DECLSPEC void setHomespace(std::string ns); ///< Set the default namespace for autocreation of URIs when a new SBOL object is created
	SBOL_DECLSPEC extern std::string getHomespace(); ///< Get the current default namespace for autocreation of URIs when a new SBOL object is created
	SBOL_DECLSPEC int hasHomespace();                ///< Checks if a valid default namespace has been defined
	SBOL_DECLSPEC void toggleSBOLCompliance();       ///< Enables SBOLCompliance, which simplifies creation of URIs in constructor calls
	SBOL_DECLSPEC int isSBOLCompliant();             ///< Checks if SBOLCompliance is enabled
	SBOL_DECLSPEC void toggleSBOLCompliantTypes();   ///< Turns option to include types in SBOL-compliant URIs on or off
	SBOL_DECLSPEC int compliantTypesEnabled();       ///< Checks if an object's type is included in SBOL-compliant URIs
	SBOL_DECLSPEC void setFileFormat(std::string file_format);
    std::string SBOL_DECLSPEC getFileFormat();
	SBOL_DECLSPEC void toggleExceptions();
	SBOL_DECLSPEC int exceptionsEnabled();
    
    std::string SBOL_DECLSPEC randomIdentifier();
    std::string SBOL_DECLSPEC autoconstructURI();
    std::string SBOL_DECLSPEC constructNonCompliantURI(std::string uri);
    std::string SBOL_DECLSPEC constructCompliantURI(std::string sbol_type, std::string display_id, std::string version);
    std::string SBOL_DECLSPEC constructCompliantURI(std::string parent_type, std::string child_type, std::string display_id, std::string version);
    std::string SBOL_DECLSPEC getCompliantURI(std::string uri_prefix, std::string sbol_class_name, std::string display_id, std::string version);
    std::string SBOL_DECLSPEC parseClassName(std::string uri);
    std::string SBOL_DECLSPEC parsePropertyName(std::string uri);
    std::string SBOL_DECLSPEC parseNamespace(std::string uri);
}

#endif /* CONFIG_INCLUDED */
