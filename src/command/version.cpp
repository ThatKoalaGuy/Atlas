#include <cstdlib>
#include <iostream>
#include <atlas/command/version.h>

namespace atlas {
    void version() {
        std::cout << "Current version: \n"
                "v1.0.0-alpha";
        std::exit(0);
    }
}
