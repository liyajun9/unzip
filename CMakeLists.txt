cmake_minimum_required(VERSION 3.15)
project(test)

set(CMAKE_CXX_STANDARD 11)

add_executable(test main.cpp
        unzip.h unzip.c
        ioapi.h ioapi.c)

target_include_directories(test PRIVATE /usr/include)

target_link_libraries(test PRIVATE /usr/lib64)

target_link_libraries(test PRIVATE -lz)