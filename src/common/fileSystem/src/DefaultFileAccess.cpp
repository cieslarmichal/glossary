#include "DefaultFileAccess.h"

#include <boost/algorithm/cxx11/any_of.hpp>
#include <filesystem>
#include <fstream>

#include "fmt/core.h"

#include "exceptions/DirectoryNotFound.h"
#include "exceptions/FileNotFound.h"
#include "GetProjectPath.h"

namespace common::fileSystem
{
void DefaultFileAccess::write(const std::string& absolutePath, const std::string& content) const
{
    std::ofstream fileStream{absolutePath};

    if (!fileStream.is_open())
    {
        throw exceptions::FileNotFound(fmt::format("file not found", absolutePath));
    }

    fileStream << content;
}

void DefaultFileAccess::append(const std::string& absolutePath, const std::string& content) const
{
    std::ofstream fileStream{absolutePath, std::ofstream::app};

    if (!fileStream.is_open())
    {
        throw exceptions::FileNotFound(fmt::format("file not found", absolutePath));
    }

    fileStream << content;
}

std::string DefaultFileAccess::readContent(const std::string& absolutePath) const
{
    std::ifstream fileStream{absolutePath};

    std::stringstream buffer;

    if (!fileStream.is_open())
    {
        throw exceptions::FileNotFound(fmt::format("file not found", absolutePath));
    }

    buffer << fileStream.rdbuf();

    return buffer.str();
}

void DefaultFileAccess::createDirectory(const std::string& absolutePath) const
{
    std::filesystem::create_directory(absolutePath);
}

void DefaultFileAccess::remove(const std::string& absolutePath) const
{
    std::filesystem::remove_all(absolutePath);
}

void DefaultFileAccess::rename(const std::string& absolutePath, const std::string& newAbsolutePath) const
{
    if (exists(absolutePath))
    {
        std::filesystem::rename(absolutePath, newAbsolutePath);
    }
}

bool DefaultFileAccess::exists(const std::string& absolutePath) const
{
    return std::filesystem::exists(absolutePath);
}

bool DefaultFileAccess::isRegularFile(const std::string& absolutePath) const
{
    return std::filesystem::is_regular_file(absolutePath);
}
bool DefaultFileAccess::isDirectory(const std::string& absolutePath) const
{
    return std::filesystem::is_directory(absolutePath);
}

std::vector<std::string> DefaultFileAccess::getAllPathsFromDirectory(const std::string& absolutePath) const
{
    const auto allPaths = getAllPaths(absolutePath);

    std::vector<std::string> pathsAsStrings;

    for (const auto& path : allPaths)
    {
        pathsAsStrings.push_back(path.string());
    }

    return pathsAsStrings;
}

std::vector<std::string> DefaultFileAccess::getAllFilenamesFromDirectory(const std::string& absolutePath) const
{
    return filterFilenames(getAllPaths(absolutePath));
}

std::vector<std::string>
DefaultFileAccess::getFilteredFilenamesFromDirectory(const std::string& absolutePath,
                                                     const std::vector<std::string>& extensions) const
{
    const auto filenames = filterFilenames(getAllPaths(absolutePath));

    auto filteredFilenames = filterByExtensions(filenames, extensions);

    return filteredFilenames;
}

std::vector<std::string> DefaultFileAccess::filterByExtensions(const std::vector<std::string>& fileNames,
                                                               const std::vector<std::string>& extensions) const
{
    std::vector<std::string> filteredFileNames;

    for (const auto& fileName : fileNames)
    {
        if (containsAnyOfExtensions(fileName, extensions))
        {
            filteredFileNames.push_back(fileName);
        }
    }

    if (filteredFileNames.empty())
    {
        return fileNames;
    }

    return filteredFileNames;
}

bool DefaultFileAccess::containsAnyOfExtensions(const std::filesystem::path& filename,
                                                const std::vector<std::string>& extensions) const
{
    return boost::algorithm::any_of(extensions,
                                    [&](const auto& extension) { return filename.extension() == extension; });
}

std::vector<std::string> DefaultFileAccess::filterFilenames(const std::vector<std::filesystem::path>& filePaths) const
{
    std::vector<std::string> fileNames;

    for (const auto& filePath : filePaths)
    {
        if (std::filesystem::is_regular_file(filePath))
        {
            const auto fileName = filePath.filename().string();

            fileNames.emplace_back(fileName);
        }
    }

    return fileNames;
}

std::vector<std::filesystem::path> DefaultFileAccess::getAllPaths(const std::string& absolutePath) const
{
    std::filesystem::path directoryPath(absolutePath);

    std::vector<std::filesystem::path> listOfFiles;

    if (not std::filesystem::exists(directoryPath) || not isDirectory(directoryPath.string()))
    {
        throw exceptions::DirectoryNotFound(fmt::format("directory not found", absolutePath));
    }

    for (auto& p : std::filesystem::recursive_directory_iterator(directoryPath))
    {
        listOfFiles.push_back(p.path());
    }

    return listOfFiles;
}
}
