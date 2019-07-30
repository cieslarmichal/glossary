#include "TextFileWriter.h"

#include <fstream>

void TextFileWriter::write(const std::string & filePath, const std::string & dataToWrite) const
{
    std::ofstream fileStream{filePath};

    if (fileStream.is_open())
    {
        fileStream << dataToWrite;
    }
    else
    {
        throw FileNotFound("File not found: " + filePath);
    }
}
