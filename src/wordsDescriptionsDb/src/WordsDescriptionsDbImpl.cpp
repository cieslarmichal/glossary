#include "WordsDescriptionsDbImpl.h"

namespace wordsDescriptionsDb
{
WordsDescriptionsDbImpl::WordsDescriptionsDbImpl(std::unique_ptr<WordsDescriptionsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void WordsDescriptionsDbImpl::addWordDescription(const WordDescription& wordDescription)
{
    std::lock_guard<std::mutex> lockGuard(lock);
    storage->addWordDescription(wordDescription);
}

boost::optional<WordDescription>
WordsDescriptionsDbImpl::getWordDescription(const EnglishWord& englishWord) const
{
    return storage->getWordDescription(englishWord);
}

WordsDescriptions WordsDescriptionsDbImpl::getWordsDescriptions() const
{
    return storage->getWordsDescriptions();
}

bool WordsDescriptionsDbImpl::contains(const EnglishWord& englishWord) const
{
    return storage->contains(englishWord);
}

}
