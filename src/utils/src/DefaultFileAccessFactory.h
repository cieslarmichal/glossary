#pragma once

#include "FileAccessFactory.h"

namespace utils
{
class DefaultFileAccessFactory : public FileAccessFactory
{
public:
    std::unique_ptr<FileAccess> createDefaultFileAccess() const override;
    std::unique_ptr<FileAccess> createProjectFileAccess(const std::string& projectName) const override;
};
}