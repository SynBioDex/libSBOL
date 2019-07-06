/**
 * @file    config.cpp
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

#include "config.h"

#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include <algorithm>
#include <json/json.h>
#include <curl/curl.h>
#include <unordered_map>

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
#include "Python.h"
#undef tolower
#endif

using namespace sbol;
using namespace std;

extern Config& config = * new sbol::Config();  ///<  Global configuration object that governs library behavior, especially with regards to URI generation
//Config& config = * new sbol::Config();  ///<  Global configuration object that governs library behavior, especially with regards to URI generation

std::map<std::string, std::string> sbol::Config::options {
    {"homespace", "http://examples.org"},
    {"sbol_compliant_uris", "True"},
    {"sbol_typed_uris", "True"},
    {"serialization_format", "sbol"},
    {"validate", "True"},
    {"validator_url", "http://www.async.ece.utah.edu/validate/"},
    {"language", "SBOL2"},
    {"test_equality", "False"},
    {"check_uri_compliance", "False"},
    {"check_completeness", "False"},
    {"check_best_practices", "False"},
    {"fail_on_first_error", "False"},
    {"provide_detailed_stack_trace", "False"},
    {"uri_prefix", ""},
    {"subset_uri", ""},
    {"version", ""},
    {"insert_type", "False"},
    {"main_file_name", "main file"},
    {"diff_file_name", "comparison file"},
    {"return_file", "False"},
    {"verbose", "False"},
    {"ca-path", ""}

};

std::map<std::string, std::vector<std::string>> sbol::Config::valid_options {
    {"sbol_compliant_uris", {"True", "False"}},
    {"sbol_typed_uris", { "True", "False" }},
    {"serialization_format", {"sbol", "rdfxml", "json", "ntriples"}},
    {"validate", { "True", "False" }},
    {"language", { "SBOL2", "FASTA", "GenBank" }},
    {"test_equality", { "True", "False" }},
    {"check_uri_compliance", { "True", "False" }},
    {"check_completeness", { "True", "False" }},
    {"check_best_practices", { "True", "False" }},
    {"fail_on_first_error", { "True", "False" }},
    {"provide_detailed_stack_trace", { "True", "False" }},
    {"insert_type", { "True", "False" }},
    {"return_file", { "True", "False" }},
    {"verbose", { "True", "False" }}
};

std::map<std::string, std::string> sbol::Config::extension_namespaces {};

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
std::map<std::string, PyObject*> sbol::Config::PYTHON_DATA_MODEL_REGISTER {};

void sbol::Config::register_extension_class(PyObject* python_class, std::string extension_name)
{
    // Construct a dummy object and parse its RDF type
    string rdf_type;
    try
    {
        PyObject* py_obj = PyObject_CallFunction(python_class, NULL);            
        PyObject* py_string = PyObject_GetAttr(py_obj, PyUnicode_FromString("type"));
        if (PyUnicode_Check(py_string)) 
        {
            PyObject * temp_bytes = PyUnicode_AsEncodedString(py_string, "UTF-8", "strict"); // Owned reference
            if (temp_bytes != NULL) 
            {
                char* result = PyBytes_AS_STRING(temp_bytes); // Borrowed pointer
                rdf_type = string(strdup(result));
                Py_DECREF(temp_bytes);
            } 
        }
        else if (PyBytes_Check(py_string)) 
        {
            char* result = PyBytes_AS_STRING(py_string); // Borrowed pointer
            rdf_type = string(strdup(result));
        }
        Py_DECREF(py_string);
        Py_DECREF(py_obj);
    }
    catch(...)
    {
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Registration of extension class failed. Extension classes must have a valid RDF type and default constructor");
    }

    // Register the extension's prefix and namespace
    if (Config::extension_namespaces.find(extension_name) == Config::extension_namespaces.end())
    {
        Config::extension_namespaces[extension_name] = parseNamespace(rdf_type);
    }
    else if (Config::extension_namespaces[extension_name] != parseNamespace(rdf_type))
    {
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Registration of extension class failed. This extension is already registered to a different namespace");        
    }

    // Register the class constructor
    Config::PYTHON_DATA_MODEL_REGISTER[rdf_type] = python_class;
};
#endif

void sbol::Config::setOption(std::string option, char const* value)
{
    Config::setOption(option, std::string(value));
}

void sbol::Config::setOption(std::string option, std::string value)
{
    if (options.find(option) != options.end())
    {
        // Check if this option has valid arguments to validate against
        if (valid_options.find(option) != valid_options.end())
        {
            // Set the option if a valid argument is provided
            if (std::find(valid_options[option].begin(), valid_options[option].end(), value) != valid_options[option].end())
            {
                options[option] = value;

            }
            else
            {
                // Format error message
                std::string msg;
                for (auto const& arg : valid_options[option]) { msg += arg + ", "; }
                msg[msg.size()-2] = '.';  // Replace last , with a .
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, value + " not a valid value for this option. Valid options are " + msg);

            }
        }
        else
            // Any argument is valid, eg uriPrefix
            options[option] = value;
    }
    else
    {
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, option + " not a valid configuration option for libSBOL");
    }
};

void sbol::Config::setOption(std::string option, bool value)
{
    string val_str;
    if (value == true)
    {
        val_str = "True";
    }
    else if (value == false)
    {
        val_str = "False";
    }
    if (options.find(option) != options.end())
    {
        // Check if this option has valid arguments to validate against
        if (valid_options.find(option) != valid_options.end())
        {
            // Set the option if a valid argument is provided
            if (std::find(valid_options[option].begin(), valid_options[option].end(), val_str) != valid_options[option].end())
                options[option] = val_str;
            else
            {
                // Format error message
                std::string msg;
                for (auto const& arg : valid_options[option]) { msg += arg + ", "; }
                msg[msg.size()-2] = '.';  // Replace last , with a .
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, val_str + " not a valid value for this option. Valid options are " + msg);
                
            }
        }
        else
            // Any argument is valid, eg uriPrefix
            options[option] = val_str;
    }
    else
    {
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, option + " not a valid configuration option for libSBOL");
    }
}


std::string sbol::Config::getOption(std::string option)
{
    if (options.find(option) != options.end())
    {
        return options[option];
    }
    else
    {
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, option + " not a valid configuration option for libSBOL");
    }
};

// @TODO move sbol_type TYPEDEF declaration to this file and use sbol_type instead of string for 2nd argument
std::string sbol::constructCompliantURI(std::string sbol_type, std::string display_id, std::string version)
{
    if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
        return getHomespace() + "/" + parseClassName(sbol_type) + "/" + display_id + "/" + version;
    else
        return "";
};

std::string sbol::constructCompliantURI(std::string parent_type, std::string child_type, std::string display_id, std::string version)
{
    if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
        return getHomespace() + "/" + parseClassName(parent_type) + "/" + parseClassName(child_type) + "/" + display_id + "/" + version;
    else
        return "";
};

// This autoconstruct method constructs non-SBOL-compliant URIs
std::string sbol::constructNonCompliantURI(std::string uri)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0 && hasHomespace())
        return getHomespace() + "/" + uri;
    else if (Config::getOption("sbol_compliant_uris").compare("False") == 0 && !hasHomespace())
        return uri;
    else
        return "";
};

// Defines format for randomly generated identifier strings to be used in autoconstructed URIs
string sbol::randomIdentifier()
{
    string id;
    srand(time(NULL));
    for (auto i = 1; i <= 16; i++)
    {
        int r_digit = rand() % 10;
        //id = id + to_string(r_digit);
        id = r_digit;
        if (r_digit % 4 == 0 && r_digit != 16)
            id = id + "-";
    }
    return id;
}

// This autoconstruct method constructs non-SBOL-compliant URIs
std::string sbol::autoconstructURI()
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0 && hasHomespace())
        return getHomespace() + "/" + randomIdentifier();
    else if (Config::getOption("sbol_compliant_uris").compare("False") == 0 && !hasHomespace())
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "The autoconstructURI method requires a valid namespace authority. Use setHomespace().");
    else
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "The autoconstructURI method only works when SBOLCompliance flag is false. Use setOption to disable SBOL-compliant URIs.");
};

std::string sbol::getCompliantURI(std::string uri_prefix, std::string sbol_class_name, std::string display_id, std::string version)
{
    return uri_prefix + "/" + sbol_class_name + "/" + display_id + "/" + version;
    
};

/// Parse a class name from a URI
/// @param uri A URI
std::string sbol::parseClassName(std::string uri)
{
    std::size_t uri_subordinate_pos = uri.find_last_of("#");
    if (uri_subordinate_pos != std::string::npos)
    {
        uri_subordinate_pos += 1;
        std::string sbol_class = uri.substr(uri_subordinate_pos, uri.size() - uri_subordinate_pos);
        return sbol_class;
    }
    uri_subordinate_pos = uri.find_last_of("/", uri.size());
    if (uri_subordinate_pos != std::string::npos)
    {
        uri_subordinate_pos += 1;
        std::string sbol_class = uri.substr(uri_subordinate_pos, uri.size() - uri_subordinate_pos);
        return sbol_class;
    }
    else
        return "";
};

std::string sbol::parseNamespace(std::string uri)
{
    std::size_t uri_subordinate_pos = uri.find_last_of("#");
    if (uri_subordinate_pos != std::string::npos)
    {
        uri_subordinate_pos += 1;
        std::string ns = uri.substr(0, uri_subordinate_pos);
        return ns;
    }
    uri_subordinate_pos = uri.find_last_of("/", uri.size());
    if (uri_subordinate_pos != std::string::npos)
    {
        uri_subordinate_pos += 1;
        std::string ns = uri.substr(0, uri_subordinate_pos);
        return ns;
    }
    else
        return "";
};

std::string sbol::parseURLDomain(std::string url)
{
    std::size_t url_begin_pos = url.find("://");
    std::size_t url_end_pos = url.find("/", url_begin_pos + 3);
    if (url_end_pos != std::string::npos)
    {
        std::string domain_name = url.substr(0, url_end_pos);
        return domain_name;
    }
    else
        return url;
};

std::string sbol::parsePropertyName(std::string uri)
{
//    std::size_t uri_subordinate_pos = uri.find("#") + 1;
//    if (uri_subordinate_pos != std::string::npos)
//    {
//        std::string ns = uri.substr(uri_subordinate_pos, uri.size() - uri_subordinate_pos);
//        return ns;
//    }
//    uri_subordinate_pos = uri.find("/", 0) + 1;
//    if (uri_subordinate_pos != std::string::npos)
//    {
//        std::string ns = uri.substr(uri_subordinate_pos, uri.size() - uri_subordinate_pos);
//        return ns;
//    }
//    else
//        throw;
    return parseClassName(uri);
};



void sbol::setHomespace(std::string ns)
{
    config.setHomespace(ns);
};

std::string sbol::getHomespace()
{
    return config.getHomespace();
};

int sbol::hasHomespace()
{
    if (config.getHomespace().compare("") == 0)
        return 0;
    else
        return 1;
};

void sbol::setFileFormat(std::string file_format)
{
    config.setFileFormat(file_format);
};

std::string sbol::getFileFormat()
{
    return config.getFileFormat();
};

int sbol::getTime()
{
    time_t curtime;
    struct tm * GMT;
    string stamp;
    
    time(&curtime);
    GMT = gmtime(&curtime);
    curtime = mktime(GMT);
    stamp = string(ctime(&curtime));
    stamp.erase(stamp.length()-1, 1);

    // // Split date string at delimiter (adapted from C++ cookbook)
    // char delimiter = ' ';
    // vector<string> tokens;
    // string::size_type i = 0;
    // string::size_type j = stamp.find(delimiter);
    
    // while (j != string::npos)
    // {
    //     string token = stamp.substr(i, j - i);
    //     if (token != " ")
    //         tokens.push_back(token);
    //     i = ++j;
    //     j = stamp.find(delimiter, j);
    //     if (j == string::npos)
    //         tokens.push_back(stamp.substr(i, stamp.length()));
    // }
    

    // Split date string at delimiter (adapted from C++ cookbook)
    char delimiter = ':';
    string::size_type i = stamp.find(delimiter);
    string hours = stamp.substr(i-2, 2);
    string minutes = stamp.substr(i+1, 2);
    i = stamp.find(delimiter, i+1);
    string seconds = stamp.substr(i+1, 2);

    int total_seconds = stoi(hours)*3600 + stoi(minutes)*60 + stoi(seconds);
    return total_seconds;
};

void Config::setHomespace(std::string ns)
{
    options["homespace"] = ns;
};

string Config::getHomespace()
{
    return options["homespace"];
};

int Config::hasHomespace()
{
    if (options["homespace"].compare("") == 0)
        return 0;
    else
        return 1;
};

void Config::setFileFormat(std::string file_format)
{
    if (file_format.compare("json") == 0)
        this->format = "json";
    else if (file_format == "ntriples")
        this->format = "ntriples";
    else
        this->format = "rdfxml";
};

std::string Config::getFileFormat()
{
    return format;
};


/* This callback is necessary to get the HTTP response as a string */
size_t sbol::CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }
    
    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
};

size_t sbol::CurlResponseHeader_CallbackFunc(char *buffer,   size_t size,   size_t nitems,   void *userdata)
{
    if (userdata)
    {
        std::unordered_map<std::string, std::string>& headers = *(std::unordered_map<std::string, std::string>*)userdata;
        size_t header_length = size * nitems;
        std::string header = std::string(buffer);
        std::size_t delimiter_pos = header.find(':');
        if (delimiter_pos != std::string::npos)
        {
            std::string key = header.substr(0, delimiter_pos);
            std::string val = header.substr(delimiter_pos + 1, header_length - 2 - delimiter_pos);
            headers[key] = val;
        }
        //userdata = &headers;
    }
    return size * nitems;
};


