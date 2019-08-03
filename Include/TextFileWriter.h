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

    explicit TextFileWriter(std::string);

    void write(const std::string &) const override;
    void append(const std::string &) const override;

private:
    void tryToWrite(std::ofstream &, const std::string &) const;

    const std::string filePath;
};


