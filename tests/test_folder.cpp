#include <gtest/gtest.h>
#include "folder.h"
#include "file.h"

TEST(FolderTest, GetName)
{
    Folder folder("Test Folder");
    EXPECT_EQ(folder.getName(), "Test Folder");
}

TEST(FolderTest, SetName)
{
    Folder folder;
    folder.setName("New Name");
    EXPECT_EQ(folder.getName(), "New Name");
}

TEST(FolderTest, AddSubdirectory)
{
    Folder folder;
    Folder subdirectory("Subdirectory");
    folder.addSubdirectory(subdirectory);
    EXPECT_EQ(folder.getSubdirectories().size(), 1);
    EXPECT_EQ(folder.getSubdirectories()[0].getName(), "Subdirectory");
}

TEST(FolderTest, AddFile)
{
    Folder folder;
    File file("test", "txt", 100, "None");
    folder.addFile(file);
    EXPECT_EQ(folder.getFiles().size(), 1);
    EXPECT_EQ(folder.getFiles()[0].getName(), "test");
}
TEST(FolderTest, OutputOperator)
{
    Folder folder("folder");
    Folder folder2("folder2");
    File file1("test", "txt", 100, "None");
    File file2("test2", "txt", 100, "None");
    folder2.addFile(file2);
    folder.addSubdirectory(folder2);
    folder.addFile(file1);
    std::ostringstream oss;
    oss << folder;
    std::string expectedOutput = "folder/test.txt\nfolder/:\nfolder2/test2.txt\n";
    EXPECT_EQ(oss.str(), expectedOutput);
}

TEST(FolderTest, acccesingFile)
{
    Folder folder("folder");
    Folder folder2("folder2");
    File file1("test", "txt", 100, "None");
    File file2("test2", "txt", 100, "None");
    folder2.addFile(file2);
    folder.addSubdirectory(folder2);
    folder.addFile(file1);
    File& file = folder.getSubdirectories()[0].getFiles()[0]; 
    EXPECT_EQ(file.getName(), "test2");
    file.setName("new_name");
    std::ostringstream oss;
    oss << folder;
    std::string expectedOutput = "folder/test.txt\nfolder/:\nfolder2/new_name.txt\n";
    EXPECT_EQ(oss.str(), expectedOutput);
}

TEST(FolderTest, MergeFolders)
{
    Folder folder("folder");
    Folder folder2("folder2");
    Folder folder3("folder3");
    Folder folder4("folder4");
    Folder folder5("folder5");
    File file1("test", "txt", 100, "None");
    File file2("test2", "txt", 100, "None");
    File file3("3rd file", "txt", 100, "n");
    folder2.addFile(file2);
    folder.addFile(file1);
    folder3.addFile(file1);
    folder2.addFile(file3);
    folder2.addSubdirectory(folder5);
    folder.addSubdirectory(folder2);
    folder.addSubdirectory(folder3);
    folder2.addFile(file1);
    folder2.addSubdirectory(folder4);
    folder2.getSubdirectories()[0].setToDelete(true);
    folder2.getFiles()[1].setToDelete(true);
    EXPECT_EQ(folder2.getFiles().size(), 3);
    folder.mergeFolders(folder2);
    EXPECT_EQ(folder.getSubdirectories()[0].getSubdirectories().size(), 1);
    EXPECT_EQ(folder.getSubdirectories()[0].getFiles()[0], file2);
}

TEST(FolderTest, toDeleteTest)
{
    Folder folder("example");
    EXPECT_FALSE(folder.getToDelete());
    folder.setToDelete(true);
    EXPECT_TRUE(folder.getToDelete());
}


TEST(FolderTest, DeleteFolder)
{
    Folder folder("Parent Folder");
    Folder subdirectory("Subdirectory");
    folder.addSubdirectory(subdirectory);
    Folder sub2("Subdirectory2");
    folder.addSubdirectory(sub2);
    folder.removeFolder(subdirectory);
    EXPECT_EQ(folder.getSubdirectories().size(), 1);
    std::vector<Folder> subs = folder.getSubdirectories();
    EXPECT_EQ(subs[0].getName(), "Subdirectory2");
}

TEST(FolderTest, DeleteFile)
{
    Folder folder("folder");
    File file1("test1", "txt", 100, "None");
    File file2("test2", "txt", 100, "None");
    folder.addFile(file1);
    folder.addFile(file2);
    folder.removeFile(file1);
    EXPECT_EQ(folder.getFiles().size(), 1);
    std::vector<File> files = folder.getFiles();
    EXPECT_EQ(files[0], file2);
}

TEST(FolderTest, FindFile)
{
    Folder folder("Parent Folder");
    File file1("test1", "txt", 100, "None");
    File file2("test2", "txt", 100, "None");
    File file3("test3", "cpp", 200, "None");
    folder.addFile(file1);
    folder.addFile(file2);
    folder.addFile(file3);

    std::string foundFile = folder.findFile("test2", "txt");
    EXPECT_EQ(foundFile, "Parent Folder/");

    foundFile = folder.findFile("test3", "cpp");
    EXPECT_EQ(foundFile, "Parent Folder/");

    foundFile = folder.findFile("test4", "txt");
    EXPECT_EQ(foundFile, "File not found");

    foundFile = folder.findFile("test1", "jpg");
    EXPECT_EQ(foundFile, "File not found");
}

TEST(FolderTest, DeepFindFile)
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

    std::string foundFile = folder.findFile("test3", "cpp");
    EXPECT_EQ(foundFile, "Parent Folder/child/");
}

TEST(FolderTest, GetFolderSizeReturnsCorrectResult)
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

    long long expectedSize = 600;
    long long actualSize = folder.getFolderSize();

    EXPECT_EQ(actualSize, expectedSize);
}
