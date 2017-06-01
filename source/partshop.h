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
        
        List<TextProperty> operator[] (std::string uri)
        {
            // If the URI has a namespace, treat the function argument as a full URI
            if (parseNamespace(uri).compare("") == 0)
                return List<TextProperty>(SBOL_URI "#" + uri, this);
            else
                return List<TextProperty>(uri, this);
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

    class SBOL_DECLSPEC SearchResponse_ : public TopLevel
    {
        List<OwnedObject<Identified>> metadata;
        
        SearchResponse_() :
            metadata(SBOL_URI "#SearchResponse", this )
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
    
    class SBOL_DECLSPEC SearchResponse : public Json::Value
    {
    private:
        std::string resource;
        std::string key;
        
    public:
        
        /// Construct an interface to an instance of SynBioHub or other parts repository
        /// @param The URL of the online repository
        SearchResponse() :
        Json::Value()
        {
            //
            //        std::vector<std::string> keys;
            //        for(auto const& key_value_pair: criteria)
            //            keys.push_back(key_value_pair.first);
            //        // Check that Json request contains the expected key-value pairs
            //        std::vector<std::string> valid_parameters = {"objectType", "sbolTag", "collection", "dcterms", "namespace/tag"};
            //        for (auto const& p : valid_parameters)
            //        {
            //            if ( std::find(valid_parameters.begin(), valid_parameters.end(), p) == valid_parameters.end() )
            //            {
            //                throw sbol::SBOLError(sbol::SBOL_ERROR_INVALID_ARGUMENT, "Invalid search parameter " + p + ". Search parameters must be one or more of objectType, sbolTag, collection, dcterms, or namespace/tag");
            //                (*this)[p] = criteria[p];
            //            }
            //        }
        }
    };  // SearchResponse
    
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
        /// @tparam SBOLClass The type of SBOL object, usually a ComponentDefinition
        /// @return The object identified by the specified uri
        template < class SBOLClass > SBOLClass& pull(std::string uri);

        /// Returns all Collections that are not members of any other Collections
        /// @return A Document containing all the root Collections
        Document& pullRootCollections();
        
        /// Scan the parts repository for objects that exactly match the specified criteria. In most uses of this function, LibSBOL's built-in RDF type constants (see @file constants.h) will come in handy. For instance, searching for all SBOL_COMPONENT_DEFINITION of type BIOPAX_DNA. These constants follow a fairly systematic and consistent naming scheme. The number of records returned in the search is specified by offset and limit parameters.
        /// @param search_text This may be a literal text value or it may be a URI. See @file constants.h for useful ontology terms
        /// @param object_type The RDF type of an SBOL object. See @file constants.h. For example, SBOL_COMPONENT_DEFINITION
        /// @param property_uri The RDF type of an SBOL property. Specifies which field of an SBOL object to search. For example, SBOL_ROLES. Refer to @file constants.h
        /// @param offset The index of the first record to return. This parameter is indexed starting from zero.
        /// @param limit The total count number of records to return
        /// @return Metadata formatted as a string encoding JSON.
        std::string search(std::string search_text, std::string object_type, std::string property_uri, int offset = 0, int limit = 25);

        /// Search name, description, and displayId properties for a match to the search text, including matches to substrings of the property value. The type of object to search for can be further restricted by use of the second parameter, though this is set to SBOL_COMPONENT_DEFINITION by default. See @file constants.h for more of libSBOL's built-in RDF type constants. These constants follow a fairly predictable and consistent naming scheme. The number of records returned in the search is specified by offset and limit parameters.
        /// @param search_text A snippet of text to search for in a property's value.
        /// @param object_type The RDF type of an SBOL object. See @file constants.h. For example, SBOL_COMPONENT_DEFINITION by default.
        /// @param offset The index of the first record to return. This parameter is indexed starting from zero.
        /// @param limit The total count number of records to return
        /// @return Metadata formatted as a string encoding JSON.
        std::string search(std::string search_text, std::string object_type = SBOL_COMPONENT_DEFINITION, int offset = 0, int limit = 25);
        
        /// Search name, description, and displayId properties for a match to the search text, including matches to substrings of the property value. The type of object to search for can be further restricted by use of the second parameter, though this is set to SBOL_COMPONENT_DEFINITION by default. See @file constants.h for more of libSBOL's built-in RDF type constants. These constants follow a fairly predictable and consistent naming scheme. The number of records returned in the search is specified by offset and limit parameters.
        /// @param search_query A map of string key-value pairs. Keys are objectType, sbolTag, collection, dcterms:tag, namespace/tag, offset, limit.
        /// @return Search metadata A vector of maps with key-value pairs.
        std::vector<std::map<std::string, std::string>> search(SearchQuery& q);
        
        /// Submit a Document to SynBioHub
        /// @param doc The Document to submit
        /// @param overwrite An integer code: 0(default) - do not overwrite, 1 - overwrite, 2 - merge
        std::string submit(Document& doc, int overwrite = 0);
        
        /// In order to submit to a PartShop, you must login first. Register on [SynBioHub](http://synbiohub.org) to obtain account credentials.
        /// @param email The email associated with the user's SynBioHub account
        /// @param password The user's password
        void login(std::string email, std::string password);
        
        /// Construct an interface to an instance of SynBioHub or other parts repository
        /// @param The URL of the online repository
        PartShop(std::string url) :
        resource(url)
        {
        };
    };
    
    template < class SBOLClass > SBOLClass& PartShop::pull(std::string uri)
    {
        std::string get_request = uri + "/sbol";
        
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
            
            /* Now specify the POST data */
            //        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
            
            /* Now specify the callback to read the response into string */
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            
            /* Perform the request, res will get the return code */
            res = curl_easy_perform(curl);
            /* Check for errors */
            if(res != CURLE_OK)
                throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + std::string(curl_easy_strerror(res)));
            
            /* always cleanup */
            curl_easy_cleanup(curl);
        }
        curl_slist_free_all(headers);
        curl_global_cleanup();
        
        Document doc = Document();
        doc.readString(response);
        SBOLClass& obj = doc.get<SBOLClass>(uri);
        obj.doc = NULL;
        return obj;
    };
    
    /// Returns a Document including all objects referenced from this object
    template <> sbol::Document& sbol::PartShop::pull<sbol::Document>(std::string uri);

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