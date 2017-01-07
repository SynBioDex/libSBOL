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
    {"validate", "True"},
    {"validatorURL", "http://www.async.ece.utah.edu/sbol-validator/endpoint.php"},
    {"output", "SBOL2"},
    {"diff", "False"},
    {"noncompliantUrisAllowed", "False"},
    {"incompleteDocumentsAllowed", "False"},
    {"bestPracticesCheck", "False"},
    {"failOnFirstError", "False"},
    {"displayFullErrorStackTrace", "False"},
    {"topLevelToConvert", ""},
    {"uriPrefix", ""},
    {"version", ""},
    {"wantFileBack", "False"}
};
std::map<std::string, std::vector<std::string>> sbol::Config::valid_options {
    {"validate", { "True", "False" }},
    {"output", { "SBOL2", "FASTA", "GenBank" }},
    {"diff", { "True", "False" }},
    {"noncompliantUrisAllowed", { "True", "False" }},
    {"incompleteDocumentsAllowed", { "True", "False" }},
    {"bestPracticesCheck", { "True", "False" }},
    {"failOnFirstError", { "True", "False" }},
    {"displayFullErrorStackTrace", { "True", "False" }},
    {"topLevelToConvert", {"", "True", "False" }},
    {"wantFileBack", {"True", "False"}}
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
    if (isSBOLCompliant())
        return getHomespace() + "/" + parseClassName(sbol_type) + "/" + display_id + "/" + version;
    else
        return "";
};

std::string sbol::constructCompliantURI(std::string parent_type, std::string child_type, std::string display_id, std::string version)
{
    if (isSBOLCompliant())
        return getHomespace() + "/" + parseClassName(parent_type) + "/" + parseClassName(child_type) + "/" + display_id + "/" + version;
    else
        return "";
};

// This autoconstruct method constructs non-SBOL-compliant URIs
std::string sbol::constructNonCompliantURI(std::string uri)
{
    if (!isSBOLCompliant() && hasHomespace())
        return getHomespace() + "/" + uri;
    else if (!isSBOLCompliant() && !hasHomespace())
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
    if (!isSBOLCompliant() && hasHomespace())
        return getHomespace() + "/" + randomIdentifier();
    else if (isSBOLCompliant() && !hasHomespace())
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "The autoconstructURI method requires a valid namespace authority. Use setHomespace().");
    else
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "The autoconstructURI method only works when SBOLCompliance flag is false. Use toggleSBOLCompliance().");
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

void sbol::toggleSBOLCompliance()
{
    config.toggleSBOLCompliance();
};

int sbol::isSBOLCompliant()
{
    return config.isSBOLCompliant();
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
    this->home = ns;
};

string Config::getHomespace()
{
    return this->home;
};

int Config::hasHomespace()
{
    if (this->home.compare("") == 0)
        return 0;
    else
        return 1;
};

void Config::toggleSBOLCompliance()
{
    if (this->SBOLCompliant == 0)
        this->SBOLCompliant = 1;
    else
        this->SBOLCompliant = 0;
};

int Config::isSBOLCompliant()
{
    return this->SBOLCompliant;
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
