#include <iostream>
#include <atlas/Parser.h>

int main(const int argc, char **argv) {
    std::cout << "Welcome to Atlas!" << std::endl;

    atlas::parser(argc, argv);

    return 0;
}
