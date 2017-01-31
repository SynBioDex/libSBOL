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

using namespace sbol;
using namespace std;

extern Config& config = * new sbol::Config();  ///<  Global configuration object that governs library behavior, especially with regards to URI generation
//Config& config = * new sbol::Config();  ///<  Global configuration object that governs library behavior, especially with regards to URI generation


std::map<std::string, std::string> sbol::Config::options {
    {"homespace", "http://examples.org"},
    {"sbol_compliant_uris", "True"},
    {"sbol_typed_uris", "True"},
    {"output_format", "rdfxml"},
    {"validate", "True"},
    {"validator_url", "http://www.async.ece.utah.edu/sbol-validator/endpoint.php"},
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
    {"insert_type", "True"},
    {"main_file_name", "main file"},
    {"diff_file_name", "comparison file"},
    {"return_file", "True"}
};

std::map<std::string, std::vector<std::string>> sbol::Config::valid_options {
    {"sbol_compliant_uris", {"True", "False"}},
    {"sbol_typed_uris", { "True", "False" }},
    {"output_format", {"rdfxml", "json"}},
    {"validate", { "True", "False" }},
    {"language", { "SBOL2", "FASTA", "GenBank" }},
    {"test_equality", { "True", "False" }},
    {"check_uri_compliance", { "True", "False" }},
    {"check_completeness", { "True", "False" }},
    {"check_best_practices", { "True", "False" }},
    {"fail_on_first_error", { "True", "False" }},
    {"provide_detailed_stack_trace", { "True", "False" }},
    {"insert_type", { "True", "False" }},
    {"return_file", { "True", "False" }}
};

void sbol::Config::setOption(std::string option, std::string value)
{
    if (options.find(option) != options.end())
    {
        // Check if this option has valid arguments to validate against
        if (valid_options.find(option) != valid_options.end())
        {
            // Set the option if a valid argument is provided
            if (std::find(valid_options[option].begin(), valid_options[option].end(), value) != valid_options[option].end())
                options[option] = value;
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

void sbol::toggleSBOLCompliantTypes()
{
    config.toggleSBOLCompliantTypes();
};

int sbol::compliantTypesEnabled()
{
    return config.compliantTypesEnabled();
};


void sbol::toggleExceptions()
{
    config.toggleExceptions();
};

void Config::toggleExceptions()
{
    if (catch_exceptions)
        catch_exceptions = 0;
    else
        catch_exceptions = 1;
};

int sbol::exceptionsEnabled()
{
    return config.exceptionsEnabled();
}

int Config::exceptionsEnabled()
{
    return catch_exceptions;
}

void sbol::setFileFormat(std::string file_format)
{
    config.setFileFormat(file_format);
};

std::string sbol::getFileFormat()
{
    return config.getFileFormat();
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


void Config::toggleSBOLCompliantTypes()
{
    if (this->SBOLCompliantTypes == 0)
        this->SBOLCompliantTypes = 1;
    else
        this->SBOLCompliantTypes = 0;
};

int Config::compliantTypesEnabled()
{
    return this->SBOLCompliantTypes;
};

void Config::setFileFormat(std::string file_format)
{
    if (file_format.compare("json") == 0)
        this->format = "json";
    else
        this->format = "rdfxml";
};

std::string Config::getFileFormat()
{
    return format;
};
