//
// Created by yusuf on 21.01.2026.
//

#ifndef MEDIAFILE_H
#define MEDIAFILE_H
#include <filesystem>



class MediaFile {
    private:
    std::filesystem::path filePath;

    public:
    MediaFile() = default;

    std::filesystem::path getFilePath();
    void setFilePath(std::filesystem::path filePath);
    bool isFileValid() const;


};



#endif //MEDIAFILE_H
