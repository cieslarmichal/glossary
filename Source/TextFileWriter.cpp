#include "TextFileWriter.h"

#include <fstream>

namespace
{
const std::string fileNotFoundMessage{"File not found: "};
}

void TextFileWriter::write(const std::string & filePath, const std::string & dataToWrite) const
{
    std::ofstream fileStream{filePath};

    if (fileStream.is_open())
    {
        fileStream << dataToWrite;
    }
    else
    {
        throw FileNotFound(fileNotFoundMessage + filePath);
    }
}
