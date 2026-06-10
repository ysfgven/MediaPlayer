if(DEFINED ENV{VCPKG_ROOT})
endif()

cmake_minimum_required(VERSION 3.30)
project(MediaPlayerCore)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
find_package(ZLIB REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)
find_package(taglib CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
add_executable(MediaPlayerCore
        main.cpp
        src/MediaFile.cpp
        src/MediaPlayer.cpp
        src/MediaLibrary.cpp
        include/MediaLibrary.h
        src/MetadataReader.cpp
        "include/MetadataReader.h"
        include/AudioEngine.h
        src/AudioEngine.cpp
        ui/MainWindow.cpp
        ui/MainWindow.h
        ui/MainWindow.ui
        resources/resources.qrc

)

target_include_directories(MediaPlayerCore
        PRIVATE include
        PRIVATE ui
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(MediaPlayerCore PRIVATE TagLib::tag Qt6::Core Qt6::Widgets)
