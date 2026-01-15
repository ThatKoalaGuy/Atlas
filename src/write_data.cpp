#include <cstdio>
#include <atlas/write_data.h>

namespace atlas {
    size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
        const auto fp = static_cast<FILE*>(userp);
        return fwrite(buffer, size, nmemb, fp);
    }
}
