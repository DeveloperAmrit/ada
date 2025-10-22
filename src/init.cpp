#include <iostream>
#include <fstream>
#include <filesystem>  // For filesystem manipulation (C++17 feature)
#include "init.h"

namespace fs = std::filesystem;

void ada_init() {
    try {
        // Define the .ada repository path
        fs::path repoPath = fs::current_path() / ".ada";

        // If .ada already exists, show message and return
        if (fs::exists(repoPath)) {
            std::cout << "Reinitialized existing ada repository in " << repoPath.string() << std::endl;
            return;
        }

        // Create the necessary directories
        fs::create_directories(repoPath / "objects");
        fs::create_directories(repoPath / "refs" / "heads");
        fs::create_directories(repoPath / "refs" / "tags");

        // Write the HEAD file to point to refs/heads/main (default branch)
        {
            std::ofstream headFile(repoPath / "HEAD", std::ios::out | std::ios::binary);
            if (!headFile) throw std::runtime_error("Failed to create HEAD file");
            headFile << "ref: refs/heads/main\n";
        }

        // Create the main branch file (refs/heads/main) — empty for now
        {
            std::ofstream branchFile(repoPath / "refs" / "heads" / "main", std::ios::out | std::ios::binary);
            if (!branchFile) throw std::runtime_error("Failed to create refs/heads/main");
        }

        // Optional config file for repo settings
        {
            std::ofstream configFile(repoPath / "config", std::ios::out | std::ios::binary);
            if (!configFile) throw std::runtime_error("Failed to create config file");
            configFile << "[core]\n";
            configFile << "\trepositoryformatversion = 0\n";
            configFile << "\tfilemode = false\n";
            configFile << "\tbare = false\n";
            configFile << "\tlogallrefupdates = true\n";
        }

        // Optional description file
        {
            std::ofstream descFile(repoPath / "description", std::ios::out | std::ios::binary);
            if (!descFile) throw std::runtime_error("Failed to create description file");
            descFile << "Unnamed repository; edit this file to name the repository.\n";
        }

        // Success message
        std::cout << "Initialized empty ada repository in " << repoPath.string() << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error initializing repository: " << ex.what() << std::endl;
    }
}
