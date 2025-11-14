#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

class Config {
public:
    // Get global config instance
    static Config& getInstance();
    
    // Set a configuration value
    void set(const std::string& key, const std::string& value, bool global = false);
    
    // Get a configuration value
    std::string get(const std::string& key, bool global = false);
    
    // List all configuration
    void list(bool global = false);
    
    // Get global config path (~/.ada/config)
    std::string getGlobalConfigPath();
    
    // Get local config path (./.ada/config)
    std::string getLocalConfigPath();

private:
    Config() = default;
    ~Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    
    // Load config from file
    std::map<std::string, std::string> loadConfig(const std::string& path);
    
    // Save config to file
    void saveConfig(const std::string& path, const std::map<std::string, std::string>& config);
};

// Command function for 'ada config'
void ada_config(int argc, char* argv[]);

#endif // CONFIG_H
