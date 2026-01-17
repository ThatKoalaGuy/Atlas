#define _CRT_SECURE_NO_WARNINGS

#include <filesystem>
#include <iostream>
#include <stdexcept>

#include <atlas/downloader.h>
#include <atlas/write_data.h>
#include <atlas/config/read_config.h>
#include <atlas/filename_from_url.h>

#include <curl/curl.h>

namespace atlas {
    std::string filename_from_url(const std::string &url) {
        std::string clean = url;

        if (const auto pos = clean.find("://"); pos != std::string::npos) {
            clean = clean.substr(pos + 3);
        }

        if (const auto pos = clean.find_first_of("?#"); pos != std::string::npos) {
            clean = clean.substr(0, pos);
        }

        const auto slash = clean.find('/');
        if (slash == std::string::npos) {
            return "index.html";
        }

        const std::string path = clean.substr(slash);
        if (path == "/" || path.empty()) {
            return "index.html";
        }

        const std::string name = path.substr(path.find_last_of('/') + 1);
        return name.empty() ? "index.html" : name;
    }

    void downloader(const std::string &url) {
        CURL *curl = curl_easy_init();
        if (!curl) {
            throw std::runtime_error("curl_easy_init failed");
        }

        const auto base = filename_from_url(url);

        // Decide output directory
        std::filesystem::path output_dir;
        try {
            const auto &cfg = read_config();
            if (!cfg.download_dir.empty()) {
                output_dir = cfg.download_dir;
            }
        } catch (...) {
            // No config file → fall back to executable directory
        }

        if (output_dir.empty()) {
            output_dir = std::filesystem::current_path();
        }

        std::filesystem::path output = output_dir / base;

        std::filesystem::create_directories(output.parent_path());

        std::cout << "Saved to: " << output << std::endl;

        FILE *fp = fopen(output.string().c_str(), "wb");
        if (!fp) {
            curl_easy_cleanup(curl);
            throw std::runtime_error("Failed to open file for writing");
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &atlas::write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        const CURLcode res = curl_easy_perform(curl);

        fclose(fp);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::filesystem::remove(output);
            throw std::runtime_error(curl_easy_strerror(res));
        }
    }
}
