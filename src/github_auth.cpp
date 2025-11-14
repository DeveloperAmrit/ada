#include "github_auth.h"
#include "config.h"
#include <iostream>
#include <curl/curl.h>
#include <sstream>

// Callback function for CURL to write data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

GitHubAuth& GitHubAuth::getInstance() {
    static GitHubAuth instance;
    return instance;
}

bool GitHubAuth::isAuthenticated() {
    Config& config = Config::getInstance();
    std::string token = config.get("github.token", true);
    std::string username = config.get("github.username", true);
    
    return !token.empty() && !username.empty();
}

std::string GitHubAuth::getToken() {
    Config& config = Config::getInstance();
    return config.get("github.token", true);
}

std::string GitHubAuth::getUsername() {
    Config& config = Config::getInstance();
    return config.get("github.username", true);
}

bool GitHubAuth::verifyToken(const std::string& token) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if(curl) {
        std::string authHeader = "Authorization: token " + token;
        std::string userAgent = "User-Agent: Ada-VCS";
        
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, authHeader.c_str());
        headers = curl_slist_append(headers, userAgent.c_str());
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/user");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        return (res == CURLE_OK && http_code == 200);
    }
    
    return false;
}

std::string GitHubAuth::getAuthenticatedUser(const std::string& token) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if(curl) {
        std::string authHeader = "Authorization: token " + token;
        std::string userAgent = "User-Agent: Ada-VCS";
        
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, authHeader.c_str());
        headers = curl_slist_append(headers, userAgent.c_str());
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/user");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        if (res == CURLE_OK && http_code == 200) {
            // Parse JSON to get username
            // Simple parsing - look for "login":"username"
            size_t loginPos = readBuffer.find("\"login\":");
            if (loginPos != std::string::npos) {
                size_t start = readBuffer.find("\"", loginPos + 8) + 1;
                size_t end = readBuffer.find("\"", start);
                return readBuffer.substr(start, end - start);
            }
        }
    }
    
    return "";
}
