#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "push.h"

namespace fs = std::filesystem;

std::string get_remote_path() {
    std::ifstream config(".ada/config");
    if (!config.is_open()) {
        std::cerr << "fatal: could not open .ada/config\n";
        exit(1);
    }

    std::string line, remote_path;
    while (std::getline(config, line)) {
        if (line.find("path") != std::string::npos) {
            size_t pos = line.find('=');
            if (pos != std::string::npos)
                remote_path = line.substr(pos + 1);
        }
    }

    if (remote_path.empty()) {
        std::cerr << "fatal: remote path not found in config\n";
        exit(1);
    }

    // trim spaces
    while (!remote_path.empty() && isspace(remote_path.front()))
        remote_path.erase(remote_path.begin());
    while (!remote_path.empty() && isspace(remote_path.back()))
        remote_path.pop_back();

    return remote_path;
}

void push() {
    std::string remote_path = get_remote_path();
    fs::path remote_repo = fs::path(remote_path);
    fs::path remote_objects = remote_repo / ".ada" / "objects";
    fs::path local_objects = ".ada/objects";

    if (!fs::exists(remote_repo / ".ada")) {
        std::cerr << "fatal: remote repository not initialized.\n";
        exit(1);
    }

    std::cout << "Pushing objects to " << remote_path << "...\n";

    // Copy missing objects
    for (auto& entry : fs::directory_iterator(local_objects)) {
        fs::path dest = remote_objects / entry.path().filename();
        if (!fs::exists(dest)) {
            fs::copy_file(entry.path(), dest);
            std::cout << "Copied object " << entry.path().filename().string() << "\n";
        }
    }

    // Update remote HEAD
    std::ifstream local_head(".ada/refs/heads/main");
    std::string head_hash;
    std::getline(local_head, head_hash);

    fs::create_directories(remote_repo / ".ada" / "refs" / "heads");
    std::ofstream remote_head(remote_repo / ".ada" / "refs" / "heads" / "main");
    remote_head << head_hash;

    std::cout << "Updated remote HEAD to " << head_hash << "\n";
    std::cout << "Push complete.\n";
}
