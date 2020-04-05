#include "DictionaryServiceFactory.h"

#include "DefaultDictionaryServiceFactory.h"
#include "utils/FileAccess.h"

namespace glossary::dictionaryService
{
std::unique_ptr<DictionaryServiceFactory> DictionaryServiceFactory::createDictionaryServiceFactory(
    const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultDictionaryServiceFactory>(fileAccess);
}
}
