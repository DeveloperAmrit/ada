#include <iostream>
#include <fstream>
#include <filesystem>
#include <filesystem>
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

void ada_add(const std::string &filePath){  //Parameter is the path of given file.
    // Define the .ada repository path
    fs::path repoPath = fs::current_path() / ".ada";

    // If .ada doesn't exist, return
    if (!fs::exists(repoPath)) {
        std::cerr << "Not an ada repository (or any of the parent directories)\n";
        return;
    }

    // If file doesn't exist, return
    fs::path targetFile = fs::current_path() / filePath;
    if (!fs::exists(targetFile)) {
        std::cerr << "File does not exist: " << filePath << "\n";
        return;
    }

    std::ifstream inFile(targetFile, std::ios::binary); // Open the target file in binary mode for reading raw bytes.
    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>()); // Read the entire file content (byte by byte) into the string 'content'.
    std::string objectHash = sha1_hash(content); // implement a simple hash or use SHA1 library

    fs::path objectPath = repoPath / "objects" / objectHash; // Build the full path for storing the file object inside '.ada/objects/<hash>'.
    std::ofstream outFile(objectPath, std::ios::binary); // Create a new file at the object path for writing in binary mode.
    outFile << content; // Write the file's original content into the new object file.

    // Open the staging (index) file in append mode to record added files.
    std::ofstream indexFile(repoPath / "index", std::ios::app);
    indexFile << filePath << " " << objectHash << "\n"; //marking it as staged for commit.

    std::cout << "Added " << filePath << " to staging area.\n";
}