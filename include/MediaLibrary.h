//
// Created by yusuf on 24.01.2026.
//

#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H
#include <MediaFile.h>
#include <vector>


class MediaLibrary {
private:
    std::vector<MediaFile> mediaFiles;
    public:
    MediaLibrary();
    void loadFromDirectory(const std::filesystem::path& directoryPath);
    const std::vector<MediaFile>& getMediaFiles() const;
    bool empty() const;
    std::size_t size() const;

};



#endif //MEDIALIBRARY_H
