#include "utility/config_file_parser/config_file_parser.hpp"

#include <iostream>

int main() {
    // Initialize configuration with config logic
    Configuration::SectionKeyPairToConfigLogic config_logic = {
        {{"server", "port"},
         [](const std::string &value) {
             int port = std::stoi(value);
             std::cout << "Setting server port to: " << port << std::endl;
         }},
        {{"database", "connection_string"},
         [](const std::string &value) { std::cout << "Setting database connection to: " << value << std::endl; }}};

    Configuration config("config.ini", config_logic);

    // Read existing values
    auto port = config.get_value("server", "port");
    if (port) {
        std::cout << "Current port: " << *port << std::endl;
    }

    // Modify configuration live
    config.set_value("server", "port",
                     "8080");                           // This will also apply the config logic
    config.set_value("server", "host", "localhost");    // New key-value pair
    config.set_value("features", "debug_mode", "true"); // New section and key

    // Query configuration
    if (config.has_section("server")) {
        auto keys = config.get_keys("server");
        std::cout << "Server section keys: ";
        for (const auto &key : keys) {
            std::cout << key << " ";
        }
        std::cout << std::endl;
    }

    // Save changes to file
    if (config.save_to_file()) {
        std::cout << "Configuration saved successfully!" << std::endl;
    }

    // Backup before making risky changes
    config.backup_config("config.ini.backup");

    // Make some changes and save to a different file
    config.set_value("experimental", "new_feature", "enabled");
    config.save_to_file("config_modified.ini");

    config.apply_config_logic();

    return 0;
}
