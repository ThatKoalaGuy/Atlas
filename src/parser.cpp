#include <iostream>
#include <ostream>
#include <atlas/parser.h>

namespace atlas {
    //argc will be used later, do not delete!
    void parser(const int argc, char *argv[]) {
        const std::string url = argv[1];
        std::cout << url << std::endl;
    }
}
