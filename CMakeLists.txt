if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

cmake_minimum_required(VERSION 3.30)
project(MediaPlayerCore)

set(CMAKE_CXX_STANDARD 20)
find_package(ZLIB REQUIRED)
find_package(taglib CONFIG REQUIRED)

add_executable(MediaPlayerCore
        main.cpp
        src/MediaFile.cpp
        src/MediaPlayer.cpp
        src/MediaLibrary.cpp
        include/MediaLibrary.h
        src/MetadataReader.cpp
        "include/MetadataReader.h"
)

target_include_directories(MediaPlayerCore
        PRIVATE include
)

target_link_libraries(MediaPlayerCore PRIVATE TagLib::tag)
