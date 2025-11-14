#ifndef REMOTE_H
#define REMOTE_H

#include <string>
#include <vector>

struct RemoteInfo {
    std::string name;
    std::string url;
    std::string owner;
    std::string repo;
};

class Remote {
public:
    // Get singleton instance
    static Remote& getInstance();
    
    // Add a remote repository
    bool addRemote(const std::string& name, const std::string& url);
    
    // Get remote URL
    std::string getRemoteUrl(const std::string& name = "origin");
    
    // List all remotes
    std::vector<RemoteInfo> listRemotes();
    
    // Parse GitHub URL to get owner and repo
    bool parseGitHubUrl(const std::string& url, std::string& owner, std::string& repo);
    
    // Check if remote exists in config
    bool hasRemote(const std::string& name = "origin");
    
    // Create GitHub repository via API
    bool createGitHubRepo(const std::string& repoName, const std::string& description, bool isPrivate = false);
    
    // Check if repository exists on GitHub
    bool checkRepoExists(const std::string& owner, const std::string& repo);
    
    // Get current repository info from remote
    RemoteInfo getCurrentRemote();
    
private:
    Remote() = default;
    ~Remote() = default;
    Remote(const Remote&) = delete;
    Remote& operator=(const Remote&) = delete;
    
    // Make HTTP request to GitHub API
    std::string makeGitHubRequest(const std::string& endpoint, const std::string& method = "GET", 
                                   const std::string& data = "");
};

// Command function for 'ada remote'
void ada_remote(int argc, char* argv[]);

#endif // REMOTE_H
