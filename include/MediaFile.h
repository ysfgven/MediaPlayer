//
// Created by yusuf on 21.01.2026.
//

#ifndef MEDIAFILE_H
#define MEDIAFILE_H
#include <string>


class MediaFile {
    private:
    std::string filePath;
    std::string fileFormat;


    public:
    MediaFile() = default;

    std::string getFilePath();
    void setFilePath(std::string filePath);
    bool isFileValid();


};



#endif //MEDIAFILE_H
