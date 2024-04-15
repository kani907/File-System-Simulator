#pragma once
#include <iostream>

class File
{
public:
    File();
    File(const std::string &name, const std::string &extension, int size, const std::string &content);
    std::string getName() const;
    std::string getExtension() const;
    int getSize() const;
    std::string getContent() const;
    void setName(const std::string &name);
    void setExtension(const std::string &extension);
    void setSize(int size);
    void setContent(const std::string &content);
    bool operator==(const File& other) const;
    void setToDelete(bool value);
    bool getToDelete() const;

private:
    std::string name;
    std::string extension;
    int size;
    std::string content;
    bool toDelete;
};;

std::ostream& operator<<(std::ostream& os, const File& file);