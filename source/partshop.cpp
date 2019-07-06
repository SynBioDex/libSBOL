#include "partshop.h"
#include <algorithm>

// For UNIX like implementation of getch (see login method)
// this may not be portable to windows, may need conio.h
#ifndef SBOL_WIN
#include <termios.h>
#include <unistd.h>
#else
#include <conio.h>
#endif

#include <stdio.h>

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
void encode_url(string& text)
{
    // string UTF8_AMPERSAND = "%26";
    // string UTF8_EQUALS = "%3D";
    // string UTF8_LESS_THAN = "%3C";
    // string UTF8_GREATER_THAN = "%3E";
    // string UTF8_COLON = "%3A";
    // string UTF8_HASH = "%23";
    // string UTF8_APOSTROPHE = "%27";
    // string UTF8_SPACE = "%20";
    // string UTF8_SLASH = "%2F";
    // string UTF8_CURLYBRACE_OPEN = "%7B";
    // string UTF8_CURLYBRACE_CLOSED = "%7D";
    // string UTF8_SEMICOLON = "%3B";
    // string UTF8_DOT = "%2E";
    // string UTF8_QUOTE = "%22";
    // string UTF8_QUESTION_MARK = "%3F";
    // string UTF8_OPEN_PARENTHESES = "%28";
    // string UTF8_CLOSE_PARENTHESES = "%29";
    // string UTF8_LINEFEED = "%0A";
    // string UTF8_CARRIAGE_RETURN = "%0D";

    // replace(text, "&", UTF8_AMPERSAND);
    // replace(text, "=", UTF8_EQUALS);
    // replace(text, "<", UTF8_LESS_THAN);
    // replace(text, ">", UTF8_GREATER_THAN);
    // replace(text, ":", UTF8_COLON);
    // replace(text, "#", UTF8_HASH);
    // replace(text, "'", UTF8_APOSTROPHE);
    // replace(text, " ", UTF8_SPACE);
    // replace(text, "/", UTF8_SLASH);
    // replace(text, "{", UTF8_CURLYBRACE_OPEN);
    // replace(text, "}", UTF8_CURLYBRACE_CLOSED);
    // replace(text, ";", UTF8_SEMICOLON);
    // replace(text, ".", UTF8_DOT);
    // replace(text, "\"", UTF8_DOT);
    // replace(text, "?", UTF8_DOT);
    // replace(text, ".", UTF8_DOT);
    // replace(text, "(", UTF8_DOT);
    // replace(text, ")", UTF8_DOT);
    CURL *curl;
    char * encoded_text = curl_easy_escape(curl, text.c_str(), text.size());
    text = string(encoded_text);
};

// Advanced search
SearchResponse& sbol::PartShop::search(SearchQuery& q)
{
    string url = parseURLDomain(resource);
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());
    
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
        
        encode_url(parameters);
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
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search request failed with " + string(curl_easy_strerror(res)));
        
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
SearchResponse& sbol::PartShop::search(std::string search_text, rdf_type object_type, std::string property_uri, int offset, int limit)
{
    string url = parseURLDomain(resource);
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());
    
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
        
        encode_url(parameters);
        
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
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search failed with: " + string(curl_easy_strerror(res)));
        
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

std::string sbol::PartShop::getKey()
{
    return key;
};

// General search
SearchResponse& sbol::PartShop::search(std::string search_text, rdf_type object_type, int offset, int limit)
{
    string url = parseURLDomain(resource);
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* Specify the GET data */
        // Specify the type of SBOL object to search for
        string parameters = "objectType=" + parseClassName(object_type) + "&";
        
        // Specify partial search text. Specify how many records to retrieve
        parameters = parameters + search_text;
        
        encode_url(search_text);
        
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
    string url = parseURLDomain(resource);
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());
    
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
        
        encode_url(parameters);
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

int sbol::PartShop::searchCount(std::string search_text, rdf_type object_type, std::string property_uri)
{
    string url = resource;
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());
    
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
        
        encode_url(parameters);
        
        parameters = parseURLDomain(url) + "/remoteSearch/" + parameters;
        
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

int sbol::PartShop::searchCount(std::string search_text, rdf_type object_type)
{
    string url = parseURLDomain(resource);
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* Specify the GET data */
        // Specify the type of SBOL object to search for
        string parameters = "objectType=" + parseClassName(object_type) + "&";
        
        // Specify partial search text. Specify how many records to retrieve
        parameters = parameters + search_text;
        
        encode_url(search_text);
        
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
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search failed with error message: " + response);
    }
    return count;
};


#ifndef SBOL_WIN
// Unix-like implementation of getch, might not be portable to Windows
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
#endif

void sbol::PartShop::login(std::string user_id, std::string password)
{
    this->user = user_id;
    
    if (password == "")
    {
        cout << "Password: ";
        int ch;
        while ((ch = getch()))
        {
            if (ch == 10 || ch == 13)
            {
                cout << endl;
                break;
            }
            if (ch == 127 || ch == 8)
            {
                if (password.length() > 0)
                {
                    cout << "\b \b";
                    password.erase(password.length() - 1);
                }
            }
            else
            {
                cout << "*";
                password += ch;
            }
        }
    }

    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    long http_response_code = 0;

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
        curl_easy_setopt(curl, CURLOPT_URL, (parseURLDomain(resource) + "/remoteLogin").c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        if (Config::getOption("ca-path") != "")
            curl_easy_setopt(curl , CURLOPT_CAINFO, Config::getOption("ca-path").c_str());

        /* Now specify the POST data */
        string parameters = "email=" + user_id + "&" + "password=" + password;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Login failed due to an HTTP error: " + string(curl_easy_strerror(res)));

        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_response_code);


        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    if (http_response_code != 200)
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Login failed due to a " + to_string(http_response_code) + " HTTP error: " + response);

    key = response;
};

std::string sbol::PartShop::submit(Document& doc, std::string collection, int overwrite)
{
    if (collection == "")
    {
        // If a Document is submitted as a new collection, then Document metadata must be specified
        if (doc.displayId.size() == 0 || doc.name.size() == 0 || doc.description.size() == 0)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot submit Document. The Document must be assigned a displayId, name, and description for upload.");
    }
    else
    {
        // Correct collection URI in case a spoofed resource is being used
        if (spoofed_resource != "" && collection.find(resource) != std::string::npos)
            collection = collection.replace(collection.find(resource), resource.size(), spoofed_resource);
        if (Config::getOption("verbose") == "True")
            cout << "Submitting Document to existing collection: " << collection << endl;
    }
    
    int t_start;  // For timing
    int t_end;  // For timing
    if (Config::getOption("verbose") == "True")
        t_start = getTime();

    if (Config::getOption("serialization_format") == "rdfxml")
    {
        addSynBioHubAnnotations(doc);
    }

    /* Perform HTTP request */
    string response;
    long http_response_code = 0;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());
    //    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, (parseURLDomain(resource) + "/submit").c_str());

        if (Config::getOption("ca-path") != "")
            curl_easy_setopt(curl , CURLOPT_CAINFO, Config::getOption("ca-path").c_str());
        
        /* Now specify the POST data */
        struct curl_httppost* post = NULL;
        struct curl_httppost* last = NULL;
        
        if (doc.displayId.size())
            curl_formadd(&post, &last, CURLFORM_COPYNAME, "id", CURLFORM_COPYCONTENTS, doc.displayId.get().c_str(), CURLFORM_END);
        if (doc.version.size())
            curl_formadd(&post, &last, CURLFORM_COPYNAME, "version", CURLFORM_COPYCONTENTS, doc.version.get().c_str(), CURLFORM_END);
        if (doc.name.size())
            curl_formadd(&post, &last, CURLFORM_COPYNAME, "name", CURLFORM_COPYCONTENTS, doc.name.get().c_str(), CURLFORM_END);
        if (doc.description.size())
            curl_formadd(&post, &last, CURLFORM_COPYNAME, "description", CURLFORM_COPYCONTENTS, doc.description.get().c_str(), CURLFORM_END);
        string citations;
        for (auto citation : doc.citations.getAll())
            citations += citation + ",";
        citations = citations.substr(0, citations.length() - 1);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "citations", CURLFORM_COPYCONTENTS, citations.c_str(), CURLFORM_END);  // Comma separated list
        string keywords;
        for (auto kw : doc.keywords.getAll())
            keywords += kw + ",";
        keywords = keywords.substr(0, keywords.length() - 1);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "keywords", CURLFORM_COPYCONTENTS, keywords.c_str(), CURLFORM_END);
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "collectionChoices", CURLFORM_COPYCONTENTS, collection.c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "overwrite_merge", CURLFORM_COPYCONTENTS, std::to_string(overwrite).c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "user", CURLFORM_COPYCONTENTS, key.c_str(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "file", CURLFORM_COPYCONTENTS, doc.writeString().c_str(), CURLFORM_CONTENTTYPE, "text/xml", CURLFORM_END);

        if (collection != "")
            curl_formadd(&post, &last, CURLFORM_COPYNAME, "rootCollections", CURLFORM_COPYCONTENTS, collection.c_str());
        
        
        /* Set the form info */
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        if (Config::getOption("verbose") == "True")
        {
            t_end = getTime();
            cout << "Serialization took " << t_end - t_start << " seconds" << endl;
            t_start = getTime();   
        }        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_response_code);
        
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "HTTP post request failed with: " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    if (Config::getOption("verbose") == "True")
    {
        cout << "Submission request returned HTTP response code " << http_response_code << endl;
        t_end = getTime();
        cout << "Submission request took " << t_end - t_start << " seconds" << endl;
    }

    if (http_response_code == 200)
        return response;
    else if (http_response_code == 401)
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "You must login with valid credentials before submitting");
    else
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "HTTP post request failed with: " + response);
};

//std::string sbol::PartShop::submit(std::string filename, std::string collection, int overwrite)
//{
//    if (filename != "" && filename[0] == '~') {
//        if (filename[1] != '/'){
//            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Malformed input path. Potentially missing slash.");
//        }
//        char const* home = getenv("HOME");
//        if (home || (home = getenv("USERPROFILE"))) {
//            filename.replace(0, 1, home);
//        }
//    }
//    FILE* fh = fopen(filename.c_str(), "rb");
//    if (!fh)
//        throw SBOLError(SBOL_ERROR_FILE_NOT_FOUND, "File " + filename + " not found");
//
//    /* Perform HTTP request */
//    string response;
//    CURL *curl;
//    CURLcode res;
//    
//    /* In windows, this will init the winsock stuff */
//    curl_global_init(CURL_GLOBAL_ALL);
//    
//    struct curl_slist *headers = NULL;
//    headers = curl_slist_append(headers, "Accept: text/plain");
//    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());
//    //    headers = curl_slist_append(headers, "charsets: utf-8");
//    
//    /* get a curl handle */
//    curl = curl_easy_init();
//    if(curl)
//    {
//        /* First set the URL that is about to receive our POST. This URL can
//         just as well be a https:// URL if that is what should receive the
//         data. */
//        
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        curl_easy_setopt(curl, CURLOPT_URL, (parseURLDomain(resource) + "/submit").c_str());
//        if (Config::getOption("verbose") == "True")
//            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
//
//        /* Now specify the POST data */
//        struct curl_httppost* post = NULL;
//        struct curl_httppost* last = NULL;
//        
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "id", CURLFORM_COPYCONTENTS, "blah", CURLFORM_END);
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "version", CURLFORM_COPYCONTENTS, "1", CURLFORM_END);
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "name", CURLFORM_COPYCONTENTS, "blah", CURLFORM_END);
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "description", CURLFORM_COPYCONTENTS, "blah", CURLFORM_END);
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "citations", CURLFORM_COPYCONTENTS, "blah", CURLFORM_END);  // Comma separated list
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "keywords", CURLFORM_COPYCONTENTS, "blah", CURLFORM_END);
//        
//        
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "overwrite_merge", CURLFORM_COPYCONTENTS, std::to_string(overwrite).c_str(), CURLFORM_END);
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "user", CURLFORM_COPYCONTENTS, key.c_str(), CURLFORM_END);
//        curl_formadd(&post, &last, CURLFORM_COPYNAME, "file", CURLFORM_FILE, filename.c_str(), CURLFORM_END);  // Upload file
//        if (collection != "")
//            curl_formadd(&post, &last, CURLFORM_COPYNAME, "rootCollections", CURLFORM_COPYCONTENTS, collection.c_str());
//        
//        
//        /* Set the form info */
//        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
//        
//        /* Now specify the callback to read the response into string */
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//        
//        /* Perform the request, res will get the return code */
//        res = curl_easy_perform(curl);
//        /* Check for errors */
//        if(res != CURLE_OK)
//            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "HTTP post request failed with: " + string(curl_easy_strerror(res)));
//        
//        /* always cleanup */
//        curl_easy_cleanup(curl);
//    }
//    return response;
//};

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
    get_request = parseURLDomain(resource) + "/rootCollections";
    
    /* Perform HTTP request */
    std::string response;
    CURL *curl;
    CURLcode res;
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());

    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
        
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, get_request.c_str());

        if (Config::getOption("ca-path") != "")
            curl_easy_setopt(curl , CURLOPT_CAINFO, Config::getOption("ca-path").c_str());

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
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
        
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        //curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, get_request.c_str());

        if (Config::getOption("ca-path") != "")
            curl_easy_setopt(curl , CURLOPT_CAINFO, Config::getOption("ca-path").c_str());

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


void PartShop::pull(std::vector<std::string> uris, Document& doc, bool recursive)
{
    for (auto & uri : uris)
        pull(uri, doc, recursive);
}

std::string http_get_request(std::string get_request, unordered_map<string, string>* headers = NULL, unordered_map<string, string>* response_headers = NULL)
{
    /* Perform HTTP request */
    std::string response;
    CURL *curl;
    CURLcode res;

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *header_list = NULL;
    if (headers)
        for (auto & header : *headers)
            header_list = curl_slist_append(header_list, (header.first + ": " + header.second).c_str());
    
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
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
        if (Config::getOption("ca-path") != "")
            curl_easy_setopt(curl , CURLOPT_CAINFO, Config::getOption("ca-path").c_str());

        /* Now specify the POST data */
        //        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Now specify the callback to read response headers */
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, CurlResponseHeader_CallbackFunc);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, response_headers);
        if (Config::getOption("ca-path") != "")
            curl_easy_setopt(curl , CURLOPT_CAINFO, Config::getOption("ca-path").c_str());

        if (Config::getOption("verbose") == "True")
        {
            std::cout << "Issuing get request: " << get_request << std::endl;
        }

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, std::string(curl_easy_strerror(res)));

        long http_response_code = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_response_code);
        if (Config::getOption("verbose") == "True")
        {
            std::cout << "Received response" << std::endl << response << std::endl;
            std::cout << "HTTP request returned status code " << http_response_code << std::endl;
        }
        if (http_response_code == 404)
            throw SBOLError(SBOL_ERROR_NOT_FOUND, "");
        else if (http_response_code == 401)
            throw SBOLError(SBOL_ERROR_HTTP_UNAUTHORIZED, "Please login with valid credentials");
        else if (http_response_code == 302)
            ;  // Do nothing in case of redirect. This occurs sometimes with spoofed resources
        else if (http_response_code != 200)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, response);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(header_list);
    curl_global_cleanup();
    return response;
}


void PartShop::pull(std::string uri, Document& doc, bool recursive)
{
    std::string response;  // holds the response returned from the http get request
    unordered_map<string, string> headers;
    headers["X-authorization"] = key;
    headers["Accept"] = "text/plain";

    string query;
    if (uri.find(resource) != std::string::npos)
        query = uri;  // User has specified full URI
    else if (uri.find(parseURLDomain(resource)) != std::string::npos)
        query = uri;  // User has specified full URI
    else if (spoofed_resource != "" && uri.find(spoofed_resource) != std::string::npos)
        query = uri.replace(uri.find(spoofed_resource), spoofed_resource.size(), resource);
    else
        query = resource + "/" + uri;  // Assume user has only specified displayId
    try
    {
        string get_request = query + "/sbol";
        if (!recursive)
            get_request += "nr";
        if (Config::getOption("verbose") == "True")
            std::cout << "Issuing get request:\n" << get_request << std::endl;
        response = http_get_request(get_request, &headers);
    }
    catch (SBOLError& e)
    {
        if (e.error_code() == SBOL_ERROR_NOT_FOUND)
            throw SBOLError(SBOL_ERROR_NOT_FOUND, "Part not found. Unable to pull " + uri);
    }

    Document temp_doc = Document();
    string serialization_format = Config::getOption("serialization_format");
    Config::setOption("serialization_format", "sbol");
    doc.readString(response);
    Config::setOption("serialization_format", serialization_format);
    doc.resource_namespaces.insert(resource);
};

void sbol::PartShop::spoof(std::string spoofed_url)
{
    if (spoofed_url.size() && spoofed_url.back() == '/')
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "PartShop initialization failed. The spoofed URL should not contain a terminal backslash");
    spoofed_resource = spoofed_url;
};

std::string sbol::PartShop::sparqlQuery(std::string query)
{
    string endpoint = parseURLDomain(this->resource) + "/sparql?query=";
    string resource;
    if (spoofed_resource == "")
        resource = this->resource;
    else
        resource = this->spoofed_resource;

    size_t p = query.find("WHERE");
    if (p != std::string::npos)
    {
        string from_clause = "  FROM <" + parseURLDomain(resource) + "/user/" + user + "> ";
        query = query.insert(p, from_clause);
    }
    encode_url(query);
    query = endpoint + query;

    unordered_map<string, string> headers;
    unordered_map<string, string> header_response;
    headers["X-authorization"] = key;
    headers["Accept"] = "application/json";
    
    string response;
    if (Config::getOption("verbose") == "True")
        std::cout << "Issuing SPARQL:\n" << query << std::endl;
    response = http_get_request(query, &headers);

    return response;
};

void sbol::PartShop::remove(string uri)
{
    string query;
    if (uri.find(resource) != std::string::npos)
        query = uri;  // User has specified full URI
    else if (uri.find(parseURLDomain(resource)) != std::string::npos)
        query = uri;  // User has specified full URI
    else if (spoofed_resource != "" && uri.find(spoofed_resource) != std::string::npos)
        query = uri.replace(uri.find(spoofed_resource), spoofed_resource.size(), resource);
    else
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Removal of " + uri + " failed. The object does not exist in the resource namespace");

    string endpoint = query + "/remove";
    
    unordered_map<string, string> headers;
    unordered_map<string, string> header_response;
    headers["X-authorization"] = key;
    headers["Accept"] = "application/json";
    
    http_get_request(endpoint, &headers);
};

string PartShop::getUser()
{
    return user;
}

string PartShop::getURL()
{
    return resource;
}

string PartShop::getSpoofedURL()
{
    return spoofed_resource;
}

void PartShop::attachFile(std::string topleveluri, std::string filename)
{
    if (filename != "" && filename[0] == '~') {
        if (filename[1] != '/'){
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Malformed input path. Potentially missing slash.");
        }
        char const* home = getenv("HOME");
        if (home || (home = getenv("USERPROFILE"))) {
            filename.replace(0, 1, home);
        }
    }
    FILE* fh = fopen(filename.c_str(), "rb");
    if (!fh)
        throw SBOLError(SBOL_ERROR_FILE_NOT_FOUND, "File " + filename + " not found");
    
    /* Perform HTTP request */
    string response;
    long http_response_code = 0;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: text/plain");
    headers = curl_slist_append(headers, string("X-authorization: " + key).c_str());
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, string(topleveluri + "/attach").c_str());
        if (Config::getOption("ca-path") != "")
            curl_easy_setopt(curl , CURLOPT_CAINFO, Config::getOption("ca-path").c_str());

        /* Now specify the POST data */
        struct curl_httppost* post = NULL;
        struct curl_httppost* last = NULL;

        curl_formadd(&post, &last, CURLFORM_COPYNAME, "file", CURLFORM_FILE, filename.c_str(), CURLFORM_END);
        
        /* Set the form info */
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to upload attachment failed with " + string(curl_easy_strerror(res)));
        
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_response_code);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    if (Config::getOption("verbose") == "True")
        std::cout << response << std::endl;

    if (http_response_code == 401)
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "You must login with valid credentials before submitting");
    if (http_response_code != 200)
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Attempt to attach file failed with HTTP " + to_string(http_response_code));
};

void PartShop::downloadAttachment(string attachment_uri, string path)
{
    if (parseURLDomain(attachment_uri) != resource)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot download attachment. The URI does not match the domain for this PartShop.");
    string url = attachment_uri + "/download";
    unordered_map<string, string> headers;
    unordered_map<string, string> header_response;

    headers["X-authorization"] = key;
    headers["Accept"] = "text/plain";
    string response = http_get_request(url, &headers, &header_response);
    if (response.find("<!DOCTYPE html>") != std::string::npos)
        throw SBOLError(SBOL_ERROR_NOT_FOUND, "Unable to download. Attachment " + attachment_uri + " not found.");
    if (header_response.find("Content-Disposition") == header_response.end())
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "You must login with valid credentials before submitting");

    std::string filename = header_response["Content-Disposition"];
    filename.erase(0, 23); // remove the substring: attachment; filename="
    filename.erase(filename.end() - 2, filename.end()); // remove the terminating "

    FILE* fh = fopen((path + "/" + filename).c_str(), "wb");
    if (!fh)
        throw SBOLError(SBOL_ERROR_FILE_NOT_FOUND, "Cannot download attachment. The target path " + path + filename + " is invalid.");

    fputs(response.c_str(), fh);
    fclose(fh);
}

void PartShop::addSynBioHubAnnotations(Document& doc)
{
    doc.addNamespace("http://wiki.synbiohub.org/wiki/Terms/synbiohub#", "sbh");
    for (auto & key_val_pair : doc.SBOLObjects)
    {
        SBOLObject* toplevel = key_val_pair.second;
        toplevel->apply( [](SBOLObject* o, void * user_data) 
            { 
                SBOLObject* toplevel = (SBOLObject*)user_data;
                URIProperty annotation = URIProperty(o, "http://wiki.synbiohub.org/wiki/Terms/synbiohub#topLevel", '0', '1', ValidationRules({}), toplevel->identity.get());
            }, (void*)toplevel);
    }
}

bool sbol::PartShop::exists(std::string uri)
{
    unordered_map<string, string> headers;
    headers["X-authorization"] = key;
    headers["Accept"] = "text/plain";

    string query;
    string response;

    if (uri.find(resource) != std::string::npos)
        query = uri;  // User has specified full URI
    else if (uri.find(parseURLDomain(resource)) != std::string::npos)
        query = uri;  // User has specified full URI
    else if (spoofed_resource != "" && uri.find(spoofed_resource) != std::string::npos)
        query = uri.replace(uri.find(spoofed_resource), spoofed_resource.size(), resource);
    try
    {
        string get_request = query + "/metadata";
        if (Config::getOption("verbose") == "True")
            std::cout << "Issuing get request:\n" << get_request << std::endl;
        response = http_get_request(get_request, &headers);
    }   
    catch (SBOLError& e)
    {
        throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Search request failed with response: " + e.error_message());
    }

    Json::Value json_response;
    Json::Reader reader;
    bool parsed = reader.parse(response, json_response);
    if (!parsed)
        return false;
    else if (response == "[]")
        return false;
    else
        return true;
};

std::string Document::convert(string language, string output_path)
{
    string original_language = Config::getOption("language");
    string original_return_file = Config::getOption("return_file");
    if (language != "")
    {
        Config::setOption("language", language);
        Config::setOption("return_file", "True");
    }

    /* Form validation options in JSON */
    Json::Value request;   // 'root' will contain the root value after parsing.
    
    vector<string> opts = {"language", "test_equality", "check_uri_compliance", "check_completeness", "check_best_practices", "fail_on_first_error", "provide_detailed_stack_trace", "subset_uri", "uri_prefix", "version", "insert_type", "main_file_name", "diff_file_name" };
    for (auto const& opt : opts)
    {
        if (Config::getOption(opt).compare("True") == 0)
            request["options"][opt] = true;
        else if (Config::getOption(opt).compare("False") == 0)
            request["options"][opt] = false;
        else
            request["options"][opt] = Config::getOption(opt);
    }
    if (Config::getOption("return_file").compare("True") == 0)
        request["return_file"] = true;
    else if (Config::getOption("return_file").compare("False") == 0)
        request["return_file"] = false;
    request["main_file"] = writeString();
    Json::StyledWriter writer;
    string json = writer.write( request );
    
    
    /* Perform HTTP request */
    string response;
    CURL *curl;
    CURLcode res;
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");
    
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        curl_easy_setopt(curl, CURLOPT_URL, Config::getOption("validator_url").c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        if (Config::getOption("ca-path") != "")
            curl_easy_setopt(curl , CURLOPT_CAINFO, Config::getOption("ca-path").c_str());

        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        
        /* Now specify the callback to read the response into string */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            throw SBOLError(SBOL_ERROR_BAD_HTTP_REQUEST, "Cannot validate online. HTTP post request failed with: " + string(curl_easy_strerror(res)));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(headers);
    curl_global_cleanup();
    
    Json::Value json_response;
    Json::Reader reader;
    bool parsed = reader.parse( response, json_response );     //parse process
    if ( parsed )
    {
        if (json_response.get("valid", response ).asString().compare("true") == 0)
        {
            response = json_response.get("output_file", response ).asString();
            string converted_file = http_get_request(response);  // retrieve converted file from URL

            if (output_path == "")
                output_path = parseClassName(response);  // parse filename from URL
            FILE* fh = fopen(output_path.c_str(), "wb");
            if (!fh)
                throw SBOLError(SBOL_ERROR_FILE_NOT_FOUND, "Cannot download converted file. The target path " + output_path + " is invalid.");
            
            fputs(converted_file.c_str(), fh);
            fclose(fh);
        }
        else
        {
            response = "Invalid.";
            for (auto itr : json_response["errors"])
            {
                response += " " + itr.asString();
            }
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, response);
        }
    }
    Config::setOption("language", original_language);
    Config::setOption("return_file", original_return_file);
    return response;
};

void SearchResponse::extend(SearchResponse& response)
{
    for (auto & record : response)
    {
        records.push_back(&record);
    }
};

string SearchResponse::__str__()
{
    Json::Value json;
    Json::Reader reader;

    for(auto & r : records)
    {
        Json::Value json_entry;
        json_entry["identity"] = r->identity.get();
        if (r->displayId.size())
            json_entry["displayId"] = r->displayId.get();
        if (r->name.size())
            json_entry["name"] = r->name.get();
        if (r->description.size())
            json_entry["description"] = r->description.get();
        if (r->version.size())
            json_entry["version"] = r->version.get();
        json.append(json_entry);
    }
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  "; // If you want whitespace-less output
    const std::string output = Json::writeString(builder, json);
    return output;
};

string SearchQuery::__str__()
{
    Json::Value json;
    Json::Reader reader;
    
    for (auto & p : getProperties())
    {
        if (p == SBOL_IDENTITY)
            continue;
        string p_name = parsePropertyName(p);
        string p_val = properties[p].front();
        p_val = p_val.substr(1, p_val.length() - 2);
        // Check if property store is empty
        if (p_val != "")
        {
            if (p_name == "title")
                p_name = "name";
            json[p_name] = p_val;
        }
    }
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  ";
    const std::string output = Json::writeString(builder, json);
    return output;
};


namespace sbol
{
    template<>
    void PartShop::pull<ComponentDefinition>(std::string uri, Document& doc, bool recursive)
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
}
