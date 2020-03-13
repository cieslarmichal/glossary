#include "FileAccessImpl.h"

#include <experimental/filesystem>
#include <fstream>
#include <sstream>

#include "GetProjectPath.h"
#include "exceptions/DirectoryNotFound.h"
#include "exceptions/FileNotFound.h"

namespace fs = std::experimental::filesystem;

namespace utils
{
namespace
{
enum class Result
{
    Success,
    Failure
};

Result tryToWrite(std::ofstream& fileStream, const std::string& data);

const std::string directoryNotFoundMessage{"Directory not found "};
const std::string fileNotFoundMessage{"File not found "};
const std::string fileNotFoundReadingMessage{fileNotFoundMessage + "while reading: "};
const std::string fileNotFoundWritingMessage{fileNotFoundMessage + "while writing: "};
const std::string fileNotFoundAppendingMessage{fileNotFoundMessage + "while appending: "};
}

FileAccessImpl::FileAccessImpl(const std::string& name) : projectPath{getProjectPath(name)} {}

void FileAccessImpl::write(const std::string& relativePath, const std::string& content) const
{
    const std::string absolutePath = getAbsolutePath(relativePath);

    std::ofstream fileStream{absolutePath};

    if (tryToWrite(fileStream, content) == Result::Failure)
    {
        throw exceptions::FileNotFound(fileNotFoundWritingMessage + absolutePath +
                                       " with project path: " + projectPath);
    }
}

void FileAccessImpl::append(const std::string& relativePath, const std::string& content) const
{
    const std::string absolutePath = getAbsolutePath(relativePath);
    std::ofstream fileStream{absolutePath, std::ofstream::app};

    if (tryToWrite(fileStream, content) == Result::Failure)
    {
        throw exceptions::FileNotFound(fileNotFoundAppendingMessage + absolutePath +
                                       " with project path: " + projectPath);
    }
}

std::string FileAccessImpl::readContent(const std::string& relativePath) const
{
    const std::string absolutePath = getAbsolutePath(relativePath);
    std::ifstream fileStream{absolutePath};
    std::stringstream buffer;

    if (fileStream.is_open())
    {
        buffer << fileStream.rdbuf();
    }
    else
    {
        throw exceptions::FileNotFound(fileNotFoundReadingMessage + absolutePath +
                                       " with project path: " + projectPath);
    }

    return buffer.str();
}

void FileAccessImpl::createDirectory(const std::string& relativePath) const
{
    const std::string absolutePath = getAbsolutePath(relativePath);
    fs::create_directory(absolutePath); // returns false if not created
}

void FileAccessImpl::remove(const std::string& relativePath) const
{
    const std::string absolutePath = getAbsolutePath(relativePath);
    fs::remove_all(absolutePath);
}

void FileAccessImpl::rename(const std::string& path, const std::string& newPath) const
{
    if (not exists(path))
    {
        return;
    }
    const std::string oldAbsolutePath = getAbsolutePath(path);
    const std::string newAbsolutePath = getAbsolutePath(newPath);
    fs::rename(oldAbsolutePath, newAbsolutePath);
}

bool FileAccessImpl::exists(const std::string& relativePath) const
{
    const std::string absolutePath = getAbsolutePath(relativePath);
    return fs::exists(absolutePath);
}

std::vector<std::string> FileAccessImpl::getDirectoryFilepaths(const std::string& relativePath) const
{
    const std::string absolutePath = getAbsolutePath(relativePath);
    fs::path directoryPath(absolutePath);

    std::vector<std::string> listOfFiles;

    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath))
    {
        throw exceptions::DirectoryNotFound{directoryNotFoundMessage + absolutePath +
                                            "with project path: " + projectPath};
    }

    for (auto& p : fs::recursive_directory_iterator(directoryPath))
    {
        listOfFiles.push_back(p.path().string());
    }
    return listOfFiles;
}

std::vector<std::string>
FileAccessImpl::getDirectoryFilenames(const std::string& path,
                                      const std::vector<std::string>& extensions) const
{
    const auto filteredFilepaths = fileExtensionsFilter.filter(getDirectoryFilepaths(path), extensions);
    const auto filenames = filenamePathFilter.filter(filteredFilepaths);
    return filenames;
}

std::string FileAccessImpl::getAbsolutePath(const std::string& relativePath) const
{
    return projectPath + relativePath;
}

namespace
{

Result tryToWrite(std::ofstream& fileStream, const std::string& data)
{
    if (fileStream.is_open())
    {
        fileStream << data;
        return Result::Success;
    }
    return Result::Failure;
}

}
}