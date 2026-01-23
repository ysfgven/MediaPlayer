//
// Created by yusuf on 24.01.2026.
//

#include "../include/MediaLibrary.h"

void MediaLibrary::loadFromDirectory(const std::filesystem::path& directoryPath) {
    mediaFiles.clear();

    if (!std::filesystem::exists(directoryPath))
        return;

    if (!std::filesystem::is_directory(directoryPath))
        return;

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        MediaFile media;
        media.setFilePath(entry.path());

        if (media.isFileValid()) {
            mediaFiles.push_back(media);
        }
    }
}
const std::vector<MediaFile>& MediaLibrary::getMediaFiles() const {
    return mediaFiles;
}

bool MediaLibrary::empty() const {
    return mediaFiles.empty();
}

std::size_t MediaLibrary::size() const {
    return mediaFiles.size();
}