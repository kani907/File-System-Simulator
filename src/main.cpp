#include <iostream>
#include <vector>
#include "file.h"
#include "fileManager.h"
#include "folder.h"

Folder configure()
{
    Folder base_folder("home");
    File file1("Welcome", "txt", 100, "Hello, World!");
    File file2("Config", "cfg", 100, "System configured");
    // second folder
    Folder user1("user1");
    File file3("userData", "dt", 100, "user: user1\n pwd: 123");
    File file4("Config", "cfg", 100, "System configured for user1");
    // third folder
    Folder user2("user2");
    File file5("userData", "dt", 100, "user: user2\n pwd: 123");
    File file6("Config", "cfg", 100, "System configured for user2");
    // fourth folder
    Folder private_data("private data");
    File file7("Picture", "png", 100, "UNREADABLE");
    File file8("CMakeLists", "txt", 100, "cmake_minimum_required(VERSION 3.12)");
    // adding files to home folder
    base_folder.addFile(file1);
    base_folder.addFile(file2);
    // adding files to folder of user 1
    user1.addFile(file3);
    user1.addFile(file4);
    // adding files to folder of user 2
    user2.addFile(file5);
    user2.addFile(file6);
    // adding files to folder with private data
    private_data.addFile(file7);
    private_data.addFile(file8);
    // creating paths
    user1.addSubdirectory(private_data);
    base_folder.addSubdirectory(user1);
    base_folder.addSubdirectory(user2);

    return base_folder;
}

int main()
{
    // main.cpp contains simple pre-created system to easily showcase abbilities of filemanager
    Folder example = configure();
    FileManager manager(example);
    std::cout << manager.ls();
    std::cout << manager;
    std::cout << manager.pwd();
    std::cout << manager.getFolder().findFile("picture", "png");
    return 0;
}