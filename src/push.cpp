#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <vector>
#include "push.h"
#include "remote.h"
#include "github_auth.h"
#include "config.h"

namespace fs = std::filesystem;

// Callback function for CURL to write data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Base64 encoding function
std::string base64_encode(const std::string& input) {
    static const char* base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    int in_len = input.size();
    const unsigned char* bytes_to_encode = reinterpret_cast<const unsigned char*>(input.c_str());

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; i < 4; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; j < i + 1; j++)
            ret += base64_chars[char_array_4[j]];

        while(i++ < 3)
            ret += '=';
    }

    return ret;
}

// Upload a file to GitHub
bool uploadFileToGitHub(const std::string& owner, const std::string& repo, 
                        const std::string& filePath, const std::string& content,
                        const std::string& token) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;
    
    std::string readBuffer;
    std::string endpoint = "/repos/" + owner + "/" + repo + "/contents/" + filePath;
    std::string url = "https://api.github.com" + endpoint;
    
    // Encode content to base64
    std::string encodedContent = base64_encode(content);
    
    // Create JSON payload
    std::string payload = "{"
        "\"message\":\"Add " + filePath + "\","
        "\"content\":\"" + encodedContent + "\""
        "}";
    
    std::string authHeader = "Authorization: token " + token;
    std::string userAgent = "User-Agent: Ada-VCS";
    std::string contentType = "Content-Type: application/json";
    
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, authHeader.c_str());
    headers = curl_slist_append(headers, userAgent.c_str());
    headers = curl_slist_append(headers, contentType.c_str());
    
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    
    CURLcode res = curl_easy_perform(curl);
    
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    
    return (res == CURLE_OK && (http_code == 201 || http_code == 200));
}

void ada_push() {
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
            std::cerr << "Or create a GitHub repo with GitHub integration\n";
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
            std::cerr << "1. Create a GitHub Personal Access Token at:\n";
            std::cerr << "   https://github.com/settings/tokens\n";
            std::cerr << "2. Configure it with: ada config --global github.token <your_token>\n";
            std::cerr << "3. Configure your username: ada config --global github.username <your_username>\n";
            return;
        }

        std::cout << "Pushing to " << remoteInfo.owner << "/" << remoteInfo.repo << "...\n";

        // Check if repository exists
        if (!remote.checkRepoExists(remoteInfo.owner, remoteInfo.repo)) {
            std::cout << "Repository doesn't exist on GitHub. Create it? [y/N]: ";
            std::string response;
            std::getline(std::cin, response);
            
            if (response == "y" || response == "Y") {
                fs::path currentPath = fs::current_path();
                std::string repoName = currentPath.filename().string();
                
                std::cout << "Creating repository '" << repoName << "' on GitHub...\n";
                if (!remote.createGitHubRepo(repoName, "Created by Ada VCS", false)) {
                    std::cerr << "Failed to create repository.\n";
                    return;
                }
            } else {
                std::cerr << "Push cancelled.\n";
                return;
            }
        }

        // Read local commits
        fs::path commitsLog = repoPath / "commits.log";
        if (!fs::exists(commitsLog) || fs::file_size(commitsLog) == 0) {
            std::cerr << "No commits to push.\n";
            return;
        }

        std::cout << "Uploading files to GitHub...\n";
        
        // Get the list of committed files from the index
        fs::path indexPath = repoPath / "index";
        std::vector<std::string> filesToUpload;
        
        if (fs::exists(indexPath)) {
            std::ifstream indexFile(indexPath);
            std::string line;
            while (std::getline(indexFile, line)) {
                std::istringstream iss(line);
                std::string filePath;
                iss >> filePath;
                filesToUpload.push_back(filePath);
            }
            indexFile.close();
        }
        
        // If no index, get all tracked files from current directory
        if (filesToUpload.empty()) {
            for (const auto& entry : fs::recursive_directory_iterator(fs::current_path())) {
                if (entry.is_regular_file()) {
                    std::string relPath = fs::relative(entry.path(), fs::current_path()).string();
                    // Skip .ada directory
                    if (relPath.find(".ada") != 0 && relPath.find("/.ada") == std::string::npos) {
                        filesToUpload.push_back(relPath);
                    }
                }
            }
        }
        
        int uploadedCount = 0;
        int failedCount = 0;
        
        for (const auto& filePath : filesToUpload) {
            fs::path fullPath = fs::current_path() / filePath;
            
            if (!fs::exists(fullPath) || !fs::is_regular_file(fullPath)) {
                continue;
            }
            
            // Read file content
            std::ifstream file(fullPath, std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "  ✗ Failed to read: " << filePath << "\n";
                failedCount++;
                continue;
            }
            
            std::string content((std::istreambuf_iterator<char>(file)), 
                               std::istreambuf_iterator<char>());
            file.close();
            
            // Upload to GitHub
            if (uploadFileToGitHub(remoteInfo.owner, remoteInfo.repo, filePath, 
                                   content, auth.getToken())) {
                std::cout << "  ✓ " << filePath << "\n";
                uploadedCount++;
            } else {
                std::cerr << "  ✗ " << filePath << "\n";
                failedCount++;
            }
        }
        
        std::cout << "\n✓ Pushed " << uploadedCount << " file(s) to GitHub\n";
        if (failedCount > 0) {
            std::cout << "⚠ " << failedCount << " file(s) failed to upload\n";
        }
        std::cout << "View at: https://github.com/" << remoteInfo.owner << "/" << remoteInfo.repo << "\n";

    } catch (const std::exception& ex) {
        std::cerr << "Error during push: " << ex.what() << std::endl;
    }
}
