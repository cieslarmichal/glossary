#pragma once

#include <memory>

#include "FileAccess.h"

namespace common::fileSystem
{
class FileAccessFactory
{
public:
    virtual ~FileAccessFactory() = default;

    virtual std::unique_ptr<FileAccess> createDefaultFileAccess() const = 0;

    static std::unique_ptr<FileAccessFactory> createFileAccessFactory();
};
}