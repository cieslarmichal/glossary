#include "DefaultFileAccessFactory.h"

#include "DefaultFileAccess.h"

namespace common::fileSystem
{
std::unique_ptr<FileAccess> DefaultFileAccessFactory::createDefaultFileAccess() const
{
    return std::make_unique<DefaultFileAccess>();
}
}