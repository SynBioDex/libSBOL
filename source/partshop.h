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

#include "document.h"

#include <string>
#include <map>
#include <vector>
#include <curl/curl.h>
#include <iostream>
#include <algorithm>
#include <json/json.h>

namespace sbol
{
    /// A SearchQuery object is used to configure advanced searches for bioparts in a PartShop. Advanced searches are useful for matching values across multiple fields, or to specify multiple values in a single field.
    class SBOL_DECLSPEC SearchQuery : public TopLevel
    {
    public:
        /// SearchQuery constructor
        /// @param search_target The type of SBOL object to search for, indicated using a URI. Set to SBOL_COMPONENT_DEFINITION by default.
        SearchQuery(rdf_type search_target = SBOL_COMPONENT_DEFINITION, int offset = 0, int limit = 25) :
            TopLevel(SBOL_URI "#SearchQuery", "example"),
            objectType(this, SBOL_URI "#objectType", '0', '1', ValidationRules({}), search_target),
            offset(this, SBOL_URI "#offset", '1', '1', ValidationRules({}), offset),
            limit(this, SBOL_URI "#limit", '1', '1', ValidationRules({}), limit)
        {
            // The following properties are set to empty string because they are treated like search criteria
            displayId.set("");
            persistentIdentity.set("");
            version.set("");
        };

        /// Set this property to indicate the type of SBOL object to search for. Set to SBOL_COMPONENT_DEFINITION by default
        URIProperty objectType;

        /// Set this property to specify the total number of records to retrieve from a search request. By default 25 records are retrieved.
        IntProperty limit;

        /// When the number of search hits exceeds the limit, the offset property can be used to retrieve more records.
        IntProperty offset;
        
        /// Used to set search criteria for a search request.
        /// @param uri A URI indicating the SBOL property to search for, eg, SBOL_ROLES will search the roles property of a ComponentDefinition
        TextProperty operator[] (std::string uri)
        {
            // If the URI has a namespace, treat the function argument as a full URI
            if (parseNamespace(uri).compare("") == 0)
                return TextProperty(this, SBOL_URI "#" + uri, '0', '1', ValidationRules({}));
            else
                return TextProperty(this, uri, '0', '1', ValidationRules({}));
        };  ///< Retrieve a child object by URI
        
        std::string __str__();
        
        ~SearchQuery() {};

    };

    /// A SearchResponse is a container of search records returned by a search request
    class SBOL_DECLSPEC SearchResponse : public TopLevel
    {
    public:
        std::vector < sbol::Identified* > records;

        /// Adds more search records to an existing SearchResponse
        /// @param response A SearchResponse object
        void extend(SearchResponse& response);
        
        SearchResponse() :
            records()
        {
        };
        
        ~SearchResponse()
        {
            for (auto & record : records)
            {
                record->close();
            }
            records.clear();
        };
        
        /// Returns the number of records contained in a search response
        int size()
        {
            return (int)records.size();
        }
        
        /// Returns an individual record from a SearchResponse
        /// @param i The integer index of the record to return
        Identified& operator[] (int i)
        {
            // If the URI has a namespace, treat the function argument as a full URI
            if (i < records.size())
                return *records[i];
            else
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Index out of range");
        };
        
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
        
        std::vector<Identified*>::iterator python_iter;
        
        std::string __str__();
    };
    
    
    /// A class which provides an API front-end for online bioparts repositories
    class SBOL_DECLSPEC PartShop
    {
    private:
        std::string resource;
        std::string spoofed_resource;
        std::string key;
        std::string user;

    public:
        /// Construct an interface to an instance of SynBioHub or other parts repository
        /// @param The URL of the online repository
        PartShop(std::string url, std::string spoofed_url = "") :
            resource(url),
            key(""),
            spoofed_resource(spoofed_url)
            {
                if (url.size() && url.back() == '/')
                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "PartShop initialization failed. The resource URL should not contain a terminal backslash");
                if (spoofed_url.size() && spoofed_url.back() == '/')
                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "PartShop initialization failed. The spoofed URL should not contain a terminal backslash");
            };
        
        /// Return the count of objects contained in a PartShop
        /// @tparam SBOLClass The type of SBOL object, usually a ComponentDefinition
        template < class SBOLClass > int count();
        
        /// Issue a SPARQL query
        std::string sparqlQuery(std::string query);

        /// Specify the URL of a resource that is simulated or spoofed by this PartShop
        void spoof(std::string spoofed_url);

        void remove(std::string uri);
        
        /// Retrieve an object from an online resource
        /// @param uri The identity of the SBOL object you want to retrieve
        /// @param doc A document to add the data to
        void pull(std::string uri, Document& doc, bool recursive = true);

        /// Retrieve an object from an online resource
        /// @param uris A vector of URIs for multiple SBOL objects you want to retrieve
        /// @param doc A document to add the data to
        void pull(std::vector<std::string> uris, Document& doc, bool recursive = true );

        template < class SBOLClass > void pull(std::string uri, Document& doc, bool recursive = true);
        
        /// Returns all Collections that are not members of any other Collections
        /// @param doc A Document to add the Collections to
        std::string searchRootCollections();
        
        /// Returns all Collections that are members of the Collection specified by its URI
        /// @param uri The URI of a Collection of Collections
        /// @param doc A Document to add the subcollections to
        std::string searchSubCollections(std::string uri);

        /// An EXACT search. Scan the parts repository for objects that exactly match the specified criteria. In most uses of this function, LibSBOL's built-in RDF type constants (see @ref constants.h) will come in handy. For instance, searching for all SBOL_COMPONENT_DEFINITION of type BIOPAX_DNA. (These constants follow a fairly systematic and consistent naming scheme (see @ref constants.h). The number of records returned in the search is specified by offset and limit parameters.
        /// @param search_text This may be a literal text value or it may be a URI.
        /// @param object_type The RDF type of an SBOL object. See @ref constants.h. For example, SBOL_COMPONENT_DEFINITION
        /// @param property_uri The RDF type of an SBOL property. Specifies which field of an SBOL object to search. For example, SBOL_ROLES. Refer to @ref constants.h
        /// @param offset The index of the first record to return. This parameter is indexed starting from zero.
        /// @param limit The total count number of records to return
        /// @return Metadata formatted as a string encoding JSON.
        SearchResponse& search(std::string search_text, std::string object_type, std::string property_uri, int offset = 0, int limit = 25);
        
        /// A GENERAL search. Search name, description, and displayId properties for a match to the search text, including matches to substrings of the property value. The type of object to search for can be further restricted by use of the second parameter, though this is set to SBOL_COMPONENT_DEFINITION by default. See @ref constants.h for more of libSBOL's built-in RDF type constants. These constants follow a fairly predictable and consistent naming scheme. The number of records returned in the search is specified by offset and limit parameters.
        /// @param search_text A snippet of text to search for in a property's value.
        /// @param object_type The RDF type of an SBOL object. See @ref constants.h. For example, SBOL_COMPONENT_DEFINITION by default.
        /// @param offset The index of the first record to return. This parameter is indexed starting from zero.
        /// @param limit The total count number of records to return
        /// @return Metadata formatted as a string encoding JSON.
        SearchResponse& search(std::string search_text, std::string object_type = SBOL_COMPONENT_DEFINITION, int offset = 0, int limit = 25);
        
        /// Perform an ADVANCED search using a SearchQuery object.
        /// @param search_query A map of string key-value pairs. Keys are objectType, sbolTag, collection, dcterms:tag, namespace/tag, offset, limit.
        /// @return Search metadata A vector of maps with key-value pairs.
        SearchResponse& search(SearchQuery& q);
        
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
        
        /// Submit an SBOL Document to SynBioHub
        /// @param doc The Document to submit
        /// @param collection The URI of an SBOL Collection to which the Document contents will be uploaded
        /// @param overwrite An integer code: 0(default) - do not overwrite, 1 - overwrite, 2 - merge
        std::string submit(Document& doc, std::string collection = "", int overwrite = 0);

//        /// Submit a file, such as COMBINE archives or SBML to a SynBioHub Collection
//        /// @param filename The file to submit
//        /// @param collection The URI of an SBOL Collection to which the file will be submitted
//        /// @param overwrite An integer code: 0(default) - do not overwrite, 1 - overwrite, 2 - merge
//        std::string submit(std::string filename, std::string collection, int overwrite = 0);
        
        /// In order to submit to a PartShop, you must login first. Register on [SynBioHub](http://synbiohub.org) to obtain account credentials.
        /// @param email The email associated with the user's SynBioHub account
        /// @param password The user's password
        void login(std::string user_id, std::string password = "");
        
        /// Returns the network address of the PartShop
        /// @return The URL of the online repository
        std::string getURL();

        std::string getKey();        

        std::string getUser();        

        std::string getSpoofedURL();        

        /// Upload and attach a file to a TopLevel object in a PartShop.
        /// @param top_level_uri The identity of the object to which the file will be attached
        /// @param file_name A path to the file attachment
        void attachFile(std::string topleveluri, std::string filename);

        /// Download a file attached to a TopLevel object in an online repository.
        /// @param attachment_uri The full URI of the attached object
        /// @param path The target path to which the file will be downloaded
        void downloadAttachment(std::string attachment_uri, std::string path = ".");
      
        void addSynBioHubAnnotations(Document& doc); 

        bool exists(std::string uri); 
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
    
    template<>
    void PartShop::pull<ComponentDefinition>(std::string uri, Document& doc, bool recursive);

    template < class SBOLClass > void PartShop::pull(std::string uri, Document& doc, bool recursive)
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
                throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to access PartShop failed with " + std::string(curl_easy_strerror(res)));
            
            /* always cleanup */
            curl_easy_cleanup(curl);
        }
        curl_slist_free_all(headers);
        curl_global_cleanup();
        
        doc.readString(response);

    };

}  // sbol namepsace
#endif
