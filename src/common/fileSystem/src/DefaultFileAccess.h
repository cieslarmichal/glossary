#pragma once

#include <filesystem>

#include "FileAccess.h"

namespace common::fileSystem
{
class DefaultFileAccess : public FileAccess
{
public:
    void write(const std::string& absolutePath, const std::string& content) const override;
    void append(const std::string& absolutePath, const std::string& content) const override;
    std::string readContent(const std::string& absolutePath) const override;
    void createDirectory(const std::string& absolutePath) const override;
    void remove(const std::string& absolutePath) const override;
    void rename(const std::string& absolutePath, const std::string& newAbsolutePath) const override;
    bool exists(const std::string& absolutePath) const override;
    bool isRegularFile(const std::string& absolutePath) const override;
    bool isDirectory(const std::string& absolutePath) const override;
    std::vector<std::string> getAllPathsFromDirectory(const std::string& absolutePath) const override;
    std::vector<std::string> getAllFilenamesFromDirectory(const std::string& absolutePath) const override;
    std::vector<std::string>
    getFilteredFilenamesFromDirectory(const std::string& absolutePath,
                                      const std::vector<std::string>& extensions) const override;

private:
    std::vector<std::filesystem::path> getAllPaths(const std::string& directoryPath) const;
    std::vector<std::string> filterByExtensions(const std::vector<std::string>& fileNames,
                                                const std::vector<std::string>& extensions) const;
    bool containsAnyOfExtensions(const std::filesystem::path& path,
                                 const std::vector<std::string>& fileExtensions) const;
    std::vector<std::string> filterFilenames(const std::vector<std::filesystem::path>& filePaths) const;
};
}
