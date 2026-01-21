//
// Created by yusuf on 21.01.2026.
//

#include "../include/FileScanner.h"


void FileScanner::fillFileList(std::vector<std::filesystem::path>& fileList, std::filesystem::path filePath) {
    for (const auto& file : std::filesystem::directory_iterator(filePath)) {
       fileList.push_back(file.path());
    }

}
std::vector<std::filesystem::path>& FileScanner::getFileList() {
        return fileList;
}
std::filesystem::path FileScanner::searchForFile(std::string fileName,std::filesystem::path filePath) {
    for (const auto& file : std::filesystem::directory_iterator(filePath)) {
        if (fileName == file.path().filename().string()) {
            return file.path();
        }
    }
    return std::filesystem::path();

}









