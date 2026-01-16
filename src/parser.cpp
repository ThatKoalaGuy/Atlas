#include <iostream>
#include <curl/curl.h>
#include <atlas/parser.h>

namespace atlas {
    //argc will be used later, do not delete!
    std::string parser(const int argc, char *argv[]) {
        std::string urlInput = argv[1];
        if (!urlInput.starts_with("http://") && !urlInput.starts_with("https://")) {
            urlInput = "https://" + urlInput;
        }

        CURLU *h = curl_url();
        if (!h) {
            throw std::runtime_error("Failed to create CURLU handle");
        }

        CURLUcode rc = curl_url_set(h, CURLUPART_URL, urlInput.c_str(), 0);
        if (rc != CURLUE_OK) {
            throw std::invalid_argument("Invalid URL");
        }

        char *out = nullptr;

        rc = curl_url_get(h, CURLUPART_URL, &out, 0);
        if (rc != CURLUE_OK || !out) {
            throw std::runtime_error("Failed to extract normalized URL");
        }

        std::string url(out);

        curl_free(out);
        curl_url_cleanup(h);

        return url;
    }
}
