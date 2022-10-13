#pragma once

#include "FileAccessFactory.h"

namespace common::fileSystem
{
class DefaultFileAccessFactory : public FileAccessFactory
{
public:
    std::unique_ptr<FileAccess> createDefaultFileAccess() const override;
};
}