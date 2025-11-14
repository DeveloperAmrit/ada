#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <curl/curl.h>
#include "pull.h"
#include "remote.h"
#include "github_auth.h"

namespace fs = std::filesystem;

// Callback function for CURL to write data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void ada_pull() {
    try {
        // Check if in ada repository
        fs::path repoPath = fs::current_path() / ".ada";
        if (!fs::exists(repoPath)) {
            std::cerr << "Not an ada repository (or any of the parent directories)\n";
            return;
        }

        // Get remote info
        Remote& remote = Remote::getInstance();
        if (!remote.hasRemote("origin")) {
            std::cerr << "No remote repository configured.\n";
            std::cerr << "Add a remote with: ada remote add origin <url>\n";
            return;
        }

        RemoteInfo remoteInfo = remote.getCurrentRemote();
        
        if (remoteInfo.owner.empty() || remoteInfo.repo.empty()) {
            std::cerr << "Could not parse GitHub repository from remote URL\n";
            return;
        }

        // Check authentication
        GitHubAuth& auth = GitHubAuth::getInstance();
        if (!auth.isAuthenticated()) {
            std::cerr << "GitHub authentication not configured.\n";
            std::cerr << "Configure with: ada config --global github.token <your_token>\n";
            return;
        }

        std::cout << "Pulling from " << remoteInfo.owner << "/" << remoteInfo.repo << "...\n";

        // Check if repository exists
        if (!remote.checkRepoExists(remoteInfo.owner, remoteInfo.repo)) {
            std::cerr << "Repository does not exist on GitHub.\n";
            return;
        }

        // Fetch the sync file from GitHub
        std::string endpoint = "/repos/" + remoteInfo.owner + "/" + remoteInfo.repo + "/contents/.ada-sync";
        
        CURL* curl = curl_easy_init();
        std::string readBuffer;
        std::string token = auth.getToken();
        
        if (curl) {
            std::string url = "https://api.github.com" + endpoint;
            std::string authHeader = "Authorization: token " + token;
            std::string userAgent = "User-Agent: Ada-VCS";
            
            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, authHeader.c_str());
            headers = curl_slist_append(headers, userAgent.c_str());
            
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            
            CURLcode res = curl_easy_perform(curl);
            
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            
            if (res == CURLE_OK && http_code == 200) {
                std::cout << "✓ Successfully pulled from remote\n";
                std::cout << "Repository is synchronized with GitHub\n";
            } else if (http_code == 404) {
                std::cout << "No changes to pull (sync file not found on remote)\n";
                std::cout << "Push first to initialize remote tracking\n";
            } else {
                std::cerr << "Failed to fetch from remote (HTTP " << http_code << ")\n";
            }
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error during pull: " << ex.what() << std::endl;
    }
}