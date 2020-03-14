#pragma once

#include "DefaultFileAccess.h"
#include "FileAccess.h"

namespace utils
{
class ProjectFileAccess : public FileAccess
{
public:
    explicit ProjectFileAccess(const std::string& projectName);

    void write(const std::string& relativePath, const std::string& content) const override;
    void append(const std::string& relativePath, const std::string& content) const override;
    std::string readContent(const std::string& relativePath) const override;
    void createDirectory(const std::string& relativePath) const override;
    void remove(const std::string& relativePath) const override;
    void rename(const std::string& relativePath, const std::string& newPath) const override;
    bool exists(const std::string& relativePath) const override;
    std::vector<std::string> getDirectoryFilepaths(const std::string& relativePath) const override;
    std::vector<std::string> getDirectoryFilenames(const std::string& relativePath,
                                                   const std::vector<std::string>& extensions) const override;

private:
    std::string getAbsolutePath(const std::string& relativePath) const;

    DefaultFileAccess fileAccess;
    const std::string projectPath;
};
}