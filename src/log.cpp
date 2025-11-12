#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

namespace fs = std::filesystem;

struct CommitEntry {
    std::string hash;
    std::string timestamp;
    std::string message;
};

// Function to split a line like: "<hash> | <timestamp> | <message>"
CommitEntry parse_commit_line(const std::string& line) {
    CommitEntry entry;
    std::stringstream ss(line);
    ss >> entry.hash >> entry.timestamp; // reads hash and first part of timestamp (date)
    std::string time_part;
    ss >> time_part;                      // reads the time part
    entry.timestamp += " " + time_part;   // combine date and time
    std::getline(ss, entry.message);      // rest is the message


    // Trim whitespace
    auto trim = [](std::string& s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        size_t end = s.find_last_not_of(" \t\r\n");
        if (start == std::string::npos || end == std::string::npos) {
            s.clear();
        } else {
            s = s.substr(start, end - start + 1);
        }
    };

    trim(entry.hash);
    trim(entry.timestamp);
    trim(entry.message);
    return entry;
}

void ada_log() {
    try {
        fs::path repoPath = fs::current_path() / ".ada";
        fs::path logPath = repoPath / "commits.log";

        if (!fs::exists(repoPath)) {
            std::cerr << "Not an ada repository (or any of the parent directories)\n";
            return;
        }

        if (!fs::exists(logPath) || fs::file_size(logPath) == 0) {
            std::cout << "No commits yet.\n";
            return;
        }

        std::ifstream logFile(logPath);
        std::vector<CommitEntry> commits;
        std::string line;

        while (std::getline(logFile, line)) {
            if (!line.empty()) {
                commits.push_back(parse_commit_line(line));
            }
        }
        logFile.close();

        // Display from latest to oldest
        for (auto it = commits.rbegin(); it != commits.rend(); ++it) {
            std::cout << "commit " << it->hash << "\n";
            std::cout << "Date:   " << it->timestamp << "\n";
            std::cout << "\n    " << it->message << "\n\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error reading log: " << ex.what() << std::endl;
    }
}
