#include <gtest/gtest.h>
#include "fileManager.h"
#include "file.h"
#include "folder.h"
#include <sstream>

TEST(FileManagerTest, LsReturnsCorrectResult)
{
    Folder folder("name");
    File file1("file1", "txt", 100, "Content1");
    File file2("file2", "txt", 200, "Content2");
    File file3("file3", "txt", 300, "Content3");
    folder.addFile(file1);
    folder.addFile(file2);
    folder.addFile(file3);

    FileManager manager(folder);

    std::string result = manager.ls();
    EXPECT_EQ(result, "file1.txt file2.txt file3.txt \n");
}

TEST(FileManagerTest, PwdReturnsCorrectResult)
{
    Folder folder("name");
    File file1("file1", "txt", 100, "Content1");
    File file2("file2", "txt", 200, "Content2");
    File file3("file3", "txt", 300, "Content3");
    folder.addFile(file1);
    folder.addFile(file2);
    folder.addFile(file3);

    FileManager manager(folder);

    std::string result = manager.pwd();
    EXPECT_EQ(result, "/name/\n");
}

TEST(FileManagerTest, CdChangesCurrentFolder)
{
    Folder root("root");
    Folder subfolder("subfolder");
    root.addSubdirectory(subfolder);
    FileManager manager(root);
    manager.cd("subfolder");
    Folder &currentFolder = manager.getFolder();
    EXPECT_EQ(currentFolder.getName(), subfolder.getName());
    EXPECT_EQ(manager.pwd(), "/root/subfolder/\n");
}

TEST(FileManagerTest, CdFileAdding)
{
    Folder root("root");
    Folder subfolder("subfolder");
    root.addSubdirectory(subfolder);
    FileManager manager(root);
    manager.cd("subfolder");
    Folder &currentFolder = manager.getFolder();
    EXPECT_EQ(currentFolder.getName(), subfolder.getName());
    EXPECT_EQ(manager.pwd(), "/root/subfolder/\n");
    File file("filename", "txt", 100, "content");
    currentFolder.addFile(file);
    EXPECT_EQ(manager.ls(), "filename.txt \n");
    manager.cd("..");
    std::stringstream ss;
    ss << manager;
    EXPECT_EQ(ss.str(), "root/\nroot/:\nsubfolder/filename.txt\n");
}

TEST(FileManagerTest, ListFilesReturnsCorrectResult)
{
    Folder root("root");
    Folder subfolder("subfolder");
    root.addSubdirectory(subfolder);
    FileManager manager(root);
    manager.cd("subfolder");
    Folder &currentFolder = manager.getFolder();
    EXPECT_EQ(currentFolder.getName(), subfolder.getName());
    EXPECT_EQ(manager.pwd(), "/root/subfolder/\n");
    File file1("file1", "txt", 100, "Content1");
    File file2("file2", "txt", 200, "Content2");
    File file3("file3", "txt", 300, "Content3");
    currentFolder.addFile(file1);
    currentFolder.addFile(file2);
    currentFolder.addFile(file3);
    std::string result = manager.listFiles();
    EXPECT_EQ(result, "file1.txt file2.txt file3.txt \n");
}

TEST(FileManagerTest, ListFilesWithExtension)
{
    Folder root("root");
    Folder subfolder("subfolder");
    root.addSubdirectory(subfolder);
    FileManager manager(root);
    manager.cd("subfolder");
    Folder &currentFolder = manager.getFolder();
    EXPECT_EQ(currentFolder.getName(), subfolder.getName());
    EXPECT_EQ(manager.pwd(), "/root/subfolder/\n");
    File file1("file1", "png", 100, "Content1");
    File file2("file2", "txt", 200, "Content2");
    File file3("file3", "png", 300, "Content3");
    currentFolder.addFile(file1);
    currentFolder.addFile(file2);
    currentFolder.addFile(file3);
    std::string result = manager.listFiles("png");
    EXPECT_EQ(result, "file1.png file3.png \n");
}

TEST(FileManagerTest, DeepFindFileNonRecursive)
{
    Folder folder("Parent Folder");
    Folder folder2("child");
    Folder folder3("child2");
    File file1("test1", "txt", 100, "None");
    File file2("test2", "txt", 100, "None");
    File file3("test3", "cpp", 200, "None");
    folder.addFile(file1);
    folder.addFile(file2);
    folder2.addFile(file3);
    folder.addSubdirectory(folder3);
    folder.addSubdirectory(folder2);
    FileManager manager(folder);
    std::string foundFile = manager.findFile("test3", "cpp");
    EXPECT_EQ(foundFile, "No such file in this folder");
}

TEST(FileManagerTest, DeepFindFileRecursive)
{
    Folder folder("Parent Folder");
    Folder folder2("child");
    Folder folder3("child2");
    File file1("test1", "txt", 100, "None");
    File file2("test2", "txt", 100, "None");
    File file3("test3", "cpp", 200, "None");
    folder.addFile(file1);
    folder.addFile(file2);
    folder2.addFile(file3);
    folder.addSubdirectory(folder3);
    folder.addSubdirectory(folder2);
    FileManager manager(folder);
    std::string foundFile = manager.findFile("test3", "cpp", true);
    EXPECT_EQ(foundFile, "Parent Folder/child/");
}

TEST(FileManagerTest, SortFiles)
{
    Folder folder("Parent Folder");
    File file1("test3", "txt", 100, "None");
    File file2("test2", "txt", 200, "None");
    File file3("test1", "cpp", 150, "None");
    folder.addFile(file1);
    folder.addFile(file2);
    folder.addFile(file3);
    FileManager manager(folder);

    EXPECT_EQ(manager.listFiles(), "test3.txt test2.txt test1.cpp \n");

    manager.sortFiles();

    std::string sortedFiles = manager.listFiles();

    std::string expectedSortedFiles = "test1.cpp test2.txt test3.txt \n";

    EXPECT_EQ(sortedFiles, expectedSortedFiles);
}

TEST(FileManagerTest, GetDirectorySizeReturnsCorrectResult)
{
    Folder folder("Parent Folder");
    Folder folder2("child");
    File file1("test1", "txt", 100, "None");
    File file2("test2", "txt", 200, "None");
    File file3("test3", "cpp", 150, "None");
    File file4("test4", "cpp", 150, "None");
    folder.addFile(file1);
    folder.addFile(file2);
    folder.addFile(file3);
    folder2.addFile(file4);
    folder.addSubdirectory(folder2);
    FileManager manager(folder);

    long long expectedSize = 600;
    long long actualSize = manager.getDirectorySize();

    EXPECT_EQ(actualSize, expectedSize);
}

