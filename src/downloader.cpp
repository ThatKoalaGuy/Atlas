#include <filesystem>
#include <atlas/downloader.h>
#include <atlas/write_data.h>
#include <atlas/filename_from_url.h>
#include <curl/curl.h>

namespace atlas {
    std::string filename_from_url(const std::string &url) {
        // strip scheme
        std::string clean = url;
        if (const auto pos = clean.find("://"); pos != std::string::npos) {
            clean = clean.substr(pos + 3);
        }

        // remove query / fragment
        if (const auto pos = clean.find_first_of("?#"); pos != std::string::npos) {
            clean = clean.substr(0, pos);
        }

        // if path exists, use the last path segment
        auto slash = clean.find('/');
        if (slash == std::string::npos) {
            // only hostname → root
            return "index.html";
        }

        std::string path = clean.substr(slash);
        if (path == "/" || path.empty()) {
            return "index.html";
        }

        std::string name = path.substr(path.find_last_of('/') + 1);
        if (name.empty()) {
            return "index.html";
        }

        return name;
    }

    void downloader(const std::string &url) {
        CURL *curl = curl_easy_init();
        if (!curl) {
            throw std::runtime_error("curl_easy_init failed");
        }

        const std::string filename = filename_from_url(url);

        FILE *fp = fopen(filename.c_str(), "wb");
        if (!fp) {
            curl_easy_cleanup(curl);
            throw std::runtime_error("failed to open file for writing");
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &atlas::write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        const CURLcode res = curl_easy_perform(curl);

        fclose(fp);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::filesystem::remove(filename);
            throw std::runtime_error(curl_easy_strerror(res));
        }
    }
}
