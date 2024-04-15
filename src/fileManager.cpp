#include <iostream>
#include "file.h"
#include "folder.h"
#include <stack>
#include "fileManager.h"
#include <algorithm>
#include <numeric>

FileManager::FileManager(Folder &folder)
{
    path.push(folder);
    workingDir.push_back(folder.getName());
}

std::string FileManager::ls() const
{
    std::string result = "";
    Folder current_folder = path.top();
    for (Folder sub : current_folder.getSubdirectories())
    {
        result += "/";
        result += sub.getName();
        result += " ";
    }
    for (File file : current_folder.getFiles())
    {
        result += file.getName();
        result += ".";
        result += file.getExtension();
        result += " ";
    }
    result += "\n";
    return result;
}

Folder &FileManager::getFolder()
{
    return path.top();
}

std::string FileManager::pwd() const
{
    std::string result;
    result += "/";
    for (std::string folderName : workingDir)
    {
        result += folderName;
        result += "/";
    }
    result += "\n";
    return result;
}

void FileManager::cd(std::string name)
{
    if (name == "..")
    {
        if (workingDir.size() > 1)
        {
            Folder child = path.top();
            path.pop();
            path.top().mergeFolders(child);
            workingDir.pop_back();
        }
        else
        {
            throw std::runtime_error("Already at the highest folder");
        }
    }
    else
    {
        auto it = std::find_if(path.top().getSubdirectories().begin(), path.top().getSubdirectories().end(), [&](const Folder &folder)
                               { return folder.getName() == name; });
        if (it != path.top().getSubdirectories().end())
        {
            Folder child = *it;
            path.push(child);
            workingDir.push_back(child.getName());
        }
        else
        {
            throw std::runtime_error("Folder not found");
        }
    }
}

std::string FileManager::listFiles(std::string ext)
{
    std::vector<File> files;
    std::string result;
    if (ext == "NONE")
    {
        files = path.top().getFiles();
    }
    else
    {
        std::vector<File> imported_files = path.top().getFiles();
        std::copy_if(imported_files.begin(), imported_files.end(), std::back_inserter(files), [&](const File &file)
                     { return file.getExtension() == ext; });
    }
    for (File file : files)
    {
        result += file.getName();
        result += ".";
        result += file.getExtension();
        result += " ";
    }
    result += "\n";
    return result;
}

std::string FileManager::findFile(std::string name, std::string ext, bool recursive)
{
    if (recursive)
    {
        return path.top().findFile(name, ext);
    }
    else
    {
        std::vector<File> files = path.top().getFiles();
        auto iterator = std::find_if(files.begin(), files.end(), [&](const File &file)
                                     { return file.getName() == name && file.getExtension() == ext; });
        if (iterator != files.end())
        {
            return path.top().getName() + "/";
        }
        else
        {
            return "No such file in this folder";
        }
    }
}

std::string toLowerCase(const std::string &str)
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return lowerStr;
}

void FileManager::sortFiles()
{
    Folder &folder = path.top();
    std::sort(folder.getFiles().begin(), folder.getFiles().end(), [&](const File &file1, const File &file2)
              { return toLowerCase(file1.getName()) < toLowerCase(file2.getName()); });
}

long long FileManager::getDirectorySize()
{
    return path.top().getFolderSize();
}

std::ostream &operator<<(std::ostream &os, FileManager &manager)
{
    os << manager.getFolder();
    return os;
}

void FileManager::mkdir(Folder& folder)
{
    path.top().addSubdirectory(folder);
}

void FileManager::touch(File& file)
{
    path.top().addFile(file);
}