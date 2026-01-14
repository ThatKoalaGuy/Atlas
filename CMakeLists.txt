cmake_minimum_required(VERSION 3.31.6)
project(Atlas)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(Atlas src/main.cpp
        src/parser.cpp
        include/atlas/parser.h)

target_include_directories(Atlas
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)