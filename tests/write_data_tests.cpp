#include <doctest/doctest.h>
#include <atlas/write_data.h>
#include <cstdio>
#include <string>
#include <filesystem>
#include <fstream>

TEST_CASE("write_data writes buffer to file") {
    const std::string test_file = "test_write_data.bin";
    const std::string test_content = "Hello, Atlas!";
    
    FILE* fp = fopen(test_file.c_str(), "wb");
    REQUIRE(fp != nullptr);
    
    size_t written = atlas::write_data((void*)test_content.c_str(), 1, test_content.size(), fp);
    CHECK(written == test_content.size());
    
    fclose(fp);
    
    {
        std::ifstream in(test_file, std::ios::binary);
        std::string read_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        CHECK(read_content == test_content);
    }
    
    std::filesystem::remove(test_file);
}
