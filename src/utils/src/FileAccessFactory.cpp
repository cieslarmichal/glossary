#include "FileAccessFactory.h"

#include "FileAccessFactoryImpl.h"

namespace utils
{

std::unique_ptr<FileAccessFactory> FileAccessFactory::createFileAccessFactory()
{
    return std::make_unique<FileAccessFactoryImpl>();
}
}