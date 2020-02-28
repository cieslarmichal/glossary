#include "DefaultFileAccessFactory.h"

#include "FileAccessImpl.h"

namespace utils
{
std::unique_ptr<FileAccess> DefaultFileAccessFactory::createFileAccess(const std::string& projectName) const
{
    return std::make_unique<FileAccessImpl>(projectName);
}
}