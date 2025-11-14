#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <cryptlib.h>
#include <sha.h>
#include <hex.h>

namespace fs = std::filesystem;

// Hash function to check file content
std::string sha1_hash_status(const std::string &data) {
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

void ada_status() {
    try {
        fs::path repoPath = fs::current_path() / ".ada";
        fs::path indexPath = repoPath / "index";

        if (!fs::exists(repoPath)) {
            std::cerr << "Not an ada repository (or any of the parent directories)\n";
            return;
        }

        // Read staged files from index
        std::map<std::string, std::string> stagedFiles; // file -> hash
        if (fs::exists(indexPath) && fs::file_size(indexPath) > 0) {
            std::ifstream indexFile(indexPath);
            std::string line;
            while (std::getline(indexFile, line)) {
                std::istringstream iss(line);
                std::string file, hash;
                iss >> file >> hash;
                if (!file.empty()) {
                    stagedFiles[file] = hash;
                }
            }
            indexFile.close();
        }

        // Read committed files from last commit
        std::map<std::string, std::string> committedFiles; // file -> hash
        fs::path commitsLog = repoPath / "commits.log";
        
        if (fs::exists(commitsLog) && fs::file_size(commitsLog) > 0) {
            // Get the last commit hash
            std::ifstream logFile(commitsLog);
            std::string lastCommitLine;
            std::string line;
            while (std::getline(logFile, line)) {
                if (!line.empty()) {
                    lastCommitLine = line;
                }
            }
            logFile.close();
            
            if (!lastCommitLine.empty()) {
                std::istringstream iss(lastCommitLine);
                std::string commitHash;
                iss >> commitHash;
                
                // Read the commit object to get files
                fs::path commitObjPath = repoPath / "objects" / commitHash;
                if (fs::exists(commitObjPath)) {
                    std::ifstream commitFile(commitObjPath);
                    std::string commitLine;
                    bool inFilesSection = false;
                    
                    while (std::getline(commitFile, commitLine)) {
                        if (commitLine == "Files:") {
                            inFilesSection = true;
                            continue;
                        }
                        if (inFilesSection && !commitLine.empty()) {
                            std::istringstream fiss(commitLine);
                            std::string file, hash;
                            fiss >> file >> hash;
                            if (!file.empty() && !hash.empty()) {
                                committedFiles[file] = hash;
                            }
                        }
                    }
                    commitFile.close();
                }
            }
        }

        // Collect all working directory files
        std::map<std::string, std::string> workingFiles; // file -> hash
        for (const auto& entry : fs::recursive_directory_iterator(fs::current_path())) {
            if (entry.is_regular_file()) {
                std::string relPath = fs::relative(entry.path(), fs::current_path()).string();
                
                // Skip .ada directory
                if (relPath.find(".ada") == 0 || relPath.find("/.ada") != std::string::npos) {
                    continue;
                }
                
                // Calculate hash of file
                std::ifstream file(entry.path(), std::ios::binary);
                std::string content((std::istreambuf_iterator<char>(file)), 
                                   std::istreambuf_iterator<char>());
                file.close();
                
                std::string hash = sha1_hash_status(content);
                workingFiles[relPath] = hash;
            }
        }

        // Categorize files
        std::set<std::string> stagedNew;
        std::set<std::string> stagedModified;
        std::set<std::string> modified;
        std::set<std::string> untracked;
        std::set<std::string> deleted;

        // Check staged files - are they new or modified?
        for (const auto& [file, hash] : stagedFiles) {
            if (committedFiles.find(file) != committedFiles.end()) {
                // File exists in last commit, so it's a modification
                stagedModified.insert(file);
            } else {
                // File doesn't exist in last commit, so it's new
                stagedNew.insert(file);
            }
        }

        // Check working files
        for (const auto& [file, hash] : workingFiles) {
            if (stagedFiles.find(file) != stagedFiles.end()) {
                // File is staged - already handled above
                continue;
            } else if (committedFiles.find(file) != committedFiles.end()) {
                // File was committed - check if modified
                if (committedFiles[file] != hash) {
                    modified.insert(file);
                }
                // else: file is unchanged from last commit
            } else {
                // File is untracked
                untracked.insert(file);
            }
        }

        // Check for deleted files
        for (const auto& [file, hash] : committedFiles) {
            if (workingFiles.find(file) == workingFiles.end() && 
                stagedFiles.find(file) == stagedFiles.end()) {
                deleted.insert(file);
            }
        }

        // Display status
        std::cout << "On branch main\n";

        if (!stagedNew.empty() || !stagedModified.empty()) {
            std::cout << "\nChanges to be committed:\n";
            std::cout << "  (use \"ada commit\" to commit)\n\n";
            for (const auto& file : stagedNew) {
                std::cout << "    new file:   " << file << "\n";
            }
            for (const auto& file : stagedModified) {
                std::cout << "    modified:   " << file << "\n";
            }
        }

        if (!modified.empty()) {
            std::cout << "\nChanges not staged for commit:\n";
            std::cout << "  (use \"ada add <file>\" to update what will be committed)\n\n";
            for (const auto& file : modified) {
                std::cout << "    modified:   " << file << "\n";
            }
        }

        if (!deleted.empty()) {
            std::cout << "\nDeleted files:\n";
            for (const auto& file : deleted) {
                std::cout << "    deleted:    " << file << "\n";
            }
        }

        if (!untracked.empty()) {
            std::cout << "\nUntracked files:\n";
            std::cout << "  (use \"ada add <file>\" to include in what will be committed)\n\n";
            for (const auto& file : untracked) {
                std::cout << "    " << file << "\n";
            }
        }

        if (stagedNew.empty() && stagedModified.empty() && modified.empty() && untracked.empty() && deleted.empty()) {
            std::cout << "\nnothing to commit, working tree clean\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error checking status: " << ex.what() << std::endl;
    }
}
