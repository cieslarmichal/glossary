#pragma once

#include "FileAccess.h"
#include <stdexcept>

class FileAccessImpl : public FileAccess
{
public:
    void write(const std::string & path, const std::string & content) const override;
    void append(const std::string & path, const std::string & content) const override;
    std::string readContent(const std::string & path) const override;
//    bool exists(const std::string & path) const override;
//    void tryRemove(const std::string & path) const override;
//    void remove(const std::string & path) const override;
};


