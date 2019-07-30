#pragma once

#include "FileWriter.h"
#include <stdexcept>

class TextFileWriter : public FileWriter
{
public:
    struct FileNotFound : std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    void write(const std::string &, const std::string &) const override;
};


