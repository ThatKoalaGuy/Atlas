#include <iostream>
#include <ostream>
#include <atlas/downloader.h>
#include <curl/curl.h>

namespace atlas {
    void downloader(const std::string &url) {
        curl_global_init(CURL_GLOBAL_ALL);
        CURL *curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_perform(curl);
        }
    }
}
