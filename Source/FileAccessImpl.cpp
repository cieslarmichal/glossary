#include "FileAccessImpl.h"

#include <fstream>
#include <sstream>

#include "exceptions/FileNotFound.h"

namespace
{
enum class Result
{
    Success,
    Failure
};

Result tryToWrite(std::ofstream& fileStream, const std::string& data);
const std::string fileNotFoundMessage{"File not found: "};
}

void FileAccessImpl::write(const std::string& path,
                           const std::string& content) const
{
    std::ofstream fileStream{path};

    if (tryToWrite(fileStream, content) == Result::Failure)
    {
        throw exceptions::FileNotFound(fileNotFoundMessage + path);
    }
}

void FileAccessImpl::append(const std::string& path,
                            const std::string& content) const
{
    std::ofstream fileStream{path, std::ofstream::app};

    if (tryToWrite(fileStream, content) == Result::Failure)
    {
        throw exceptions::FileNotFound(fileNotFoundMessage + path);
    }
}

std::string FileAccessImpl::readContent(const std::string& path) const
{
    std::ifstream fileStream{path};
    std::stringstream buffer;

    if (fileStream.is_open())
    {
        buffer << fileStream.rdbuf();
    }
    else
    {
        throw exceptions::FileNotFound(fileNotFoundMessage + path);
    }

    return buffer.str();
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
