#include "WordsDescriptionsDbImpl.h"
#include "plog/Log.h"

namespace wordsDescriptionsDb
{
WordsDescriptionsDbImpl::WordsDescriptionsDbImpl(std::unique_ptr<WordsDescriptionsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void WordsDescriptionsDbImpl::addWordDescription(const WordDescription& wordDescription)
{
    std::lock_guard<std::mutex> lockGuard(lock);
    LOG_DEBUG << "Adding word description for word:"<< wordDescription.englishWord<<" to database";
    storage->addWordDescription(wordDescription);
}

boost::optional<WordDescription>
WordsDescriptionsDbImpl::getWordDescription(const EnglishWord& englishWord) const
{
    LOG_DEBUG << "Getting word description for: "<< englishWord;
    return storage->getWordDescription(englishWord);
}

WordsDescriptions WordsDescriptionsDbImpl::getWordsDescriptions() const
{
    LOG_DEBUG << "Getting all stored word descriptions";
    return storage->getWordsDescriptions();
}

bool WordsDescriptionsDbImpl::contains(const EnglishWord& englishWord) const
{
    return storage->contains(englishWord);
}

}
