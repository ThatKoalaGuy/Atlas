#include <iostream>
#include <ostream>
#include <atlas/parser.h>
#include <atlas/command/help.h>

namespace atlas {
    //argc will be used later, do not delete!
    void parser(const int argc, char *argv[]) {
        if (argc != 2) {
            std::cout <<"Invalid usage, write atlas --help to help."<< std::endl;
        }
        else {
            if (argv[1] == "--help"|| argv[1] == "-h") {
                atlas::help();
            }
            else if (argv[1] == "--version" || argv[1] == "-v") {
                std::cout << "Current version: \n"
                "v1.0.0-alpha";
            }
        }



    }
}
