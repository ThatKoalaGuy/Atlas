cmake_minimum_required(VERSION 3.31.6)
project(Atlas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Atlas
        src/main.cpp
        src/parser.cpp
        src/downloader.cpp
        src/write_data.cpp
        include/atlas/write_data.h
)

target_include_directories(Atlas PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(Atlas PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

find_package(CURL CONFIG REQUIRED)
target_link_libraries(Atlas PRIVATE CURL::libcurl)