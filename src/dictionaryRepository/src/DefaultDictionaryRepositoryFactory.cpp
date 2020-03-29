#include "DefaultDictionaryRepositoryFactory.h"

#include "DefaultDictionaryRepository.h"
#include "DictionaryJsonSerializer.h"
#include "DictionaryPersistentStorage.h"
#include "DictionaryWordsTextFileReader.h"

namespace dictionaryRepository
{
DefaultDictionaryRepositoryFactory::DefaultDictionaryRepositoryFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}
std::unique_ptr<DictionaryRepository> DefaultDictionaryRepositoryFactory::createDictionaryRepository() const
{
    return std::make_unique<DefaultDictionaryRepository>(
        std::make_unique<DictionaryPersistentStorage>(fileAccess,
                                                      std::make_shared<DictionaryJsonSerializer>()),
        std::make_unique<DictionaryWordsTextFileReader>(fileAccess));
}
}
