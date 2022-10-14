#include "DictionaryServiceFactory.h"

#include "DefaultDictionaryServiceFactory.h"
#include "FileAccess.h"

namespace glossary::dictionary
{
std::unique_ptr<DictionaryServiceFactory> DictionaryServiceFactory::createDictionaryServiceFactory(
    const std::shared_ptr<const common::fileSystem::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultDictionaryServiceFactory>(fileAccess);
}
}
