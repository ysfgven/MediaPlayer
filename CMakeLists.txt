cmake_minimum_required(VERSION 3.30)
project(MediaPlayerCore)

set(CMAKE_CXX_STANDARD 20)

add_executable(MediaPlayerCore
        main.cpp
        src/MediaFile.cpp
        src/MediaPlayer.cpp
        src/FileScanner.cpp
        include/FileScanner.h
        src/MediaLibrary.cpp
        include/MediaLibrary.h
)

target_include_directories(MediaPlayerCore
        PRIVATE include
)
