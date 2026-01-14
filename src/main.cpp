#include <iostream>
#include <atlas/parser.h>

#include "atlas/downloader.h"

int main(const int argc, char **argv) {
    std::cout << "Welcome to Atlas!" << std::endl;

    try {
        if (argc < 2) {
            throw std::invalid_argument("Usage: atlas <url>");
        }

        const std::string url = atlas::parser(argc, argv);
        atlas::downloader(url);

        return 0;
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 99;
    }
}
