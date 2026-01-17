#include <fstream>
#include <atlas/config/read_config.h>

namespace atlas {
    Config read_config() {
        const std::string path = "atlas.conf";
        std::ifstream file(path);

        Config config;
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#')
                continue;

            const auto pos = line.find('=');
            if (pos == std::string::npos)
                continue;

            const std::string key = line.substr(0, pos);
            const std::string value = line.substr(pos + 1);

            if (key == "download_dir") {
                config.download_dir = value;
            }
        }

        return config;
    }
}
