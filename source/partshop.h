/**
 * @file    partshop.h
 * @brief   API front-end for online bioparts repositories
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

#ifndef PART_SHOP_INCLUDED
#define PART_SHOP_INCLUDED

#include "assembly.h"
#include <string>
#include <map>
#include <vector>
#include <curl/curl.h>
#include <iostream>
#include <algorithm>
#include <json/json.h>

namespace sbol
{
    class SBOL_DECLSPEC SearchQuery : public TopLevel
    {
    public:
        URIProperty objectType;
        IntProperty offset;
        IntProperty limit;
        
        TextProperty operator[] (std::string uri)
        {
            // If the URI has a namespace, treat the function argument as a full URI
            if (parseNamespace(uri).compare("") == 0)
                return TextProperty(SBOL_URI "#" + uri, this);
            else
                return TextProperty(uri, this);
        };  ///< Retrieve a child object by URI

        SearchQuery(sbol_type type = SBOL_COMPONENT_DEFINITION) :
            TopLevel(SBOL_URI "#SearchQuery", "example"),
            objectType(SBOL_URI "#objectType", this, type),
            offset(SBOL_URI "#offset", this, 0),
            limit(SBOL_URI "#limit", this, 25)
        {
            // The following properties are set to empty string because they are treated like search criteria
            displayId.set("");
            persistentIdentity.set("");
            version.set("");
        };
    };

    class SBOL_DECLSPEC SearchResponse : public TopLevel
    {
    friend class PartShop;
    
    public:
        int size()
        {
            return (int)records.size();
        }
        
        Identified& operator[] (int i)
        {
            // If the URI has a namespace, treat the function argument as a full URI
            if (i < records.size())
                return *records[i];
            else
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Index out of range");
        };  ///< Retrieve a child object by URI
        
        /// Provides iterator functionality for SBOL properties that contain multiple objects
        class iterator : public std::vector<Identified*>::iterator
        {
        public:
            
            iterator(typename std::vector<Identified*>::iterator i_object = std::vector<Identified*>::iterator()) : std::vector<Identified*>::iterator(i_object)
            {
            }
            
            Identified& operator*()
            {
                return (Identified&) *std::vector<Identified*>::iterator::operator *();
            }
        };
        
        iterator begin()
        {
            return iterator(records.begin());
        };
        
        iterator end()
        {
            return iterator(records.end());
        };
        
    protected:
        std::vector < sbol::Identified* > records;

        SearchResponse() :
            records()
        {
        };
        
        ~SearchResponse()
        {
        };
    };
    
//    class SBOL_DECLSPEC SearchQuery : public Json::Value
//    {
//    private:
//        std::string resource;
//        std::string key;
//        
//    public:
//        
//        /// Construct an interface to an instance of SynBioHub or other parts repository
//        /// @param The URL of the online repository
//        SearchQuery(std::map<std::string, std::string> criteria ) :
//        Json::Value()
//        {
//            //        std::vector<std::string> keys;
//            //        for(auto const& key_value_pair: criteria)
//            //            keys.push_back(key_value_pair.first);
//            //        // Check that Json request contains the expected key-value pairs
//            //        std::vector<std::string> valid_parameters = {"objectType", "sbolTag", "collection", "dcterms", "namespace/tag"};
//            //        for (auto const& p : valid_parameters)
//            //        {
//            //            if ( std::find(valid_parameters.begin(), valid_parameters.end(), p) == valid_parameters.end() )
//            //            {
//            //                throw sbol::SBOLError(sbol::SBOL_ERROR_INVALID_ARGUMENT, "Invalid search parameter " + p + ". Search parameters must be one or more of objectType, sbolTag, collection, dcterms, or namespace/tag");
//            //                (*this)[p] = criteria[p];
//            //            }
//            //        }
//        }
//    };
    
//    class SBOL_DECLSPEC SearchResponse : public Json::Value
//    {
//    private:
//        std::string resource;
//        std::string key;
//        
//    public:
//        
//        /// Construct an interface to an instance of SynBioHub or other parts repository
//        /// @param The URL of the online repository
//        SearchResponse() :
//        Json::Value()
//        {
//            //
//            //        std::vector<std::string> keys;
//            //        for(auto const& key_value_pair: criteria)
//            //            keys.push_back(key_value_pair.first);
//            //        // Check that Json request contains the expected key-value pairs
//            //        std::vector<std::string> valid_parameters = {"objectType", "sbolTag", "collection", "dcterms", "namespace/tag"};
//            //        for (auto const& p : valid_parameters)
//            //        {
//            //            if ( std::find(valid_parameters.begin(), valid_parameters.end(), p) == valid_parameters.end() )
//            //            {
//            //                throw sbol::SBOLError(sbol::SBOL_ERROR_INVALID_ARGUMENT, "Invalid search parameter " + p + ". Search parameters must be one or more of objectType, sbolTag, collection, dcterms, or namespace/tag");
//            //                (*this)[p] = criteria[p];
//            //            }
//            //        }
//        }
//    };  // SearchResponse
    
    /// A class which provides an API front-end for online bioparts repositories
    class SBOL_DECLSPEC PartShop
    {
    private:
        std::string resource;
        std::string key;
        
    public:
        /// Return the count of objects contained in a PartShop
        /// @tparam SBOLClass The type of SBOL object, usually a ComponentDefinition
        template < class SBOLClass > int count();
        
        /// Retrieve an object from an online resource
        /// @param uri The identity of the SBOL object you want to retrieve
        /// @param doc A document to add the data to
        void pull(std::string uri, Document& doc);

        /// Returns all Collections that are not members of any other Collections
        /// @param doc A Document to add the Collections to
        std::string searchRootCollections();
        
        /// Returns all Collections that are members of the Collection specified by its URI
        /// @param uri The URI of a Collection of Collections
        /// @param doc A Document to add the subcollections to
        std::string searchSubCollections(std::string uri);

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
        
        std::string search(std::string search_text, std::string object_type, std::string property_uri, int offset = 0, int limit = 25);
        
        std::string search(std::string search_text, std::string object_type = SBOL_COMPONENT_DEFINITION, int offset = 0, int limit = 25);

        std::string search(SearchQuery& q);

#else

        /// An EXACT search. Scan the parts repository for objects that exactly match the specified criteria. In most uses of this function, LibSBOL's built-in RDF type constants (see @ref constants.h) will come in handy. For instance, searching for all SBOL_COMPONENT_DEFINITION of type BIOPAX_DNA. (These constants follow a fairly systematic and consistent naming scheme (see @ref constants.h). The number of records returned in the search is specified by offset and limit parameters.
        /// @param search_text This may be a literal text value or it may be a URI.
        /// @param object_type The RDF type of an SBOL object. See @ref constants.h. For example, SBOL_COMPONENT_DEFINITION
        /// @param property_uri The RDF type of an SBOL property. Specifies which field of an SBOL object to search. For example, SBOL_ROLES. Refer to @ref constants.h
        /// @param offset The index of the first record to return. This parameter is indexed starting from zero.
        /// @param limit The total count number of records to return
        /// @return Metadata formatted as a string encoding JSON.
        std::vector<std::map<std::string, std::string>> search(std::string search_text, std::string object_type, std::string property_uri, int offset = 0, int limit = 25);
        
        /// A GENERAL search. Search name, description, and displayId properties for a match to the search text, including matches to substrings of the property value. The type of object to search for can be further restricted by use of the second parameter, though this is set to SBOL_COMPONENT_DEFINITION by default. See @ref constants.h for more of libSBOL's built-in RDF type constants. These constants follow a fairly predictable and consistent naming scheme. The number of records returned in the search is specified by offset and limit parameters.
        /// @param search_text A snippet of text to search for in a property's value.
        /// @param object_type The RDF type of an SBOL object. See @ref constants.h. For example, SBOL_COMPONENT_DEFINITION by default.
        /// @param offset The index of the first record to return. This parameter is indexed starting from zero.
        /// @param limit The total count number of records to return
        /// @return Metadata formatted as a string encoding JSON.
        std::vector<std::map<std::string, std::string>> search(std::string search_text, std::string object_type = SBOL_COMPONENT_DEFINITION, int offset = 0, int limit = 25);
        
        /// Perform an ADVANCED search using a SearchQuery object.
        /// @param search_query A map of string key-value pairs. Keys are objectType, sbolTag, collection, dcterms:tag, namespace/tag, offset, limit.
        /// @return Search metadata A vector of maps with key-value pairs.
        SearchResponse& search(SearchQuery& q);
        
#endif
        
        /// Returns the number of search records for an EXACT search matching the given criteria.
        /// @return An integer count.
        int searchCount(std::string search_text, std::string object_type, std::string property_uri);
        
        /// Returns the number of search records for a general search matching the given criteria.
        /// @return An integer count.
        int searchCount(std::string search_text, std::string object_type = SBOL_COMPONENT_DEFINITION);
        
        /// Returns the number of search records matching the given criteria for an ADVANCED search
        /// @param search_query A map of string key-value pairs. See SearchQuery for required and optional criteria.
        /// @return An integer count.
        int searchCount(SearchQuery& q);
        
        /// Submit a Document to SynBioHub
        /// @param doc The Document to submit
        /// @param overwrite An integer code: 0(default) - do not overwrite, 1 - overwrite, 2 - merge
        std::string submit(Document& doc, int overwrite = 0);
        
        /// In order to submit to a PartShop, you must login first. Register on [SynBioHub](http://synbiohub.org) to obtain account credentials.
        /// @param email The email associated with the user's SynBioHub account
        /// @param password The user's password
        void login(std::string email, std::string password);
        
        /// Returns the network address of the PartShop
        /// @return The URL of the online repository
        std::string getURL();
        
        /// Construct an interface to an instance of SynBioHub or other parts repository
        /// @param The URL of the online repository
        PartShop(std::string url) :
        resource(url)
        {
        };
    };
    
//    /// Returns a Document including all objects referenced from this object
//    template <> sbol::Document& sbol::PartShop::pull<sbol::Document>(std::string uri);

    template < class SBOLClass > int PartShop::count()
    {
        // Form get request
        std::string get_request;
        SBOLClass dummy = SBOLClass();
        std::string sbol_class = parseClassName(dummy.getTypeURI());
        get_request = resource + "/" + sbol_class + "/count";
        
        /* Perform HTTP request */
        std::string response;
        CURL *curl;
        CURLcode res;
        
        /* In windows, this will init the winsock stuff */
        curl_global_init(CURL_GLOBAL_ALL);
        
        struct curl_slist *headers = NULL;
        //    headers = curl_slist_append(headers, "Accept: application/json");
        //    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        //    headers = curl_slist_append(headers, "charsets: utf-8");
        
        /* get a curl handle */
        curl = curl_easy_init();
        if(curl) {
            /* First set the URL that is about to receive our POST. This URL can
             just as well be a https:// URL if that is what should receive the
             data. */
            //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
            curl_easy_setopt(curl, CURLOPT_URL, get_request.c_str());
            //        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            
            /* Now specify the callback to read the response into string */
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            
            /* Perform the request, res will get the return code */
            res = curl_easy_perform(curl);
            /* Check for errors */
            if(res != CURLE_OK)
                throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to count objects failed with " + std::string(curl_easy_strerror(res)));
            
            /* always cleanup */
            curl_easy_cleanup(curl);
        }
        curl_slist_free_all(headers);
        curl_global_cleanup();
        
        return stoi(response);
    };
    
}  // sbol namepsace
#endif