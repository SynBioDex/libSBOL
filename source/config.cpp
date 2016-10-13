#include "config.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace sbol;
using namespace std;

extern Config& config = * new sbol::Config();  ///<  Global configuration object that governs library behavior, especially with regards to URI generation

// @TODO move sbol_type TYPEDEF declaration to this file and use sbol_type instead of string for 2nd argument
std::string sbol::constructCompliantURI(std::string sbol_type, std::string display_id, std::string version)
{
    if (isSBOLCompliant())
        return getHomespace() + "/" + getClassName(sbol_type) + "/" + display_id + "/" + version;
    else
        return "";
};

std::string sbol::constructCompliantURI(std::string parent_type, std::string child_type, std::string display_id, std::string version)
{
    if (isSBOLCompliant())
        return getHomespace() + "/" + getClassName(parent_type) + "/" + getClassName(child_type) + "/" + display_id + "/" + version;
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

std::string sbol::getClassName(std::string type)
{
    std::size_t uri_subordinate_pos = type.find("#") + 1;
    if (uri_subordinate_pos != std::string::npos)
    {
        std::string sbol_class = type.substr(uri_subordinate_pos, type.size() - uri_subordinate_pos);
        return sbol_class;
    }
    else
        return type;
};

std::string sbol::getNameSpace(std::string type)
{
    std::size_t uri_subordinate_pos = type.find("#") + 1;
    if (uri_subordinate_pos != std::string::npos)
    {
        std::string ns = type.substr(0, uri_subordinate_pos);
        cout << ns << endl;
        return ns;
    }
    else
        return type;
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

