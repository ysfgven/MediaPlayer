//
// Created by yusuf on 21.01.2026.
//

#ifndef MEDIAFILE_H
#define MEDIAFILE_H
#include <filesystem>



class MediaFile {
    private:
    std::string title;
    std::string artist;
    int duration;
    std::filesystem::path filePath;

    public:
    MediaFile() = default;

    std::filesystem::path getFilePath() const;
    void setFilePath(std::filesystem::path filePath);
    bool isFileValid() const;



    std::string getTitle() const;
    std::string getArtist() const;
    int getDuration() const;

    void setDuration(int duration);
    void setTitle(std::string title);
    void setArtist(std::string artist);


};



#endif //MEDIAFILE_H
