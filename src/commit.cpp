#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cryptlib.h>
#include <sha.h>
#include <hex.h>
#include "commit.h"

namespace fs = std::filesystem;

std::string sha1_hash_commit(const std::string &data) {
    using namespace CryptoPP;

    SHA1 hash;
    byte digest[SHA1::DIGESTSIZE];

    hash.Update(reinterpret_cast<const byte*>(data.data()), data.size());
    hash.Final(digest);

    HexEncoder encoder;
    std::string hexHash;
    encoder.Attach(new StringSink(hexHash));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return hexHash;
}

std::string get_current_timestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string get_parent_commit(const fs::path& repoPath) {
    fs::path headPath = repoPath / "HEAD";
    if (!fs::exists(headPath)) {
        return "";
    }

    std::ifstream headFile(headPath);
    std::string headContent;
    std::getline(headFile, headContent);
    headFile.close();

    // HEAD contains "ref: refs/heads/main"
    if (headContent.find("ref:") == 0) {
        std::string refPath = headContent.substr(5); // Remove "ref: "
        // Trim whitespace
        refPath.erase(0, refPath.find_first_not_of(" \t\n\r"));
        refPath.erase(refPath.find_last_not_of(" \t\n\r") + 1);
        
        fs::path branchPath = repoPath / refPath;
        if (fs::exists(branchPath) && fs::file_size(branchPath) > 0) {
            std::ifstream branchFile(branchPath);
            std::string commitHash;
            std::getline(branchFile, commitHash);
            branchFile.close();
            return commitHash;
        }
    }
    
    return "";
}

void ada_commit(){
    try {
        // Define the .ada repository path
        fs::path repoPath = fs::current_path() / ".ada";

        // Check if .ada exists
        if (!fs::exists(repoPath)) {
            std::cerr << "Not an ada repository (or any of the parent directories)\n";
            return;
        }

        // Check if index file exists and has content
        fs::path indexPath = repoPath / "index";
        if (!fs::exists(indexPath) || fs::file_size(indexPath) == 0) {
            std::cerr << "Nothing to commit. Use 'ada add <file>' to stage changes.\n";
            return;
        }

        // Read the staging area (index)
        std::ifstream indexFile(indexPath);
        std::stringstream stagedFiles;
        std::string line;
        
        while (std::getline(indexFile, line)) {
            stagedFiles << line << "\n";
        }
        indexFile.close();

        if (stagedFiles.str().empty()) {
            std::cerr << "Nothing to commit. Use 'ada add <file>' to stage changes.\n";
            return;
        }

        // Get commit message from user
        std::cout << "Enter commit message: ";
        std::string commitMessage;
        std::getline(std::cin, commitMessage);

        if (commitMessage.empty()) {
            std::cerr << "Aborting commit due to empty commit message.\n";
            return;
        }

        // Get parent commit (if exists)
        std::string parentCommit = get_parent_commit(repoPath);

        // Create commit object content
        std::stringstream commitContent;
        commitContent << "tree " << "\n";
        
        if (!parentCommit.empty()) {
            commitContent << "parent " << parentCommit << "\n";
        }
        
        commitContent << "author ada-user <user@ada.local> " << get_current_timestamp() << "\n";
        commitContent << "committer ada-user <user@ada.local> " << get_current_timestamp() << "\n";
        commitContent << "\n";
        commitContent << commitMessage << "\n";
        commitContent << "\n";
        commitContent << "Files:\n";
        commitContent << stagedFiles.str();

        // Generate commit hash
        std::string commitHash = sha1_hash_commit(commitContent.str());

        // Store commit object
        fs::path commitObjectPath = repoPath / "objects" / commitHash;
        std::ofstream commitFile(commitObjectPath, std::ios::binary);
        commitFile << commitContent.str();
        commitFile.close();

        // Update the current branch reference
        fs::path headPath = repoPath / "HEAD";
        std::ifstream headFile(headPath);
        std::string headContent;
        std::getline(headFile, headContent);
        headFile.close();

        if (headContent.find("ref:") == 0) {
            std::string refPath = headContent.substr(5);
            refPath.erase(0, refPath.find_first_not_of(" \t\n\r"));
            refPath.erase(refPath.find_last_not_of(" \t\n\r") + 1);
            
            fs::path branchPath = repoPath / refPath;
            std::ofstream branchFile(branchPath, std::ios::trunc);
            branchFile << commitHash << "\n";
            branchFile.close();
        }

        // Append to commit log
        fs::path logPath = repoPath / "commits.log";
        std::ofstream logFile(logPath, std::ios::app);
        logFile << commitHash << " " << get_current_timestamp() << " " << commitMessage << "\n";
        logFile.close();

        // Clear the staging area
        fs::remove(indexPath);

        std::cout << "[main " << commitHash.substr(0, 7) << "] " << commitMessage << "\n";
        std::cout << "Commit created successfully.\n";

    } catch (const std::exception& ex) {
        std::cerr << "Error creating commit: " << ex.what() << std::endl;
    }
}
