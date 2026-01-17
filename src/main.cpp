#include <iostream>
#include <atlas/parser.h>
#include <curl/curl.h>
#include <atlas/downloader.h>

#include "atlas/command/help.h"

int main(const int argc, char **argv) {
    std::cout << "Welcome to Atlas!" << std::endl;
    curl_global_init(CURL_GLOBAL_ALL);

    try {
        if (argc < 2) {
            atlas::help();
            throw std::invalid_argument("No parameters provided");
        }

        const std::string url = atlas::parser(argc, argv);
        atlas::downloader(url);

        curl_global_cleanup();
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
