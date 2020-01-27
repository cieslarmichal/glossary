#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsDbImpl.h"

namespace wordsDb::wordsDescriptionsDb
{
WordsDescriptionsDbImpl::WordsDescriptionsDbImpl(
    std::unique_ptr<WordsDescriptionsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void WordsDescriptionsDbImpl::addWordDescription(
    const WordDescription& word) const
{
    storage->addWordDescription(word);
}

boost::optional<WordDescription> WordsDescriptionsDbImpl::getWordDescription(
    const EnglishWord& englishWord) const
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
