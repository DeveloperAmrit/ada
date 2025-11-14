#ifndef GITHUB_AUTH_H
#define GITHUB_AUTH_H

#include <string>

class GitHubAuth {
public:
    // Get singleton instance
    static GitHubAuth& getInstance();
    
    // Check if user is authenticated
    bool isAuthenticated();
    
    // Get GitHub token from config
    std::string getToken();
    
    // Get GitHub username from config
    std::string getUsername();
    
    // Verify token is valid by making an API call
    bool verifyToken(const std::string& token);
    
    // Get authenticated user info
    std::string getAuthenticatedUser(const std::string& token);
    
private:
    GitHubAuth() = default;
    ~GitHubAuth() = default;
    GitHubAuth(const GitHubAuth&) = delete;
    GitHubAuth& operator=(const GitHubAuth&) = delete;
};

#endif // GITHUB_AUTH_H
