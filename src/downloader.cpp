#include <filesystem>
#include <iostream>
#include <atlas/downloader.h>
#include <atlas/write_data.h>
#include <curl/curl.h>

namespace atlas {
    void downloader(const std::string &url) {
        if (CURL *curl = curl_easy_init()) {
            //std::filesystem::create_directory("output");
            if (FILE *fp = fopen("datoteka.html", "wb"); !fp) {
                curl_easy_cleanup(curl);
                throw std::runtime_error("failed to open file for writing");
            } else {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &atlas::write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

                const CURLcode res = curl_easy_perform(curl);

                fclose(fp);
                curl_easy_cleanup(curl);

                if (res != CURLE_OK) {
                    throw std::runtime_error(curl_easy_strerror(res));
                }
            }
        }
    }
}
