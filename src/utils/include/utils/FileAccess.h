#pragma once

#include <string>
#include <vector>

namespace utils
{
class FileAccess
{
public:
    virtual ~FileAccess() = default;

    virtual void write(const std::string& filepath, const std::string& content) const = 0;
    virtual void append(const std::string& filepath, const std::string& content) const = 0;
    virtual std::string readContent(const std::string& filepath) const = 0;
    virtual void createDirectory(const std::string& directoryPath) const = 0;
    virtual void remove(const std::string& path) const = 0;
    virtual void rename(const std::string& oldPath, const std::string& newPath) const = 0;
    virtual bool exists(const std::string& path) const = 0;
    virtual bool isRegularFile(const std::string& path) const = 0;
    virtual bool isDirectory(const std::string& path) const = 0;
    virtual std::vector<std::string> getAllPathsFromDirectory(const std::string& directoryPath) const = 0;
    virtual std::vector<std::string>
    getAllFilenamesFromDirectory(const std::string& directoryPath,
                                 const std::vector<std::string>& extensions) const = 0;
};
}