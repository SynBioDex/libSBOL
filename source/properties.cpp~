/**
 * @file    properties.cpp
 * @brief   Property template classes (eg, TextProperty, URIProperty, IntProperty)
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

#include "object.h"

#include <stdexcept>      // std::invalid_argument

#include <vector>
#include <utility>
#include <time.h>

#ifndef SBOL_BUILD_MANYLINUX
#include <regex>
#endif

using namespace sbol;
using namespace std;

/// @return A string literal
std::string TextProperty::get()
{
    if (this->sbol_owner)
    {
        // check if property a valid member of this object (mismatching of properties can result from improper template calls)
        if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
        {
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "This object does not have a property of type " + type);
        }
        else
        {
            // property value not set
            if (this->sbol_owner->properties[type].size() == 0)
                throw SBOLError(SBOL_ERROR_NOT_FOUND, "The " + type + " property has not been set");
            // property value is found
            else
            {
                std::string value = this->sbol_owner->properties[type].front();
                value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                if (value == "")
                    throw SBOLError(SBOL_ERROR_NOT_FOUND, "The " + type + " property has not been set");
                return value;
            }
        }
    }	else
    {
        throw SBOLError(SBOL_ERROR_ORPHAN_OBJECT, "Property " + type + " is not a member of a parent SBOLObject");    }
};

/// @return A string of characters used to identify a resource
std::string URIProperty::get()
{
    if (this->sbol_owner)
    {
        // check if property a valid member of this object (mismatching of properties can result from improper template calls)
        if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
        {
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "This object does not have a property of type " + type);
        }
        else
        {
            // property value not set
            if (this->sbol_owner->properties[type].size() == 0)
                throw SBOLError(SBOL_ERROR_NOT_FOUND, "Property has not been set");
            // property value is found
            else
            {
                std::string value = this->sbol_owner->properties[type].front();
                value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                if (value == "")
                    throw SBOLError(SBOL_ERROR_NOT_FOUND, "The " + type + " property has not been set");
                return value;
            }
        }
    }	else
    {
        throw SBOLError(SBOL_ERROR_ORPHAN_OBJECT, "Property " + type + " is not a member of a parent SBOLObject");    }
};

/// @return An integer
int IntProperty::get()
{
    if (this->sbol_owner)
    {
        // check if property a valid member of this object (mismatching of properties can result from improper template calls)
        if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
        {
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "This object does not have a property of type " + type);
        }
        else
        {
            // property value not set
            if (this->sbol_owner->properties[type].size() == 0)
                throw SBOLError(SBOL_ERROR_NOT_FOUND, "Property has not been set");
            // property value is found
            else
            {
                std::string value = this->sbol_owner->properties[type].front();
                value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                if (value == "")
                    throw SBOLError(SBOL_ERROR_NOT_FOUND, "The " + type + " property has not been set");
                return stoi(value);
            }
        }
    }	else
    {
        throw SBOLError(SBOL_ERROR_ORPHAN_OBJECT, "Property " + type + " is not a member of a parent SBOLObject");    }
};

/// @return An integer
double FloatProperty::get()
{
    if (this->sbol_owner)
    {
        // check if property a valid member of this object (mismatching of properties can result from improper template calls)
        if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
        {
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "This object does not have a property of type " + type);
        }
        else
        {
            // property value not set
            if (this->sbol_owner->properties[type].size() == 0)
                throw SBOLError(SBOL_ERROR_NOT_FOUND, "Property has not been set");
            // property value is found
            else
            {
                std::string value = this->sbol_owner->properties[type].front();
                value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                if (value == "")
                    throw SBOLError(SBOL_ERROR_NOT_FOUND, "The " + type + " property has not been set");
                return stod(value);
            }
        }
    }	else
    {
        throw SBOLError(SBOL_ERROR_ORPHAN_OBJECT, "Property " + type + " is not a member of a parent SBOLObject");    }
};

void VersionProperty::incrementMinor()
{
#ifndef SBOL_BUILD_MANYLINUX
    pair< vector<string>, vector<string> > v = this->split();
    vector< string > v_tokens = v.first;
    vector< string > v_delimiters = v.second;
    
    if (v_tokens.size() < 2)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Maven version string does not have a minor version");
    
    // Increment minor version
    regex d("([0-9]+)");
    smatch m;
    regex_search(v_tokens[1], m, d);
    string minor_version = to_string(stoi(v_tokens[1]) + 1) + m.suffix().str();
    v_tokens[1] = minor_version;
    
    // Concatenate new version string
    string new_version;
    unsigned int i_v = 0;
    do
    {
        new_version += v_tokens[i_v] + v_delimiters[i_v];
        ++i_v;
    } while (i_v < v_tokens.size() - 1);
    new_version += v_tokens[i_v];
    this->set(new_version);
    
    /// Update the identity if SBOLCompliant
    if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
    {
        SBOLObject* parent_obj = this->sbol_owner;
        std::string persistentIdentity;
        if (parent_obj->properties.find(SBOL_PERSISTENT_IDENTITY) != parent_obj->properties.end())
        {
            persistentIdentity = parent_obj->properties[SBOL_PERSISTENT_IDENTITY].front();
            persistentIdentity = persistentIdentity.substr(1, persistentIdentity.length() - 2);  // Removes flanking < and > from the uri
        }
        parent_obj->identity.set(persistentIdentity + "/" + new_version);
    }
#endif
};

void VersionProperty::incrementMajor()
{
#ifndef SBOL_BUILD_MANYLINUX
    pair< vector<string>, vector<string> > v = this->split();
    vector< string > v_tokens = v.first;
    vector< string > v_delimiters = v.second;

    if (v_tokens.size() < 1)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Maven version string does not have a valid major version");
    
    // Increment major version
    regex d("([0-9]+)");
    smatch m;
    regex_search(v_tokens[0], m, d);
    string major_version = to_string(stoi(v_tokens[0]) + 1) + m.suffix().str();
    v_tokens[0] = major_version;
    
    // Concatenate new version string
    string new_version;
    if (v_tokens.size() == 1)
        new_version = v_tokens[0];
    else
    {
        // Insert delimiters
        unsigned int i_v = 0;
        do
        {
            new_version += v_tokens[i_v] + v_delimiters[i_v];
            ++i_v;
        } while (i_v < v_tokens.size() - 1);
        new_version += v_tokens[i_v];
    }
    this->set(new_version);
    
    /// Update the identity if SBOLCompliant
    if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
    {
        SBOLObject* parent_obj = this->sbol_owner;
        std::string persistentIdentity;
        if (parent_obj->properties.find(SBOL_PERSISTENT_IDENTITY) != parent_obj->properties.end())
        {
            persistentIdentity = parent_obj->properties[SBOL_PERSISTENT_IDENTITY].front();
            persistentIdentity = persistentIdentity.substr(1, persistentIdentity.length() - 2);  // Removes flanking < and > from the uri
        }
        parent_obj->identity.set(persistentIdentity + "/" + new_version);
    }
#endif
};

void VersionProperty::incrementPatch()
{
#ifndef SBOL_BUILD_MANYLINUX
    pair< vector<string>, vector<string> > v = this->split();
    vector< string > v_tokens = v.first;
    vector< string > v_delimiters = v.second;
    
    // Increment patch version
    if (v_tokens.size() < 3)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Maven version string does not have a minor version");
    regex d("([0-9]+)");
    smatch m;
    regex_search(v_tokens[2], m, d);
    string patch_version = to_string(stoi(v_tokens[2]) + 1) + m.suffix().str();
    v_tokens[2] = patch_version;
    
    // Concatenate new version string
    string new_version;
    unsigned int i_v = 0;
    do
    {
        new_version += v_tokens[i_v] + v_delimiters[i_v];
        ++i_v;
    } while (i_v < v_tokens.size() - 1);
    new_version += v_tokens[i_v];
    this->set(new_version);
    
    /// Update the identity if SBOLCompliant
    if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
    {
        SBOLObject* parent_obj = this->sbol_owner;
        std::string persistentIdentity;
        if (parent_obj->properties.find(SBOL_PERSISTENT_IDENTITY) != parent_obj->properties.end())
        {
            persistentIdentity = parent_obj->properties[SBOL_PERSISTENT_IDENTITY].front();
            persistentIdentity = persistentIdentity.substr(1, persistentIdentity.length() - 2);  // Removes flanking < and > from the uri
        }
        parent_obj->identity.set(persistentIdentity + "/" + new_version);
    }
#endif
};

void VersionProperty::decrementMinor()
{
};

void VersionProperty::decrementMajor()
{
};

void VersionProperty::decrementPatch()
{
};

/// @return The major version as an integer
/// Splits the version string by a delimiter and returns the major version number
int VersionProperty::major()
{
    pair< vector<string>, vector<string> > v = this->split();
    vector< string > v_tokens = v.first;
    vector< string > v_delimiters = v.second;
    int major_version = stoi(v_tokens[0]);
    return major_version;
};

/// @return The minor version as an integer
/// Splits the version string by a delimiter and returns the minor version number
int VersionProperty::minor()
{
    pair< vector<string>, vector<string> > v = this->split();
    vector< string > v_tokens = v.first;
    vector< string > v_delimiters = v.second;
    
    int minor_version;
    try
    {
        // bitset constructor throws an invalid_argument if initialized
        // with a string containing characters other than 0 and 1
        minor_version = stoi(v_tokens[1]);
    }
    catch (const std::invalid_argument& ia)
    {
        std::cerr << "Invalid minor version: " << ia.what() << "\nMinor version must begin with an int";
    }
    return minor_version;
};

/// @return The patch version as an integer
/// Splits the version string by a delimiter and returns the patch version
int VersionProperty::patch()
{
    pair< vector<string>, vector<string> > v = this->split();
    vector< string > v_tokens = v.first;
    vector< string > v_delimiters = v.second;
    
    int patch_version;
    try
    {
        // bitset constructor throws an invalid_argument if initialized
        // with a string containing characters other than 0 and 1
        patch_version = stoi(v_tokens[2]);
    }
    catch (const std::invalid_argument& ia)
    {
        std::cerr << "Invalid patch version: " << ia.what() << "\nPatch number must begin with an int";
    }
    return patch_version;
};


vector<string> VersionProperty::split(const char c)
{
      // Adapted from C++ cookbook
    const string& s = this->get();
    vector<string> v;

    string::size_type i = 0;
    string::size_type j = s.find(c);

    while (j != string::npos)
    {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);
        if (j == string::npos)
            v.push_back(s.substr(i, s.length()));
    }
    return v;
}

pair < vector<string>, vector<string> > VersionProperty::split()
{
#ifndef SBOL_BUILD_MANYLINUX
    // Adapted from C++ cookbook
    const string& s = this->get();
    vector<string> tokens;
    vector<string> delimiters;
    
    std::regex rgx("[-|.|\\\\|_]");
    std::sregex_token_iterator i_token(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;
    while (i_token != end)
    {
        tokens.push_back(*i_token);
        ++i_token;
    }
    
    std::sregex_token_iterator i_delimiter(s.begin(), s.end(), rgx);
    while (i_delimiter != end)
    {
        delimiters.push_back(*i_delimiter);
        ++i_delimiter;
    }
    
    return make_pair(tokens, delimiters);
#endif
}

string DateTimeProperty::stampTime()
{
    time_t curtime;
    struct tm * GMT;
    string stamp;
    
    time(&curtime);
    GMT = gmtime(&curtime);
    curtime = mktime(GMT);
    stamp = string(ctime(&curtime));
    stamp.erase(stamp.length()-1, 1);

    // Split date string at delimiter (adapted from C++ cookbook)
    const char delimiter = ' ';
    vector<string> tokens;
    string::size_type i = 0;
    string::size_type j = stamp.find(delimiter);
    
    while (j != string::npos)
    {
        tokens.push_back(stamp.substr(i, j - i));
        i = ++j;
        j = stamp.find(delimiter, j);
        if (j == string::npos)
            tokens.push_back(stamp.substr(i, stamp.length()));
    }
    
    // Format into DateTime XSD Schema
    string month = tokens[1];
    string day = tokens[2];
    string t = tokens[3];
    string yr = tokens[4];
    
    if (month.compare("Jan") == 0)
        month = "01";
    else if(month.compare("Feb") == 0)
        month = "02";
    else if(month.compare("Mar") == 0)
        month = "03";
    else if(month.compare("Apr") == 0)
        month = "04";
    else if(month.compare("May") == 0)
        month = "05";
    else if(month.compare("Jun") == 0)
        month = "06";
    else if(month.compare("Jul") == 0)
        month = "07";
    else if(month.compare("Aug") == 0)
        month = "08";
    else if(month.compare("Sep") == 0)
        month = "09";
    else if(month.compare("Oct") == 0)
        month = "10";
    else if(month.compare("Nov") == 0)
        month = "11";
    else if(month.compare("Nov") == 0)
        month = "12";
    return stamp;
}



