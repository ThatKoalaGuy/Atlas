#ifndef ATLAS_WRITEDATA_H
#define ATLAS_WRITEDATA_H
#include <cstddef>

namespace atlas {
    size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp);
}

#endif //ATLAS_WRITEDATA_H