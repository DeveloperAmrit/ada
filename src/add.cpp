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
#include "add.h"

namespace fs = std::filesystem;

std::string sha1_hash(const std::string &data) {
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

// Helper function to add a single file
void add_single_file(const std::string &filePath, const fs::path &repoPath) {
    fs::path targetFile = fs::current_path() / filePath;
    
    // Skip if file doesn't exist or is a directory
    if (!fs::exists(targetFile) || fs::is_directory(targetFile)) {
        return;
    }

    std::ifstream inFile(targetFile, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Warning: Could not open file: " << filePath << "\n";
        return;
    }
    
    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();
    
    std::string objectHash = sha1_hash(content);

    fs::path objectPath = repoPath / "objects" / objectHash;
    std::ofstream outFile(objectPath, std::ios::binary);
    outFile << content;
    outFile.close();

    // Read existing index
    std::set<std::string> indexedFiles;
    std::map<std::string, std::string> fileHashes;
    fs::path indexPath = repoPath / "index";
    
    if (fs::exists(indexPath)) {
        std::ifstream existingIndex(indexPath);
        std::string line;
        while (std::getline(existingIndex, line)) {
            std::istringstream iss(line);
            std::string file, hash;
            iss >> file >> hash;
            indexedFiles.insert(file);
            fileHashes[file] = hash;
        }
        existingIndex.close();
    }

    // Update or add the file
    if (indexedFiles.find(filePath) != indexedFiles.end()) {
        // File already staged, update the hash
        std::ifstream oldIndex(indexPath);
        std::ofstream tempIndex(repoPath / "index.tmp");
        std::string line;
        while (std::getline(oldIndex, line)) {
            std::istringstream iss(line);
            std::string file, hash;
            iss >> file >> hash;
            if (file == filePath) {
                tempIndex << filePath << " " << objectHash << "\n";
            } else {
                tempIndex << line << "\n";
            }
        }
        oldIndex.close();
        tempIndex.close();
        fs::remove(indexPath);
        fs::rename(repoPath / "index.tmp", indexPath);
    } else {
        // Add new file
        std::ofstream indexFile(indexPath, std::ios::app);
        indexFile << filePath << " " << objectHash << "\n";
        indexFile.close();
    }

    std::cout << "Added " << filePath << "\n";
}

void ada_add(const std::string &filePath){
    // Define the .ada repository path
    fs::path repoPath = fs::current_path() / ".ada";

    // If .ada doesn't exist, return
    if (!fs::exists(repoPath)) {
        std::cerr << "Not an ada repository (or any of the parent directories)\n";
        return;
    }

    // Handle "ada add ." - add all files
    if (filePath == ".") {
        std::cout << "Adding all files in current directory...\n";
        int fileCount = 0;
        
        // Recursively iterate through all files
        for (const auto& entry : fs::recursive_directory_iterator(fs::current_path())) {
            if (entry.is_regular_file()) {
                // Get relative path
                std::string relPath = fs::relative(entry.path(), fs::current_path()).string();
                
                // Skip .ada directory and its contents
                if (relPath.find(".ada") == 0 || relPath.find("/.ada") != std::string::npos) {
                    continue;
                }
                
                // Skip hidden files (except if explicitly added)
                if (relPath[0] == '.') {
                    continue;
                }
                
                add_single_file(relPath, repoPath);
                fileCount++;
            }
        }
        
        if (fileCount == 0) {
            std::cout << "No files to add.\n";
        } else {
            std::cout << "Added " << fileCount << " file(s) to staging area.\n";
        }
        return;
    }

    // Handle single file or directory
    fs::path targetFile = fs::current_path() / filePath;
    if (!fs::exists(targetFile)) {
        std::cerr << "File does not exist: " << filePath << "\n";
        return;
    }

    // If it's a directory, add all files in it recursively
    if (fs::is_directory(targetFile)) {
        std::cout << "Adding all files in directory: " << filePath << "\n";
        int fileCount = 0;
        
        for (const auto& entry : fs::recursive_directory_iterator(targetFile)) {
            if (entry.is_regular_file()) {
                std::string relPath = fs::relative(entry.path(), fs::current_path()).string();
                
                // Skip .ada directory
                if (relPath.find(".ada") == 0 || relPath.find("/.ada") != std::string::npos) {
                    continue;
                }
                
                add_single_file(relPath, repoPath);
                fileCount++;
            }
        }
        
        if (fileCount == 0) {
            std::cout << "No files found in directory.\n";
        } else {
            std::cout << "Added " << fileCount << " file(s) from directory.\n";
        }
        return;
    }

    // Single file - use the helper function
    add_single_file(filePath, repoPath);
}
