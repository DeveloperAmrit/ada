#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "pull.h"
#include "push.h"  // for get_remote_path()

namespace fs = std::filesystem;

void pull() {
    std::string remote_path = get_remote_path();
    fs::path remote_repo = fs::path(remote_path);
    fs::path remote_objects = remote_repo / ".ada" / "objects";
    fs::path local_objects = ".ada/objects";

    if (!fs::exists(remote_repo / ".ada")) {
        std::cerr << "fatal: remote repository not initialized.\n";
        exit(1);
    }

    std::cout << "Pulling objects from " << remote_path << "...\n";

    // Copy missing objects from remote
    for (auto& entry : fs::directory_iterator(remote_objects)) {
        fs::path dest = local_objects / entry.path().filename();
        if (!fs::exists(dest)) {
            fs::copy_file(entry.path(), dest);
            std::cout << "Fetched object " << entry.path().filename().string() << "\n";
        }
    }

    // Read HEADs
    std::ifstream local_head_file(".ada/refs/heads/main");
    std::ifstream remote_head_file(remote_repo / ".ada" / "refs" / "heads" / "main");
    if (!local_head_file.is_open() || !remote_head_file.is_open()) {
        std::cerr << "fatal: could not open HEAD file.\n";
        exit(1);
    }

    std::string local_head, remote_head;
    std::getline(local_head_file, local_head);
    std::getline(remote_head_file, remote_head);

    // If same -> up-to-date
    if (local_head == remote_head) {
        std::cout << "Already up to date.\n";
        return;
    }

    // Check if remote commit object exists locally
    fs::path remote_commit_obj = local_objects / remote_head;
    fs::path local_commit_obj = local_objects / local_head;

    bool remote_exists = fs::exists(remote_commit_obj);
    bool local_exists = fs::exists(local_commit_obj);

    if (remote_exists && local_exists) {
        // Divergence detected — require merge
        std::cout << "warning: divergent branches detected.\n";
        std::cout << "Local HEAD:  " << local_head << "\n";
        std::cout << "Remote HEAD: " << remote_head << "\n";
        std::cout << "Please run `ada merge` to resolve.\n";
        return;
    }

    // If remote is ahead, fast-forward
    if (remote_exists && !local_exists) {
        std::ofstream new_head(".ada/refs/heads/main");
        new_head << remote_head;
        std::cout << "Fast-forwarded to remote HEAD " << remote_head << "\n";
    } else {
        std::cout << "Could not determine relation between heads — manual merge required.\n";
    }

    std::cout << "Pull complete.\n";
}