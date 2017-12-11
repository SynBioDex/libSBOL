#include "partshop.h"
#include <algorithm>

using namespace std;
using namespace sbol;

// A utility function to replace a substring with a new substring
void replace(string& text, string target, string replacement)
{
    size_t i_replace = 0;
    while (i_replace != std::string::npos)
    {
        i_replace = text.find(target);
        if (i_replace != std::string::npos)
            text.replace(i_replace, target.length(), replacement);
    }
};

// A utility function for encoding text into UTF8 for http requests
void encode_http(string& text)
{
    string UTF8_AMPERSAND = "%26";
    string UTF8_EQUALS = "%3D";
    string UTF8_LESS_THAN = "%3C";
    string UTF8_GREATER_THAN = "%3E";
    string UTF8_COLON = "%3A";
    string UTF8_HASH = "%23";
    string UTF8_APOSTROPHE = "%27";
    string UTF8_SPACE = "%20";
    string UTF8_SLASH = "%2F";
    
    replace(text, "&", UTF8_AMPERSAND);
    replace(text, "=", UTF8_EQUALS);
    replace(text, "<", UTF8_LESS_THAN);
    replace(text, ">", UTF8_GREATER_THAN);
    replace(text, ":", UTF8_COLON);
    replace(text, "#", UTF8_HASH);
    replace(text, "'", UTF8_APOSTROPHE);
    replace(text, " ", UTF8_SPACE);
    replace(text, "/", UTF8_SLASH);
};

// Advanced search
SearchResponse& sbol::PartShop::search(SearchQuery& q)
{
    string url = resource;
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    //    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    
    /* Specify the GET parameters */
    if(curl)
    {
        string parameters;
        // Specify the type of SBOL object to search for
        if (q["objectType"].size() == 1)
            parameters = "objectType=" + parseClassName(q["objectType"].get()) + "&";
        else
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "SearchQuery is invalid because it does not have an objectType specified");
        
        // Get the search criteria, while ignoring special search parameters like objectType, offset, and limit
        vector<string> search_criteria = q.getProperties();
        auto i_ignore = std::find(std::begin(search_criteria), std::end(search_criteria), SBOL_IDENTITY);
        search_criteria.erase(i_ignore);
        i_ignore = std::find(std::begin(search_criteria), std::end(search_criteria), SBOL_URI "#objectType");
        search_criteria.erase(i_ignore);
        i_ignore = std::find(std::begin(search_criteria), std::end(search_criteria), SBOL_URI "#offset");
        search_criteria.erase(i_ignore);
        i_ignore = std::find(std::begin(search_criteria), std::end(search_criteria), SBOL_URI "#limit");
        search_criteria.erase(i_ignore);
        
        // Form GET request from the search criteria
        for (auto & property_uri : search_criteria)
            for (auto & property_val : q.getPropertyValues(property_uri))
            {
                if (property_val.length() > 0)
                {
                    parameters += "<" + property_uri + ">=";
                    if (property_val.find("http") == 0)
                        parameters += "<" + property_val + ">&"; // encode property value as a URI
                    else
                        parameters += "'" + property_val + "'&"; // encode property value as a literal
                }
            }
        
        // Specify index of the first record to retrieve
        if (q["offset"].size() == 1)
            parameters += "/?offset=" + q["offset"].get();
        else
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid offset parameter specified");
        
        // Specify how many records to retrieve
        if (q["limit"].size() == 1)
            parameters += "&limit=" + q["limit"].get();
        else
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid limit parameter specified");
        
        encode_http(parameters);
        parameters = url + "/remoteSearch/" + parameters;
        
        /* First set the URL that is about to receive our GET. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, parameters.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    SearchResponse& search_response = * new SearchResponse();
    Json::Value json_response;
    Json::Reader reader;
    bool parsed = reader.parse( response, json_response );     //parse process
    if ( parsed )
    {
        for( Json::ValueIterator i_entry = json_response.begin() ; i_entry != json_response.end(); i_entry++ )
        {
            Json::Value json_entry = *i_entry;
            Identified* record = new Identified(SBOL_IDENTIFIED, "dummy", "0");
            record->identity.set( json_entry.get("uri", response ).asString() );
            record->displayId.set( json_entry.get("displayId", response ).asString() );
            record->name.set( json_entry.get("name", response ).asString() );
            record->description.set( json_entry.get("description", response ).asString() );
            record->version.set( json_entry.get("version", response ).asString() );
            search_response.records.push_back(record);
        }
    }
    else
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search failed with error message" + response);
    return search_response;
};

// Exact search
SearchResponse& sbol::PartShop::search(std::string search_text, sbol_type object_type, std::string property_uri, int offset, int limit)
{
    string url = resource;
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    //    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* Specify the GET data */
        // Specify the type of SBOL object to search for
        string parameters = "objectType=" + parseClassName(object_type) + "&";
        
        //        // Specify which property of the SBOL object to look in for the search text
        //        parameters += parsePropertyName(property_uri) + UTF8_EQUALS;
        parameters += "<" + property_uri + ">=";
        
        if (search_text.find("http") == 0)
            // Encode search text as a URL
            parameters += "<" + search_text + ">&";
        else
            // Encode as a literal
            parameters += "'" + search_text + "'&";
        
        encode_http(parameters);
        
        // Specify how many records to retrieve
        parameters += "/?offset=" + to_string(offset) + "&limit=" + to_string(limit);
        
        parameters = url + "/remoteSearch/" + parameters;
        
        /* First set the URL that is about to receive our GET. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, parameters.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    SearchResponse& search_response = * new SearchResponse();
    Json::Value json_response;
    Json::Reader reader;
    bool parsed = reader.parse( response, json_response );     //parse process
    if ( parsed )
    {
        for( Json::ValueIterator i_entry = json_response.begin() ; i_entry != json_response.end(); i_entry++ )
        {
            Json::Value json_entry = *i_entry;
            Identified* record = new Identified(SBOL_IDENTIFIED, "dummy", "0");
            record->identity.set( json_entry.get("uri", response ).asString() );
            record->displayId.set( json_entry.get("displayId", response ).asString() );
            record->name.set( json_entry.get("name", response ).asString() );
            record->description.set( json_entry.get("description", response ).asString() );
            record->version.set( json_entry.get("version", response ).asString() );
            search_response.records.push_back(record);
        }
    }
    else
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search failed with error message" + response);
    return search_response;
};

// General search
SearchResponse& sbol::PartShop::search(std::string search_text, sbol_type object_type, int offset, int limit)
{
    string url = resource;
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    //    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* Specify the GET data */
        // Specify the type of SBOL object to search for
        string parameters = "objectType=" + parseClassName(object_type) + "&";
        
        // Specify partial search text. Specify how many records to retrieve
        parameters = parameters + search_text;
        
        encode_http(search_text);
        
        // Specify how many records to retrieve
        parameters += "/?offset=" + to_string(offset) + "&limit=" + to_string(limit);
        
        parameters = url + "/remoteSearch/" + parameters;
        
        /* First set the URL that is about to receive our GET. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, parameters.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    SearchResponse& search_response = * new SearchResponse();
    Json::Value json_response;
    Json::Reader reader;
    bool parsed = reader.parse( response, json_response );     //parse process
    if ( parsed )
    {
        for( Json::ValueIterator i_entry = json_response.begin() ; i_entry != json_response.end(); i_entry++ )
        {
            Json::Value json_entry = *i_entry;
            Identified* record = new Identified(SBOL_IDENTIFIED, "dummy", "0");
            record->identity.set( json_entry.get("uri", response ).asString() );
            record->displayId.set( json_entry.get("displayId", response ).asString() );
            record->name.set( json_entry.get("name", response ).asString() );
            record->description.set( json_entry.get("description", response ).asString() );
            record->version.set( json_entry.get("version", response ).asString() );
            search_response.records.push_back(record);
        }
    }
    else
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search failed with error message" + response);
    return search_response;
};


int sbol::PartShop::searchCount(SearchQuery& q)
{
    string url = resource;
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    //    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    
    /* Specify the GET parameters */
    if(curl)
    {
        string parameters;
        // Specify the type of SBOL object to search for
        if (q["objectType"].size() == 1)
            parameters = "objectType=" + parseClassName(q["objectType"].get()) + "&";
        else
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "SearchQuery is invalid because it does not have an objectType specified");
        
        // Get the search criteria, while ignoring special search parameters like objectType, offset, and limit
        vector<string> search_criteria = q.getProperties();
        auto i_ignore = std::find(std::begin(search_criteria), std::end(search_criteria), SBOL_IDENTITY);
        search_criteria.erase(i_ignore);
        i_ignore = std::find(std::begin(search_criteria), std::end(search_criteria), SBOL_URI "#objectType");
        search_criteria.erase(i_ignore);
        i_ignore = std::find(std::begin(search_criteria), std::end(search_criteria), SBOL_URI "#offset");
        search_criteria.erase(i_ignore);
        i_ignore = std::find(std::begin(search_criteria), std::end(search_criteria), SBOL_URI "#limit");
        search_criteria.erase(i_ignore);
        
        // Form GET request from the search criteria
        for (auto & property_uri : search_criteria)
            for (auto & property_val : q.getPropertyValues(property_uri))
            {
                if (property_val.length() > 0)
                {
                    parameters += "<" + property_uri + ">=";
                    if (property_val.find("http") == 0)
                        parameters += "<" + property_val + ">&"; // encode property value as a URI
                    else
                        parameters += "'" + property_val + "'&"; // encode property value as a literal
                }
            }
        
        encode_http(parameters);
        parameters = url + "/searchCount/" + parameters;
        
        /* First set the URL that is about to receive our GET. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, parameters.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    int count;
    try
    {
        count = stoi(response);
    }
    catch (...)
    {
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search failed with error message" + response);
    }
    return count;
};

int sbol::PartShop::searchCount(std::string search_text, sbol_type object_type, std::string property_uri)
{
    string url = resource;
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    //    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* Specify the GET data */
        // Specify the type of SBOL object to search for
        string parameters = "objectType=" + parseClassName(object_type) + "&";
        
        //        // Specify which property of the SBOL object to look in for the search text
        //        parameters += parsePropertyName(property_uri) + UTF8_EQUALS;
        parameters += "<" + property_uri + ">=";
        
        if (search_text.find("http") == 0)
            // Encode search text as a URL
            parameters += "<" + search_text + ">&";
        else
            // Encode as a literal
            parameters += "'" + search_text + "'&";
        
        encode_http(parameters);
        
        parameters = url + "/remoteSearch/" + parameters;
        
        /* First set the URL that is about to receive our GET. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, parameters.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();

    int count;
    try
    {
        count = stoi(response);
    }
    catch (...)
    {
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search failed with error message" + response);
    }
    return count;
};

int sbol::PartShop::searchCount(std::string search_text, sbol_type object_type)
{
    string url = resource;
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    //    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* Specify the GET data */
        // Specify the type of SBOL object to search for
        string parameters = "objectType=" + parseClassName(object_type) + "&";
        
        // Specify partial search text. Specify how many records to retrieve
        parameters = parameters + search_text;
        
        encode_http(search_text);
        
        parameters = url + "/searchCount/" + parameters;
        
        /* First set the URL that is about to receive our GET. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, parameters.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    int count;
    try
    {
        count = stoi(response);
    }
    catch (...)
    {
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search failed with error message" + response);
    }
    return count;
};


void sbol::PartShop::login(std::string email, std::string password)
{
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    //    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, "https://synbiohub.org/remoteLogin");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the POST data */
        string parameters = "email=" + email + "&" + "password=" + password;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    if (response == "Your password was not recognized.")
        std::cout << response << std::endl;
    else
        key = response;
};

std::string sbol::PartShop::submit(Document& doc, std::string collection, int overwrite)
{
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
//        headers = curl_slist_append(headers, "Accept: application/json");
//    headers = curl_slist_append(headers, "Content-Type:  multipart/form-data");
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_URL, "https://synbiohub.org/remoteSubmit");
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        /* Now specify the POST data */
        struct curl_httppost* post = NULL;
        struct curl_httppost* last = NULL;
        
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "id",
                     CURLFORM_COPYCONTENTS, doc.displayId.get().c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "version",
                     CURLFORM_COPYCONTENTS, doc.version.get().c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "name",
                     CURLFORM_COPYCONTENTS, doc.name.get().c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "description",
                     CURLFORM_COPYCONTENTS, doc.description.get().c_str(), CURLFORM_END);
        string citations;
        for (auto citation : doc.citations.getAll())
            citations += citation + ",";
        citations = citations.substr(0, citations.length() - 1);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "citations",
                     CURLFORM_COPYCONTENTS, citations.c_str(), CURLFORM_END);  // Comma separated list
        string keywords;
        for (auto kw : doc.keywords.getAll())
            keywords += kw + ",";
        keywords = keywords.substr(0, keywords.length() - 1);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "keywords",
                     CURLFORM_COPYCONTENTS, doc.keywords.get().c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "collectionChoices",
                     CURLFORM_COPYCONTENTS, collection.c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "overwrite_merge",
                     CURLFORM_COPYCONTENTS, std::to_string(overwrite).c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "user",
                     CURLFORM_COPYCONTENTS, key.c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "file",
                     CURLFORM_COPYCONTENTS, doc.writeString().c_str(), CURLFORM_CONTENTTYPE, "text/xml", CURLFORM_END);
        
        /* Set the form info */
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to submit Document failed with " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    //    Json::Value json_response;
    //    Json::Reader reader;
    //    bool parsed = reader.parse( response, json_response );     //parse process
    //    if ( parsed )
    //    {
    //        //response = json_response.get("result", response ).asString();
    //        //response = json_response.get("valid", response ).asString() << endl;
    //        //response = json_response.get("output_file", response ).asString() << endl;
    //        //response = json_response.get("valid", response ).asString();
    //        if (json_response.get("valid", response ).asString().compare("true") == 0)
    //            response = "Valid.";
    //        else
    //            response = "Invalid.";
    //        for (auto itr : json_response["errors"])
    //        {
    //            response += " " + itr.asString();
    //        }
    //    }
    if (response.compare("Error: Invalid user token") == 0)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "You must login with valid credentials before submitting");
    return response;
};

//template <> sbol::Document& sbol::PartShop::pull<sbol::Document>(std::string uri)
//{
//    std::string get_request = uri + "/sbol";
//    
//    /* Perform HTTP request */
//    std::string response;
//    CURL *curl;
//    CURLcode res;
//    
//    /* In windows, this will init the winsock stuff */
//    curl_global_init(CURL_GLOBAL_ALL);
//    
//    struct curl_slist *headers = NULL;
//    //    headers = curl_slist_append(headers, "Accept: application/json");
//    //    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
//    //    headers = curl_slist_append(headers, "charsets: utf-8");
//    
//    /* get a curl handle */
//    curl = curl_easy_init();
//    if(curl) {
//        /* First set the URL that is about to receive our POST. This URL can
//         just as well be a https:// URL if that is what should receive the
//         data. */
//        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
//        curl_easy_setopt(curl, CURLOPT_URL, get_request.c_str());
//        //        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        
//        /* Now specify the POST data */
//        //        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
//        
//        /* Now specify the callback to read the response into string */
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//        
//        /* Perform the request, res will get the return code */
//        res = curl_easy_perform(curl);
//        /* Check for errors */
//        if(res != CURLE_OK)
//            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to validate online failed with " + std::string(curl_easy_strerror(res)));
//            
//        /* always cleanup */
//            curl_easy_cleanup(curl);
//            }
//    curl_slist_free_all(headers);
//    curl_global_cleanup();
//    
//    Document& doc = *new Document();
//    doc.readString(response);
//    return doc;
//};
//
std::string PartShop::searchRootCollections()
{
    // Form get request
    std::string get_request;
    get_request = resource + "/rootCollections";
    
    /* Perform HTTP request */
    std::string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    
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
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to retrieve root collections failed with: " + std::string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    return response;
};

std::string PartShop::searchSubCollections(std::string uri)
{
    // Form get request
    std::string get_request;
    get_request = uri + "/subCollections";
    
    /* Perform HTTP request */
    std::string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    
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
    return response;
};


void PartShop::pull(std::vector<std::string> uris, Document& doc)
{
    for (auto & uri : uris)
        pull(uri, doc);
}

std::string http_get_request(std::string get_request)
{
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
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, std::string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    std::cout << response << std::endl;
    return response;
}


void PartShop::pull(std::string uri, Document& doc)
{
    std::string get_request = getURL() + "/" + uri + "/sbol";
    std::string response = http_get_request(get_request);
    
    if (response.find("<title>Error</title>") != std::string::npos)
    {
        get_request = uri + "/sbol";
        response = http_get_request(get_request);
        if (response.find("<title>Error</title>") != std::string::npos)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Part not found. Unable to pull " + uri);
    }
    
    Document temp_doc = Document();
    temp_doc.readString(response);
    temp_doc.copy(getURL(), &doc);
};

string PartShop::getURL()
{
    return resource;
}


void SearchResponse::extend(SearchResponse& response)
{
    for (auto & record : response)
    {
        records.push_back(&record);
    }
};

template<>
void sbol::PartShop::pull<ComponentDefinition>(std::string uri, Document& doc, bool recursive)
{
    pull(uri, doc);
    ComponentDefinition& cd = doc.get<ComponentDefinition>(uri);
    
    if (recursive)
    {
        pull(cd.sequences.get(), doc);
        for (auto & c : cd.components)
            pull(c.definition.get(), doc);
    }
};

