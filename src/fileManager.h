#pragma once
#include <iostream>
#include "file.h"
#include "folder.h"
#include <stack>

// this is able to be refactored and while descending it creates new object of file manager yet i thpught of it after implementing
// all needed methods therefore it stays as it is
// used stl algorithms:
// remove
// copy_if
// find
// sort
// accumulate

class FileManager
{
public:
    FileManager(Folder& folder);
    Folder& getFolder();
    std::string ls() const;
    void cd(std::string name);
    std::string pwd() const;
    std::string listFiles(std::string ext = "NONE");
    std::string findFile(std::string name, std::string ext, bool recursive = false);
    void sortFiles(); // std::sort
    long long getDirectorySize(); // std::accumulted:: remove
    void mkdir(Folder& folder);
    void touch(File& file);
private:
    std::stack<Folder> path;
    std::vector<std::string> workingDir;
};

std::ostream& operator<<(std::ostream& os, FileManager& manager);