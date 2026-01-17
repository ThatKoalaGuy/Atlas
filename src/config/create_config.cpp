#define _CRT_SECURE_NO_WARNINGS
#include <filesystem>
#include <atlas/config/create_config.h>
#include <fstream>
#include <iosfwd>

namespace atlas {
    void create_config() {
        const std::filesystem::path path = "atlas.conf";

        // If config already exists, leave it alone
        if (std::filesystem::exists(path)) {
            return;
        }

        std::ofstream file(path);
        if (!file) {
            throw std::runtime_error("Failed to create config file");
        }

        file << "# Atlas config file\n";
        file << "download_dir=\n";

        std::exit(0);
    }
}
