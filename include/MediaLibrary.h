//
// Created by yusuf on 24.01.2026.
//

#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

#include <vector>
#include <filesystem>
#include "MediaFile.h"

class MediaLibrary {
private:
    std::vector<MediaFile> mediaFiles;

public:
    void loadFromDirectory(const std::filesystem::path& directoryPath);

    size_t getTrackCount() const;
    const MediaFile* getTrack(size_t index) const;

    bool empty() const;
};

#endif

