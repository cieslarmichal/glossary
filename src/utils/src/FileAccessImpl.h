#pragma once

#include "FileAccess.h"
#include "FileExtensionsFilter.h"
#include "FilenamePathFilter.h"

namespace utils
{
class FileAccessImpl : public FileAccess
{
public:
    FileAccessImpl(const std::string& projectName);

    void write(const std::string& path, const std::string& content) const override;
    void append(const std::string& path, const std::string& content) const override;
    std::string readContent(const std::string& path) const override;
    void createDirectory(const std::string& path) const override;
    void remove(const std::string& path) const override;
    void rename(const std::string& path, const std::string& newPath) const override;
    bool exists(const std::string& path) const override;
    std::vector<std::string> getDirectoryFilepaths(const std::string& path) const override;
    std::vector<std::string> getDirectoryFilenames(const std::string& path,
                                                   const std::vector<std::string>& extensions) const override;

private:
    std::string getAbsolutePath(const std::string&) const;

    FilenamePathFilter filenamePathFilter;
    FileExtensionsFilter fileExtensionsFilter;
    const std::string projectPath;
};
}