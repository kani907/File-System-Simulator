#include <iostream>
#include <vector>
#include "file.h"
#include "folder.h"
#include <algorithm>
#include <numeric>

Folder::Folder() : name("New Folder") {}
Folder::Folder(std::string name) : name(name) {}

std::vector<Folder> &Folder::getSubdirectories()
{
    return subdirectories;
}

std::vector<File> &Folder::getFiles()
{
    return files;
}

std::string Folder::getName() const
{
    return name;
}

bool Folder::getToDelete() const
{
    return toDelete;
}

void Folder::setName(const std::string &folderName)
{
    name = folderName;
}

void Folder::addSubdirectory(Folder &subdirectory)
{
    subdirectories.push_back(subdirectory);
}

void Folder::addFile(File &file)
{
    files.push_back(file);
}

void Folder::setToDelete(bool value)
{
    toDelete = value;
}

void Folder::removeFolder(Folder &folder)
{
    auto iterator = std::remove_if(subdirectories.begin(), subdirectories.end(), [&](const Folder &sub)
                                   { return sub.getName() == folder.getName(); });
    if (iterator != subdirectories.end())
    {
        subdirectories.erase(iterator, subdirectories.end());
    }
}

void Folder::removeFile(File &file)
{
    auto iterator = std::remove_if(files.begin(), files.end(), [&](const File &f)
                                   { return f == file; });
    if (iterator != files.end())
    {
        files.erase(iterator, files.end());
    }
}

std::ostream &operator<<(std::ostream &os, Folder &folder)
{
    if (folder.getFiles().size() == 0)
    {
        os << folder.getName() << "/" << std::endl;
    }
    for (File file : folder.getFiles())
    {
        os << folder.getName() << "/" << file << std::endl;
    }

    for (Folder sub : folder.getSubdirectories())
    {
        os << folder.getName() << "/:" << std::endl
           << sub;
    }
    return os;
}

void Folder::mergeFolders(Folder &folder)
{
    // finds subdirectory in current folder that matches the given folder
    auto iterator = std::find_if(subdirectories.begin(), subdirectories.end(), [&](const Folder &sub)
                                 { return sub.getName() == folder.getName(); });

    // if such directory exists proceeds to merge given folder into it
    if (iterator != folder.getSubdirectories().end())
    {
        // proceeds to compare files in both directories and merges them
        for (File file : folder.getFiles())
        {
            if (!file.getToDelete())
            {
                // if file is not marked as to delete it will be merged into parent folder
                std::vector<File> folder_files = (*iterator).getFiles();
                auto iterator_for_file = std::find(folder_files.begin(), folder_files.end(), file);
                if (iterator_for_file == folder_files.end())
                {
                    (*iterator).addFile(file);
                }
            }
            // if it is marked as to delete it wil be not
            else
            {
                (*iterator).removeFile(file);
            }
        }
        // proceeds to compare subdirectories in both directories and merges them
        for (Folder sub : folder.getSubdirectories())
        {
            if (!sub.getToDelete())
            {
                // if subdirectory is not marked as to delete it will be merged into parent folder
                std::vector<Folder> folder_subs = (*iterator).getSubdirectories();
                auto iterator_for_folder = std::find_if(folder_subs.begin(), folder_subs.end(), [&](const Folder &tested_folder)
                                                        { return sub.getName() == tested_folder.getName(); });
                if (iterator_for_folder == folder_subs.end())
                {
                    (*iterator).addSubdirectory(sub);
                }
            }
            // if it is marked as to delete it wil be not
            else
            {
                (*iterator).removeFolder(sub);
            }
        }
    }
    // else adds new directory to parent folder
    else
    {
        this->addSubdirectory(folder);
    }
}

bool fileExists(std::string name, std::string ext, Folder &folder)
{
    std::vector<File> files = folder.getFiles();
    auto iterator = std::find_if(files.begin(), files.end(), [&](const File &file)
                                 { return file.getName() == name && file.getExtension() == ext; });
    return iterator != files.end();
}

std::string Folder::findFile(std::string name, std::string ext)
{
    if (fileExists(name, ext, *this))
    {
        return this->name + "/";
    }
    else
    {
        std::vector<std::string> results;
        for (Folder sub : subdirectories)
        {
            std::string result = sub.findFile(name, ext);
            results.push_back(result);
        }
        auto iterator = std::remove(results.begin(), results.end(), "File not found");
        results.erase(iterator, results.end());
        if (results.empty())
        {
            return "File not found";
        }
        else
        {
            return this->name + "/" + results[0];
        }
    }
    return "";
}

long long Folder::getFolderSize()
{
    long long result = 0;
    result += std::accumulate(files.begin(), files.end(), 0LL, [&](long long sum, const File &file)
                             { return sum + file.getSize(); });
    for (Folder &sub : subdirectories)
    {
        result += sub.getFolderSize();
    }
    return result;
}
