#include "FileAccessImpl.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "exceptions/FileNotFound.h"
#include "GetProjectPath.h"

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

const std::string fileNotFoundMessage{"File not found "};
const std::string fileNotFoundReadingMessage{fileNotFoundMessage + "while reading: "};
const std::string fileNotFoundWritingMessage{fileNotFoundMessage + "while writing: "};
}

FileAccessImpl::FileAccessImpl(const std::string& name) : projectPath{getProjectPath(name)}
{
}

void FileAccessImpl::write(const std::string& relativePath,
                           const std::string& content) const
{
    const std::string absolutePath = getAbsolutePath(relativePath);
    std::cerr<<absolutePath;
    std::ofstream fileStream{absolutePath};

    if (tryToWrite(fileStream, content) == Result::Failure)
    {
        throw exceptions::FileNotFound(fileNotFoundWritingMessage + absolutePath + "with project path: " + projectPath);
    }
}

void FileAccessImpl::append(const std::string& relativePath,
                            const std::string& content) const
{
    const std::string absolutePath = getAbsolutePath(relativePath);
    std::ofstream fileStream{absolutePath, std::ofstream::app};

    if (tryToWrite(fileStream, content) == Result::Failure)
    {
        throw exceptions::FileNotFound(fileNotFoundWritingMessage + absolutePath + "with project path: " + projectPath);
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
        throw exceptions::FileNotFound(fileNotFoundReadingMessage + absolutePath + "with project path: " + projectPath);
    }

    return buffer.str();
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