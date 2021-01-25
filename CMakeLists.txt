cmake_minimum_required(VERSION 3.17)
project(Composition)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Composition
        src/main.cpp src/Image.cpp src/Image.h)
