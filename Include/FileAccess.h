#pragma once

#include <string>

class FileAccess
{
public:
    virtual ~FileAccess() = default;

    virtual void write(const std::string & path, const std::string & content) const = 0;
    virtual void append(const std::string & path, const std::string & content) const = 0;
    virtual std::string readContent(const std::string & path) const = 0;
};
