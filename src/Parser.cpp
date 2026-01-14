#include <iostream>
#include <ostream>
#include <atlas/Parser.h>

namespace atlas {
    void parser(const int argc, char *argv[]) {
        if (argc == 1)
            std::cout << "You must provide at least one argument." << std::endl;
        else {
            const std::string url = argv[1];
            std::cout << url << std::endl;
        }
    }
}
