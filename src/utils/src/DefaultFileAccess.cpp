#include "DefaultFileAccess.h"

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

void DefaultFileAccess::write(const std::string& absolutePath, const std::string& content) const
{
    std::ofstream fileStream{absolutePath};

    if (tryToWrite(fileStream, content) == Result::Failure)
    {
        throw exceptions::FileNotFound(fileNotFoundWritingMessage + absolutePath);
    }
}

void DefaultFileAccess::append(const std::string& absolutePath, const std::string& content) const
{
    std::ofstream fileStream{absolutePath, std::ofstream::app};

    if (tryToWrite(fileStream, content) == Result::Failure)
    {
        throw exceptions::FileNotFound(fileNotFoundAppendingMessage + absolutePath);
    }
}

std::string DefaultFileAccess::readContent(const std::string& absolutePath) const
{
    std::ifstream fileStream{absolutePath};
    std::stringstream buffer;

    if (fileStream.is_open())
    {
        buffer << fileStream.rdbuf();
    }
    else
    {
        throw exceptions::FileNotFound(fileNotFoundReadingMessage + absolutePath);
    }

    return buffer.str();
}

void DefaultFileAccess::createDirectory(const std::string& absolutePath) const
{
    fs::create_directory(absolutePath); // returns false if not created
}

void DefaultFileAccess::remove(const std::string& absolutePath) const
{
    fs::remove_all(absolutePath);
}

void DefaultFileAccess::rename(const std::string& absolutePath, const std::string& newAbsolutePath) const
{
    if (not exists(absolutePath))
    {
        return;
    }
    fs::rename(absolutePath, newAbsolutePath);
}

bool DefaultFileAccess::exists(const std::string& absolutePath) const
{
    return fs::exists(absolutePath);
}

std::vector<std::string> DefaultFileAccess::getAllPathsFromDirectory(const std::string& absolutePath) const
{
    fs::path directoryPath(absolutePath);

    std::vector<std::string> listOfFiles;

    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath))
    {
        throw exceptions::DirectoryNotFound{directoryNotFoundMessage + absolutePath};
    }

    for (auto& p : fs::recursive_directory_iterator(directoryPath))
    {
        listOfFiles.push_back(p.path().string());
    }
    return listOfFiles;
}

std::vector<std::string>
DefaultFileAccess::getAllFilenamesFromDirectory(const std::string& absolutePath,
                                                const std::vector<std::string>& extensions) const
{
    const auto filenames = filenamePathFilter.filterFilenames(getAllPathsFromDirectory(absolutePath));
    const auto filteredFilenames = fileExtensionsFilter.filterByExtensions(filenames, extensions);
    return filteredFilenames;
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