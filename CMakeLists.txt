cmake_minimum_required(VERSION 3.31.6)
project(Atlas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- dependencies ----
find_package(CURL CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)

# ---- core library ----
add_library(atlas_lib
        src/parser.cpp
        src/downloader.cpp
        src/write_data.cpp
        src/command/help.cpp
        src/command/version.cpp
)

target_include_directories(atlas_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(atlas_lib PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

target_link_libraries(atlas_lib PUBLIC
        CURL::libcurl
)

# ---- main executable ----
add_executable(Atlas
        src/main.cpp
)

target_link_libraries(Atlas PRIVATE atlas_lib)

# ---- tests ----
add_executable(atlas_tests
        tests/main.cpp
        tests/parser_tests.cpp
        tests/filename_from_url.cpp
)

# ---- CI ----
enable_testing()
add_test(
        NAME atlas_tests
        COMMAND atlas_tests
)

target_link_libraries(atlas_tests PRIVATE
        atlas_lib
        doctest::doctest
)
