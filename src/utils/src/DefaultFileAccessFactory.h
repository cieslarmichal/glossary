#pragma once

#include "FileAccessFactory.h"

namespace utils
{
class DefaultFileAccessFactory : public FileAccessFactory
{
public:
    std::unique_ptr<FileAccess> createFileAccess(const std::string& projectName) const override;
};
}