cmake_minimum_required(VERSION 3.17)
project(Composition)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Composition
        src/main.cpp
        src/Image.cpp
        src/Image.h
        src/Tools/ChannelType.h src/Tools/Debug.h src/Tools/Debug.cpp)

target_include_directories(Composition PRIVATE
        "vendor/stb")