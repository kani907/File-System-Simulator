#pragma once
#include <iostream>
#include <vector>
#include "file.h"

class Folder {
public:
    Folder();
    Folder(const std::string name);
    std::vector<Folder>& getSubdirectories();
    std::vector<File>& getFiles();
    std::string getName() const;
    void setName(const std::string& folderName);
    void addSubdirectory(Folder& subdirectory);
    void addFile(File& file);
    void mergeFolders(Folder& folder);
    void setToDelete(bool value);
    bool getToDelete() const;
    void removeFolder(Folder& folder);
    void removeFile(File& file);
    std::string findFile(std::string name, std::string ext);
    long long getFolderSize();

private:
    std::vector<Folder> subdirectories;
    std::vector<File> files;
    std::string name;
    bool toDelete;
};

std::ostream& operator<<(std::ostream& os, Folder& folder);