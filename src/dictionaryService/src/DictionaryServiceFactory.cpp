#include "DictionaryServiceFactory.h"

#include "../../common/fileSystem/include/FileAccess.h"
#include "DefaultDictionaryServiceFactory.h"

namespace glossary::dictionaryService
{
std::unique_ptr<DictionaryServiceFactory> DictionaryServiceFactory::createDictionaryServiceFactory(
    const std::shared_ptr<const common::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultDictionaryServiceFactory>(fileAccess);
}
}
