#pragma once

#include <string>
#include <vector>

namespace utils
{
class FileAccess
{
public:
    //TODO: change param names to filepath, dirpath
    virtual ~FileAccess() = default;

    virtual void write(const std::string& path, const std::string& content) const = 0;
    virtual void append(const std::string& path, const std::string& content) const = 0;
    virtual std::string readContent(const std::string& path) const = 0;
    virtual void createDirectory(const std::string& path) const = 0;
    virtual void remove(const std::string& path) const = 0;
    virtual void rename(const std::string& path, const std::string& filename) const = 0;
    virtual bool exists(const std::string& path) const = 0;
    virtual std::vector<std::string> getDirectoryFilePaths(const std::string& path) const = 0;
    virtual std::vector<std::string>
    getDirectoryFilenames(const std::string& path, const std::vector<std::string>& extensions) const = 0;
};
}