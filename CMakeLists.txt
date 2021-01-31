cmake_minimum_required(VERSION 3.17)
project(Composition)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(Composition
        src/main.cpp
        src/Image.cpp
        src/Image.h
        src/UserInterface.cpp
        src/UserInterface.h
        src/Tools/Debug.h
        src/Tools/Debug.cpp
        src/Tools/ImageType.h
        src/Helpers/StringHelpers.cpp
        src/Helpers/StringHelpers.h
        src/Helpers/FileHelper.cpp
        src/Helpers/FileHelper.h
        src/Helpers/ImageProcessingHelper.h
        src/Helpers/ImageProcessingHelper.cpp)

target_include_directories(Composition PRIVATE
        "vendor/stb")

add_custom_command(TARGET Composition PRE_BUILD
        COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")