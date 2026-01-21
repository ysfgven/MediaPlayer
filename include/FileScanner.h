//
// Created by yusuf on 21.01.2026.
//

#ifndef FILESCANNER_H
#define FILESCANNER_H
#include <string>
#include <vector>
#include <filesystem>


class FileScanner {

private:
    std::string fileName;
    std::vector<std::filesystem::path> fileList;

public:
    FileScanner() = default;

    void fillFileList(std::vector<std::filesystem::path>& fileList,std::filesystem::path filePath);
    std::vector<std::filesystem::path>& getFileList();
    std::filesystem::path FileScanner::searchForFile(std::string fileName,std::filesystem::path filePath);


};



#endif //FILESCANNER_H
