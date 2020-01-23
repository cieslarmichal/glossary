#include "wordsDb/descriptionsDb/DescriptionsDbImpl.h"

namespace wordsDb::descriptionsDb
{
DescriptionsDbImpl::DescriptionsDbImpl(
    std::unique_ptr<DescriptionsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void DescriptionsDbImpl::addWordDescription(const WordDescription& word) const
{
    storage->addWordDescription(word);
}

boost::optional<WordDescription>
DescriptionsDbImpl::getWordDescription(const EnglishWord& englishWord) const
{
    return storage->getWordDescription(englishWord);
}

WordsDescriptions DescriptionsDbImpl::getWordsDescriptions() const
{
    return storage->getWordsDescriptions();
}

bool DescriptionsDbImpl::contains(const EnglishWord& englishWord) const
{
    return storage->contains(englishWord);
}

}
