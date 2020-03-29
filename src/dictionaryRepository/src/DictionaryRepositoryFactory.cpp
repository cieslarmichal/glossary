#include "DictionaryRepositoryFactory.h"

#include "DefaultDictionaryRepositoryFactory.h"
#include "utils/FileAccess.h"

namespace dictionaryRepository
{
std::unique_ptr<DictionaryRepositoryFactory> DictionaryRepositoryFactory::createDictionaryRepositoryFactory(
    const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultDictionaryRepositoryFactory>(fileAccess);
}
}
