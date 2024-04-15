#include "file.h"
#include <iostream>

File::File()
{
    name = "";
    extension = "";
    size = 0;
    content = "";
    toDelete = false;
}

File::File(const std::string &name, const std::string &extension, int size, const std::string &content) : name(name), extension(extension), size(size), content(content), toDelete(false) {}

std::string File::getName() const
{
    return name;
}

std::string File::getExtension() const
{
    return extension;
}

int File::getSize() const
{
    return size;
}

std::string File::getContent() const
{
    return content;
}
bool File::getToDelete() const
{
    return toDelete;    
}

void File::setName(const std::string &new_name)
{
    name = new_name;
}

void File::setExtension(const std::string &new_extension)
{
    extension = new_extension;
}

void File::setSize(int new_size)
{
    size = new_size;
}

void File::setContent(const std::string &new_content)
{
    content = new_content;
}

void File::setToDelete(bool value)
{
    toDelete = value;
}

std::ostream &operator<<(std::ostream &os, const File &file)
{
    os << file.getName() << "." << file.getExtension();
    return os;
}

bool File::operator==(const File &other) const
{
    return name == other.getName() && extension == other.getExtension() && size == other.getSize() && content == other.getContent();
}