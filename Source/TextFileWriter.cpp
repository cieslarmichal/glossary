#include "TextFileWriter.h"

#include <fstream>

namespace
{
const std::string fileNotFoundMessage{"File not found: "};
}

TextFileWriter::TextFileWriter(std::string path) : filePath(std::move(path))
{
}

void TextFileWriter::write(const std::string &dataToWrite) const
{
    std::ofstream fileStream{filePath};

    tryToWrite(fileStream, dataToWrite);
}

void TextFileWriter::append(const std::string &dataToAppend) const
{
    std::ofstream fileStream{filePath, std::ofstream::app};

    tryToWrite(fileStream, dataToAppend);
}

void TextFileWriter::tryToWrite(std::ofstream &fileStream, const std::string &data) const
{
    if (fileStream.is_open())
    {
        fileStream << data;
    }
    else
    {
        throw FileNotFound(fileNotFoundMessage + filePath);
    }
}


