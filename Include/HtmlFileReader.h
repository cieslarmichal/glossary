#pragma once

#include "FileReader.h"

#include <string>
#include <stdexcept>

class HtmlFileReader : public FileReader
{
public:
    struct ConnectionFailed : std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    struct FileNotFound : std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    std::string read(const std::string &) const override;
};


