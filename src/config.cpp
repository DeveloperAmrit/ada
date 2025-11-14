#include "config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

std::string Config::getGlobalConfigPath() {
    const char* home = std::getenv("HOME");
    if (!home) {
        throw std::runtime_error("HOME environment variable not set");
    }
    return std::string(home) + "/.ada/config";
}

std::string Config::getLocalConfigPath() {
    return fs::current_path().string() + "/.ada/config";
}

std::map<std::string, std::string> Config::loadConfig(const std::string& path) {
    std::map<std::string, std::string> config;
    
    if (!fs::exists(path)) {
        return config;
    }
    
    std::ifstream file(path);
    std::string line;
    
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;
        
        // Parse key=value
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            
            // Trim whitespace
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            
            config[key] = value;
        }
    }
    
    return config;
}

void Config::saveConfig(const std::string& path, const std::map<std::string, std::string>& config) {
    // Create directory if it doesn't exist
    fs::path configPath(path);
    fs::create_directories(configPath.parent_path());
    
    std::ofstream file(path, std::ios::trunc);
    if (!file) {
        throw std::runtime_error("Failed to open config file for writing: " + path);
    }
    
    file << "# Ada Configuration File\n";
    file << "# Format: key=value\n\n";
    
    for (const auto& [key, value] : config) {
        file << key << "=" << value << "\n";
    }
}

void Config::set(const std::string& key, const std::string& value, bool global) {
    std::string configPath = global ? getGlobalConfigPath() : getLocalConfigPath();
    
    // Check if local repo exists when setting local config
    if (!global && !fs::exists(getLocalConfigPath())) {
        fs::path repoPath = fs::current_path() / ".ada";
        if (!fs::exists(repoPath)) {
            std::cerr << "Not an ada repository. Use --global for global config.\n";
            return;
        }
    }
    
    auto config = loadConfig(configPath);
    config[key] = value;
    saveConfig(configPath, config);
    
    std::cout << "Set " << key << " = " << value;
    if (global) std::cout << " (global)";
    std::cout << "\n";
}

std::string Config::get(const std::string& key, bool global) {
    std::string configPath = global ? getGlobalConfigPath() : getLocalConfigPath();
    auto config = loadConfig(configPath);
    
    if (config.find(key) != config.end()) {
        return config[key];
    }
    
    // If not found in local, try global
    if (!global) {
        configPath = getGlobalConfigPath();
        config = loadConfig(configPath);
        if (config.find(key) != config.end()) {
            return config[key];
        }
    }
    
    return "";
}

void Config::list(bool global) {
    std::string configPath = global ? getGlobalConfigPath() : getLocalConfigPath();
    auto config = loadConfig(configPath);
    
    if (config.empty()) {
        std::cout << "No configuration found";
        if (global) std::cout << " (global)";
        std::cout << "\n";
        return;
    }
    
    std::cout << "Configuration";
    if (global) std::cout << " (global)";
    std::cout << ":\n";
    
    for (const auto& [key, value] : config) {
        std::cout << "  " << key << " = " << value << "\n";
    }
}

void ada_config(int argc, char* argv[]) {
    Config& config = Config::getInstance();
    
    // ada config --list or ada config --global --list
    bool globalFlag = false;
    bool listFlag = false;
    
    // Parse flags
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--global") {
            globalFlag = true;
        } else if (arg == "--list" || arg == "-l") {
            listFlag = true;
        }
    }
    
    if (listFlag) {
        config.list(globalFlag);
        return;
    }
    
    // ada config <key> <value>
    // ada config --global <key> <value>
    int keyIdx = 2;
    if (globalFlag) keyIdx = 3;
    
    if (argc < keyIdx + 2) {
        std::cout << "Usage:\n";
        std::cout << "  ada config <key> <value>           Set local config\n";
        std::cout << "  ada config --global <key> <value>  Set global config\n";
        std::cout << "  ada config --list                  List local config\n";
        std::cout << "  ada config --global --list         List global config\n";
        std::cout << "\nCommon keys:\n";
        std::cout << "  user.name        Your name\n";
        std::cout << "  user.email       Your email\n";
        std::cout << "  github.token     GitHub personal access token\n";
        std::cout << "  github.username  GitHub username\n";
        return;
    }
    
    std::string key = argv[keyIdx];
    std::string value = argv[keyIdx + 1];
    
    config.set(key, value, globalFlag);
}
