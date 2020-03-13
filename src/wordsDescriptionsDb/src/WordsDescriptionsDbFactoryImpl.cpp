#include "WordsDescriptionsDbFactoryImpl.h"

#include "WordsDescriptionsDbImpl.h"
#include "WordsDescriptionsPersistentStorage.h"
#include "WordsDescriptionsSerializerImpl.h"

namespace wordsDescriptionsDb
{
WordsDescriptionsDbFactoryImpl::WordsDescriptionsDbFactoryImpl(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<WordsDescriptionsDb> WordsDescriptionsDbFactoryImpl::createWordsDescriptionDb() const
{
    return std::make_unique<WordsDescriptionsDbImpl>(std::make_unique<WordsDescriptionsPersistentStorage>(
        fileAccess, std::make_shared<WordsDescriptionsSerializerImpl>()));
}

}