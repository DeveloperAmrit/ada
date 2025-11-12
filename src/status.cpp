#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <set>
#include <sstream>

namespace fs = std::filesystem;

void ada_status() {
    try {
        fs::path repoPath = fs::current_path() / ".ada";
        fs::path indexPath = repoPath / "index";

        if (!fs::exists(repoPath)) {
            std::cerr << "Not an ada repository (or any of the parent directories)\n";
            return;
        }

        std::set<std::string> stagedFiles;

        // Read staged files from index
        if (fs::exists(indexPath) && fs::file_size(indexPath) > 0) {
            std::ifstream indexFile(indexPath);
            std::string line;
            while (std::getline(indexFile, line)) {
                if (!line.empty()) stagedFiles.insert(line);
            }
            indexFile.close();
        }

        std::set<std::string> workingFiles;

        // Collect all working directory files except .ada folder
        for (const auto& entry : fs::recursive_directory_iterator(fs::current_path())) {
            if (entry.is_regular_file()) {
                std::string relPath = fs::relative(entry.path(), fs::current_path()).string();
                if (relPath.rfind(".ada", 0) == 0) continue; // skip repo files
                workingFiles.insert(relPath);
            }
        }

        std::set<std::string> unstaged;
        std::set<std::string> untracked;

        // Determine unstaged and untracked files
        for (const auto& file : workingFiles) {
            if (stagedFiles.find(file) == stagedFiles.end()) {
                untracked.insert(file);
            }
        }

        for (const auto& file : stagedFiles) {
            if (workingFiles.find(file) == workingFiles.end()) {
                unstaged.insert(file);
            }
        }

        std::cout << "On branch main\n";

        if (!stagedFiles.empty()) {
            std::cout << "\nChanges to be committed:\n";
            for (const auto& file : stagedFiles) {
                std::cout << "    " << file << "\n";
            }
        }

        if (!unstaged.empty()) {
            std::cout << "\nChanges staged but missing from working directory:\n";
            for (const auto& file : unstaged) {
                std::cout << "    " << file << "\n";
            }
        }

        if (!untracked.empty()) {
            std::cout << "\nUntracked files:\n";
            for (const auto& file : untracked) {
                std::cout << "    " << file << "\n";
            }
        }

        if (stagedFiles.empty() && untracked.empty()) {
            std::cout << "\nNothing to commit, working tree clean.\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error checking status: " << ex.what() << std::endl;
    }
}
