#pragma once

#include <vector>
#include "FileReader.h"
#include <stdexcept>

class TextFileReader : public FileReader
{
public:
    struct FileNotFound : std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    std::string read(const std::string &) const override;

    std::vector<std::string> readAndSplitLines(const std::string & filePath) const;
};


