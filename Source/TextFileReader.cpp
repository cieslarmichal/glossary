#include "TextFileReader.h"

#include "boost/algorithm/string.hpp"
#include <sstream>
#include <fstream>

namespace
{
const std::string endOfLine{"\n"};
const std::string fileNotFoundMessage{"File not found: "};
}

std::string TextFileReader::read(const std::string &filePath) const
{
    std::ifstream fileStream{filePath};
    std::stringstream buffer;

    if (fileStream.is_open())
    {
        buffer << fileStream.rdbuf();
    }
    else
    {
        throw FileNotFound(fileNotFoundMessage + filePath);
    }

    return buffer.str();
}

std::vector<std::string> TextFileReader::readAndSplitLines(const std::string &filePath) const
{
    std::string fileContent = read(filePath);

    std::vector<std::string> splittedLines;

    boost::split(splittedLines, fileContent, boost::is_any_of(endOfLine));

    return splittedLines;
}


