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

namespace sbol
{
    /// A class which provides an API front-end for online bioparts repositories
    class SBOL_DECLSPEC PartShop
    {
    private:
        std::string resource;
        
    public:
        /// Retrieve an object from an online resource
        /// @param uri The identity of the SBOL object you want to retrieve
        /// @tparam SBOLClass The type of SBOL object, usually a ComponentDefinition
        template < class SBOLClass > SBOLClass& pull(std::string uri);

        /// Retrieve all the objects referenced in a Collection
        /// @param uri The identity of the Collection you want to retrieve
        /// @tparam SBOLClass The type of SBOL objects in the Collection, for example, a ComponentDefinition
        template <class SBOLClass > std::vector < SBOLClass* > pull(sbol::Collection& collection);

        /// Retrieve an object from an online resource
        /// @param uri The identity of the SBOL object you want to retrieve
        std::vector < ComponentDefinition* > pullComponentDefinitionFromCollection(Collection& collection);
        
        /// Scan the parts repository for objects that exactly match the specified criteria. In most uses of this function, LibSBOL's built-in RDF type constants (see @file constants.h) will come in handy, for instance, if searching for ComponentDefinitions of type BIOPAX_DNA. These constants follow a fairly systematic and consistent naming scheme. The number of records returned in the search is specified by offset and limit parameters.
        /// @param search_text This may be a literal text value or it may be a URI. See @file constants.h for useful ontology terms
        /// @param object_type The RDF type of an SBOL object. See @file constants.h. For example, SBOL_COMPONENT_DEFINITION
        /// @param property_uri The RDF type of an SBOL property. Specifies which field of an SBOL object to search. For example, SBOL_ROLES. Refer to @file constants.h
        /// @param offset The index of the first record to return. This parameter is indexed starting from zero.
        /// @param limit The total count number of records to return
        /// @return Metadata formatted as a string encoding JSON.
        std::string search(std::string search_text, std::string object_type, std::string property_uri, int offset = 0, int limit = 25);

        
        std::string search(std::string search_text, std::string object_type = SBOL_COMPONENT_DEFINITION, int offset = 0, int limit = 25);
        
//        std::string search(std::string search_query, std::map < std::string, std::string > query_options = {});
        
        std::string login(std::string email, std::string password);
        
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
    
    template <class SBOLClass > std::vector < SBOLClass* > PartShop::pull(sbol::Collection& collection)
    {
        std::vector < SBOLClass* > objects;
        for (auto & ref : collection.members)
        {
            SBOLClass& obj = pull < SBOLClass >(ref);
            objects.push_back(&obj);
        }
        return objects;
    };
    
}

#endif