#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <ctime>
#include "merge.h"
#include "push.h"  // for get_remote_path()
#include "commit.h" // for sha1_hash_commit if needed

namespace fs = std::filesystem;

// Utility to read the content of a file safely
std::string read_file(const fs::path &path) {
    std::ifstream in(path);
    if (!in.is_open()) return "";
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

// Utility to write content to a file safely
void write_file(const fs::path &path, const std::string &content) {
    std::ofstream out(path);
    out << content;
}

// Detects file conflict (basic — compares entire file)
bool has_conflict(const std::string &local, const std::string &remote) {
    return (local != remote);
}

// Simple merge algorithm (adds conflict markers if needed)
std::string merge_content(const std::string &local, const std::string &remote) {
    if (local == remote)
        return local;

    return "<<<<<<< LOCAL VERSION\n" + local +
           "\n=======\n" + remote +
           "\n>>>>>>> REMOTE VERSION\n";
}

void merge() {
    std::string remote_path = get_remote_path();
    fs::path remote_repo = fs::path(remote_path);

    // Paths
    fs::path local_head_path = ".ada/refs/heads/main";
    fs::path remote_head_path = remote_repo / ".ada/refs/heads/main";
    fs::path objects_dir = ".ada/objects";

    if (!fs::exists(local_head_path) || !fs::exists(remote_head_path)) {
        std::cerr << "fatal: missing HEAD references.\n";
        exit(1);
    }

    // Read both HEADs
    std::string local_head = read_file(local_head_path);
    std::string remote_head = read_file(remote_head_path);

    if (local_head == remote_head) {
        std::cout << "Already up to date — nothing to merge.\n";
        return;
    }

    std::cout << "Merging branches...\n";
    std::cout << "Local:  " << local_head << "\n";
    std::cout << "Remote: " << remote_head << "\n";

    // For now, merge only tracked files in current directory (non-.ada)
    bool conflict_found = false;
    for (auto &entry : fs::directory_iterator(".")) {
        if (entry.path().string().find(".ada") != std::string::npos) continue;

        fs::path local_file = entry.path();
        fs::path remote_file = remote_repo / entry.path().filename();

        if (!fs::exists(remote_file)) continue;

        std::string local_content = read_file(local_file);
        std::string remote_content = read_file(remote_file);

        if (has_conflict(local_content, remote_content)) {
            std::string merged_content = merge_content(local_content, remote_content);
            write_file(local_file, merged_content);
            conflict_found = true;
            std::cout << "Conflict in file: " << local_file.filename().string() << "\n";
        }
    }

    // Create a new merge commit object
    std::string merge_message;
    if (conflict_found)
        merge_message = "Merge with conflicts between " + local_head.substr(0, 7) + " and " + remote_head.substr(0, 7);
    else
        merge_message = "Merged successfully between " + local_head.substr(0, 7) + " and " + remote_head.substr(0, 7);

    // Timestamp
    std::time_t now = std::time(nullptr);
    std::string date = std::ctime(&now);
    date.pop_back(); // remove trailing newline

    std::string commit_data = "merge " + local_head + " " + remote_head + "\nDate: " + date + "\n\n" + merge_message;
    std::string merge_hash = sha1_hash_commit(commit_data);

    // Store merge commit object
    std::ofstream merge_obj(objects_dir / merge_hash);
    merge_obj << commit_data;
    merge_obj.close();

    // Update HEAD
    std::ofstream head_out(local_head_path);
    head_out << merge_hash;

    if (conflict_found)
        std::cout << "Merge completed with conflicts. Resolve them manually in the files.\n";
    else
        std::cout << "Merge completed cleanly.\n";

    std::cout << "Created merge commit " << merge_hash.substr(0, 7) << "\n";
}