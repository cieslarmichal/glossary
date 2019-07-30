#pragma once

#include <string>

class FileWriter
{
public:
    virtual ~FileWriter() = default;

    virtual void write(const std::string &, const std::string &) const = 0;
};


