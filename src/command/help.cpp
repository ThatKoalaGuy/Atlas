#include <iostream>
#include <ostream>
#include <atlas/command/help.h>
namespace atlas {
    void help() {
        std::cout <<
        "Usage: \n"
        "   atlas [OPTIONS] <URL> \n\n"
        

        "Options: \n"
        "   -h --help       show this screen \n"
        "   -v --version       Show version \n"
        "Examples: \n"
        "    \n"
        ;
    }
}