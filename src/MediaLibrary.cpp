//
// Created by yusuf on 24.01.2026.
//

#include "MediaLibrary.h"
#include "MetadataReader.h"

void MediaLibrary::loadFromDirectory(const std::filesystem::path& directoryPath) {
    mediaFiles.clear();

    if (!std::filesystem::exists(directoryPath)) return;
    if (!std::filesystem::is_directory(directoryPath)) return;

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        MediaFile media;
        media.setFilePath(entry.path());

        if (media.isFileValid()) {
            MetadataReader::load(media);
            mediaFiles.push_back(media);
        }
    }
}

size_t MediaLibrary::getTrackCount() const {
    return mediaFiles.size();
}

const MediaFile* MediaLibrary::getTrack(size_t index) const {
    if (index >= mediaFiles.size())
        return nullptr;
    return &mediaFiles[index];
}

bool MediaLibrary::empty() const {
    return mediaFiles.empty();
}
