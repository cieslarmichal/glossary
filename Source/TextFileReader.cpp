#include "TextFileReader.h"

#include "boost/algorithm/string.hpp"
#include <sstream>
#include <fstream>


std::string TextFileReader::read(const std::string &filePath) const
{
    std::ifstream fileStream{filePath};
    std::stringstream buffer;

    if (fileStream.is_open())
    {
        buffer << fileStream.rdbuf();
    } else
    {
        throw FileNotFound("File not found: " + filePath);
    }

    return buffer.str();
}

std::vector<std::string> TextFileReader::readAndSplitLines(const std::string &filePath) const
{
    std::vector<std::string> splittedLines;

    std::string fileContent = read(filePath);

    boost::split(splittedLines, fileContent, boost::is_any_of("\n"));

    return splittedLines;
}


