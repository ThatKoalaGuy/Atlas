#ifndef ATLAS_READ_CONFIG_H
#define ATLAS_READ_CONFIG_H
#include <string>

namespace atlas {
    struct Config {
        std::string download_dir;
    };

    Config read_config();
}

#endif //ATLAS_READ_CONFIG_H