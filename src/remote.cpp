#include "remote.h"
#include "config.h"
#include "github_auth.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <curl/curl.h>
#include <regex>

namespace fs = std::filesystem;

// Callback function for CURL to write data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Remote& Remote::getInstance() {
    static Remote instance;
    return instance;
}

bool Remote::addRemote(const std::string& name, const std::string& url) {
    Config& config = Config::getInstance();
    std::string key = "remote." + name + ".url";
    config.set(key, url, false);
    return true;
}

std::string Remote::getRemoteUrl(const std::string& name) {
    Config& config = Config::getInstance();
    std::string key = "remote." + name + ".url";
    return config.get(key, false);
}

std::vector<RemoteInfo> Remote::listRemotes() {
    std::vector<RemoteInfo> remotes;
    
    // Read local config file
    fs::path repoPath = fs::current_path() / ".ada";
    fs::path configPath = repoPath / "config";
    
    if (!fs::exists(configPath)) {
        return remotes;
    }
    
    std::ifstream file(configPath);
    std::string line;
    std::regex remoteRegex(R"(remote\.([^.]+)\.url=(.+))");
    
    while (std::getline(file, line)) {
        std::smatch match;
        if (std::regex_match(line, match, remoteRegex)) {
            RemoteInfo info;
            info.name = match[1];
            info.url = match[2];
            
            // Parse URL for owner and repo
            parseGitHubUrl(info.url, info.owner, info.repo);
            
            remotes.push_back(info);
        }
    }
    
    return remotes;
}

bool Remote::parseGitHubUrl(const std::string& url, std::string& owner, std::string& repo) {
    // Handle both HTTPS and SSH URLs
    // HTTPS: https://github.com/owner/repo.git or https://github.com/owner/repo
    // SSH: git@github.com:owner/repo.git
    
    std::regex httpsRegex(R"(https://github\.com/([^/]+)/(.+))");
    std::regex sshRegex(R"(git@github\.com:([^/]+)/(.+))");
    
    std::smatch match;
    
    if (std::regex_search(url, match, httpsRegex) || std::regex_search(url, match, sshRegex)) {
        owner = match[1];
        repo = match[2];
        
        // Remove .git suffix if present
        if (repo.size() > 4 && repo.substr(repo.size() - 4) == ".git") {
            repo = repo.substr(0, repo.size() - 4);
        }
        
        // Trim any whitespace or newlines
        repo.erase(repo.find_last_not_of(" \t\n\r") + 1);
        owner.erase(owner.find_last_not_of(" \t\n\r") + 1);
        
        return true;
    }
    
    return false;
}

bool Remote::hasRemote(const std::string& name) {
    std::string url = getRemoteUrl(name);
    return !url.empty();
}

std::string Remote::makeGitHubRequest(const std::string& endpoint, const std::string& method, 
                                      const std::string& data) {
    GitHubAuth& auth = GitHubAuth::getInstance();
    std::string token = auth.getToken();
    
    if (token.empty()) {
        std::cerr << "GitHub token not configured. Run: ada config --global github.token <your_token>\n";
        return "";
    }
    
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://api.github.com" + endpoint;
        std::string authHeader = "Authorization: token " + token;
        std::string userAgent = "User-Agent: Ada-VCS";
        std::string contentType = "Content-Type: application/json";
        
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, authHeader.c_str());
        headers = curl_slist_append(headers, userAgent.c_str());
        headers = curl_slist_append(headers, contentType.c_str());
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        if (method == "POST") {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        } else if (method == "PUT") {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        } else if (method == "DELETE") {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        }
        
        res = curl_easy_perform(curl);
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        if (res == CURLE_OK) {
            return readBuffer;
        }
    }
    
    return "";
}

bool Remote::createGitHubRepo(const std::string& repoName, const std::string& description, bool isPrivate) {
    // Create JSON payload
    std::string payload = "{"
        "\"name\":\"" + repoName + "\","
        "\"description\":\"" + description + "\","
        "\"private\":" + (isPrivate ? "true" : "false") +
        "}";
    
    std::string response = makeGitHubRequest("/user/repos", "POST", payload);
    
    if (!response.empty() && response.find("\"id\":") != std::string::npos) {
        std::cout << "Repository created successfully on GitHub!\n";
        
        // Extract clone URL and add as remote
        size_t urlPos = response.find("\"clone_url\":\"");
        if (urlPos != std::string::npos) {
            size_t start = urlPos + 13;
            size_t end = response.find("\"", start);
            std::string cloneUrl = response.substr(start, end - start);
            
            addRemote("origin", cloneUrl);
            std::cout << "Added remote 'origin': " << cloneUrl << "\n";
        }
        
        return true;
    }
    
    std::cerr << "Failed to create repository on GitHub.\n";
    if (response.find("\"name already exists\"") != std::string::npos) {
        std::cerr << "Repository with this name already exists.\n";
    }
    
    return false;
}

bool Remote::checkRepoExists(const std::string& owner, const std::string& repo) {
    std::string endpoint = "/repos/" + owner + "/" + repo;
    std::string response = makeGitHubRequest(endpoint, "GET");
    
    return !response.empty() && response.find("\"id\":") != std::string::npos;
}

RemoteInfo Remote::getCurrentRemote() {
    RemoteInfo info;
    info.name = "origin";
    info.url = getRemoteUrl("origin");
    
    if (!info.url.empty()) {
        parseGitHubUrl(info.url, info.owner, info.repo);
    }
    
    return info;
}

void ada_remote(int argc, char* argv[]) {
    Remote& remote = Remote::getInstance();
    
    // Check if in ada repository
    fs::path repoPath = fs::current_path() / ".ada";
    if (!fs::exists(repoPath)) {
        std::cerr << "Not an ada repository (or any of the parent directories)\n";
        return;
    }
    
    // ada remote (list remotes)
    if (argc == 2) {
        auto remotes = remote.listRemotes();
        if (remotes.empty()) {
            std::cout << "No remotes configured.\n";
        } else {
            for (const auto& r : remotes) {
                std::cout << r.name << "\t" << r.url << "\n";
            }
        }
        return;
    }
    
    std::string subcommand = argv[2];
    
    // ada remote add <name> <url>
    if (subcommand == "add") {
        if (argc < 5) {
            std::cerr << "Usage: ada remote add <name> <url>\n";
            return;
        }
        
        std::string name = argv[3];
        std::string url = argv[4];
        
        remote.addRemote(name, url);
        std::cout << "Added remote '" << name << "': " << url << "\n";
        return;
    }
    
    // ada remote -v (verbose list)
    if (subcommand == "-v") {
        auto remotes = remote.listRemotes();
        if (remotes.empty()) {
            std::cout << "No remotes configured.\n";
        } else {
            for (const auto& r : remotes) {
                std::cout << r.name << "\t" << r.url << " (fetch)\n";
                std::cout << r.name << "\t" << r.url << " (push)\n";
            }
        }
        return;
    }
    
    std::cout << "Usage:\n";
    std::cout << "  ada remote                  List remotes\n";
    std::cout << "  ada remote -v               List remotes verbosely\n";
    std::cout << "  ada remote add <name> <url> Add a new remote\n";
}
