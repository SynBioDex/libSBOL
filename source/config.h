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
#include "constants.h"
#include <string>
#include <map>
#include <vector>
#include <curl/curl.h>
#include <iostream>

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
#include "Python.h"
#undef tolower
#endif

namespace sbol
{
    /// A class which contains global configuration variables for the libSBOL environment. Intended to be used like a static class, configuration variables are accessed through the Config::setOptions and Config::getOptions methods.
    class SBOL_DECLSPEC Config
    {
    friend class Document;      // needs to access PYTHON_DATA_MODEL_REGISTER
    friend class SBOLObject;    // needs to access PYTHON_DATA_MODEL_REGISTER
    
    private:
        static std::map<std::string, std::string> options;
        static std::map<std::string, std::vector<std::string>> valid_options;
        static std::map<std::string, std::string> extension_namespaces;

        std::string home; ///< The authoritative namespace for the Document. Setting the home namespace is like     signing a piece of paper.
        int SBOLCompliantTypes; ///< Flag indicating whether an object's type is included in SBOL-compliant URIs
        int catch_exceptions = 0;
        std::string format = "rdfxml";

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        // This is the global SBOL register for Python extension classes.  It maps an SBOL RDF type (eg, "http://sbolstandard.org/v2#Sequence" to a Python constructor
//        static PyObject* PYTHON_DATA_MODEL_REGISTER = PyDict_New();
        static std::map<std::string, PyObject*> PYTHON_DATA_MODEL_REGISTER;
#endif
        
    public:
        Config() :
        SBOLCompliantTypes(1)
            {
            };
        /// @cond
        void setHomespace(std::string ns);  
        std::string getHomespace();
        int hasHomespace();
        void setFileFormat(std::string file_format);
        std::string getFileFormat();
        /// @endcond

        /// Configure options for libSBOL. Access online validation and conversion.
        /// | Option                       | Description                                                              | Values          |
        /// | :--------------------------- | :----------------------------------------------------------------------- | :-------------- |
        /// | homespace                    | Enable validation and conversion requests through the online validator   | http://examples.org |
        /// | sbol_compliant_uris          | Enables autoconstruction of SBOL-compliant URIs from displayIds          | True or False   |
        /// | sbol_typed_uris              | Include the SBOL type in SBOL-compliant URIs                             | True or False   |
        /// | output_format                | File format for serialization                                            | True or False   |
        /// | validate                     | Enable validation and conversion requests through the online validator   | True or False   |
        /// | validator_url                | The http request endpoint for validation                                 | A valid URL, set to<br>http://www.async.ece.utah.edu/sbol-validator/endpoint.php by default |
        /// | language                     | File format for conversion                                               | SBOL2, SBOL1, FASTA, GenBank |
        /// | test_equality                | Report differences between two files                                     | True or False |
        /// | check_uri_compliance         | If set to false, URIs in the file will not be checked for compliance<br>with the SBOL specification | True or False |
        /// | check_completeness           | If set to false, not all referenced objects must be described within<br>the given main_file | True or False |
        /// | check_best_practices         | If set to true, the file is checked for the best practice rules set<br>in the SBOL specification | True or False |
        /// | fail_on_first_error          | If set to true, the validator will fail at the first error               | True or False |
        /// | provide_detailed_stack_trace | If set to true (and failOnFirstError is true) the validator will<br>provide a stack trace for the first validation error | True or False |
        /// | uri_prefix                   | Required for conversion from FASTA and GenBank to SBOL1 or SBOL2,<br>used to generate URIs  | True or False |
        /// | version                      | Adds the version to all URIs and to the document                         | A valid Maven version string |
        /// | return_file                  | Whether or not to return the file contents as a string                   | True or False |
        /// @param option The option key
        /// @param value The option value
        static void setOption(std::string option, std::string value);
        
        static void setOption(std::string option, char const* value);
        
        static void setOption(std::string option, bool value);

        /// Get current option value for online validation and conversion
        /// @param option The option key
        static std::string getOption(std::string option);

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)

        static void register_extension_class(PyObject* python_class, std::string extension_name);

#endif 
    
    };
    
    /// Global methods
	SBOL_DECLSPEC void setHomespace(std::string ns); ///< Set the default namespace for autocreation of URIs when a new SBOL object is created
	SBOL_DECLSPEC extern std::string getHomespace(); ///< Get the current default namespace for autocreation of URIs when a new SBOL object is created
	SBOL_DECLSPEC int hasHomespace();                ///< Checks if a valid default namespace has been defined
	SBOL_DECLSPEC void setFileFormat(std::string file_format);    ///< Sets file format to use
    std::string SBOL_DECLSPEC getFileFormat();       ///< Returns currently accepted file format
    
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
    std::string SBOL_DECLSPEC parseURLDomain(std::string url);
    int SBOL_DECLSPEC getTime();


    size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s);
    size_t CurlResponseHeader_CallbackFunc(char *buffer,   size_t size,   size_t nitems,   void *userdata);
    /// @endcond
}

#endif /* CONFIG_INCLUDED */
