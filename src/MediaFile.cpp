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

std::filesystem::path MediaFile::getFilePath() {
    return filePath;
}

void MediaFile::setFilePath(std::filesystem::path filePath) {
    this->filePath = filePath;
}
