#include "DefaultWordsDescriptionsDbFactory.h"

#include "DefaultWordsDescriptionsDb.h"
#include "WordsDescriptionsJsonSerializer.h"
#include "WordsDescriptionsPersistentStorage.h"

namespace wordsDescriptionsDb
{
DefaultWordsDescriptionsDbFactory::DefaultWordsDescriptionsDbFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<WordsDescriptionsDb> DefaultWordsDescriptionsDbFactory::createWordsDescriptionDb() const
{
    return std::make_unique<DefaultWordsDescriptionsDb>(std::make_unique<WordsDescriptionsPersistentStorage>(
        fileAccess, std::make_shared<WordsDescriptionsJsonSerializer>()));
}

}