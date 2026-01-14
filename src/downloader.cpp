#include <iostream>
#include <ostream>
#include <atlas/downloader.h>

namespace atlas {
    void downloader(std::string url) {
        std::cout << "Downloading from url: " << url << std::endl;
        std::cout << "Finished downloading." << std::endl;
    }
}
