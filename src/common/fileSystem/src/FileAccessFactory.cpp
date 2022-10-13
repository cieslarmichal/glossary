#include "FileAccessFactory.h"

#include "DefaultFileAccessFactory.h"

namespace common::fileSystem
{
std::unique_ptr<FileAccessFactory> FileAccessFactory::createFileAccessFactory()
{
    return std::make_unique<DefaultFileAccessFactory>();
}
}