//
// Created by yusuf on 21.01.2026.
//

#include "MediaFile.h"

bool MediaFile::isFileValid() const {
    if (filePath.empty())
        return false;

    if (!std::filesystem::exists(filePath))
        return false;

    if (!std::filesystem::is_regular_file(filePath))
        return false;

    // extension check
    if (filePath.extension() != ".mp3")
        return false;

    return true;
}

std::filesystem::path MediaFile::getFilePath() const {
    return filePath;
}

void MediaFile::setFilePath(std::filesystem::path filePath) {
    this->filePath = filePath;
}

std::string MediaFile::getTitle() const {
    return title;
}

std::string MediaFile::getArtist() const {
    return artist;
}

int MediaFile::getDuration() const {
    return duration;
}

void MediaFile::setDuration(int duration) {
    this -> duration =  duration;
}

void MediaFile::setTitle(std::string title) {
    this->title = title;
}

void MediaFile::setArtist(std::string artist) {
    this->artist = artist;
}
