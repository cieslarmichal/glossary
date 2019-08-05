#pragma once

#include "FileAccess.h"
#include <stdexcept>

class FileAccessImpl : public FileAccess
{
public:
    struct FileNotFound : std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    void write(const std::string & path, const std::string & content) const override;
    void append(const std::string & path, const std::string & content) const override;
    std::string readContent(const std::string & path) const override;
//    bool exists(const std::string & path) const override;
//    void tryRemove(const std::string & path) const override;
//    void remove(const std::string & path) const override;
};


