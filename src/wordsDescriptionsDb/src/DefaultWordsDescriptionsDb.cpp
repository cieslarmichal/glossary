#include "DefaultWordsDescriptionsDb.h"

namespace wordsDescriptionsDb
{
DefaultWordsDescriptionsDb::DefaultWordsDescriptionsDb(std::unique_ptr<WordsDescriptionsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void DefaultWordsDescriptionsDb::addWordDescription(const WordDescription& wordDescription)
{
    std::lock_guard<std::mutex> lockGuard(lock);
    storage->addWordDescription(wordDescription);
}

boost::optional<WordDescription>
DefaultWordsDescriptionsDb::getWordDescription(const EnglishWord& englishWord) const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->getWordDescription(englishWord);
}

WordsDescriptions DefaultWordsDescriptionsDb::getWordsDescriptions() const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->getWordsDescriptions();
}

bool DefaultWordsDescriptionsDb::contains(const EnglishWord& englishWord) const
{
    return storage->contains(englishWord);
}

}
