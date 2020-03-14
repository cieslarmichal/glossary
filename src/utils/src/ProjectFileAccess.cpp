#include "ProjectFileAccess.h"

#include "GetProjectPath.h"

namespace utils
{

ProjectFileAccess::ProjectFileAccess(const std::string& projectName)
    : projectPath{getProjectPath(projectName)}
{
}

void ProjectFileAccess::write(const std::string& relativePath, const std::string& content) const
{
    fileAccess.write(getAbsolutePath(relativePath), content);
}

void ProjectFileAccess::append(const std::string& relativePath, const std::string& content) const
{
    fileAccess.append(getAbsolutePath(relativePath), content);
}

std::string ProjectFileAccess::readContent(const std::string& relativePath) const
{
    return fileAccess.readContent(getAbsolutePath(relativePath));
}

void ProjectFileAccess::createDirectory(const std::string& relativePath) const
{
    fileAccess.createDirectory(getAbsolutePath(relativePath));
}

void ProjectFileAccess::remove(const std::string& relativePath) const
{
    fileAccess.remove(getAbsolutePath(relativePath));
}

void ProjectFileAccess::rename(const std::string& relativePath, const std::string& newRelativePath) const
{
    fileAccess.rename(getAbsolutePath(relativePath), getAbsolutePath(newRelativePath));
}

bool ProjectFileAccess::exists(const std::string& relativePath) const
{
    return fileAccess.exists(getAbsolutePath(relativePath));
}

std::vector<std::string> ProjectFileAccess::getDirectoryFilepaths(const std::string& relativePath) const
{
    return fileAccess.getDirectoryFilepaths(getAbsolutePath(relativePath));
}

std::vector<std::string>
ProjectFileAccess::getDirectoryFilenames(const std::string& relativePath,
                                         const std::vector<std::string>& extensions) const
{
    return fileAccess.getDirectoryFilenames(getAbsolutePath(relativePath), extensions);
}

std::string ProjectFileAccess::getAbsolutePath(const std::string& relativePath) const
{
    return projectPath + relativePath;
}

}
