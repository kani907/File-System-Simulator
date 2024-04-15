#include "gtest/gtest.h"
#include "file.h"

TEST(FileTest, GetName) {
    File file("example", "txt", 100, "This is an example file");
    EXPECT_EQ(file.getName(), "example");
}

TEST(FileTest, GetExtension) {
    File file("example", "txt", 100, "This is an example file");
    EXPECT_EQ(file.getExtension(), "txt");
}

TEST(FileTest, GetSize) {
    File file("example", "txt", 100, "This is an example file");
    EXPECT_EQ(file.getSize(), 100);
}

TEST(FileTest, GetContent) {
    File file("example", "txt", 100, "This is an example file");
    EXPECT_EQ(file.getContent(), "This is an example file");
}

TEST(FileTest, SetName) {
    File file("example", "txt", 100, "This is an example file");
    file.setName("new_example");
    EXPECT_EQ(file.getName(), "new_example");
}

TEST(FileTest, SetExtension) {
    File file("example", "txt", 100, "This is an example file");
    file.setExtension("doc");
    EXPECT_EQ(file.getExtension(), "doc");
}

TEST(FileTest, SetSize) {
    File file("example", "txt", 100, "This is an example file");
    file.setSize(200);
    EXPECT_EQ(file.getSize(), 200);
}

TEST(FileTest, SetContent) {
    File file("example", "txt", 100, "This is an example file");
    file.setContent("This is a new content");
    EXPECT_EQ(file.getContent(), "This is a new content");
}

TEST(FileTest, OutputOperator) {
    File file("example", "txt", 100, "This is an example file");
    std::ostringstream oss;
    oss << file;
    std::string expectedOutput = "example.txt";
    EXPECT_EQ(oss.str(), expectedOutput);
}

TEST(FileTest, EqualityOperator) {
    File file1("example", "txt", 100, "This is an example file");
    File file2("example", "txt", 100, "This is an example file");
    File file3("example", "doc", 200, "This is a different file");

    EXPECT_TRUE(file1 == file2);
    EXPECT_FALSE(file1 == file3);
}

TEST(FileTest, toDeleteTest)
{
    File file1("example", "txt", 100, "This is an example file");
    EXPECT_FALSE(file1.getToDelete());
    file1.setToDelete(true);
    EXPECT_TRUE(file1.getToDelete());
}