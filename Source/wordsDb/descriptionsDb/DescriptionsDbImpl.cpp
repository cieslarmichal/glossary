#include "wordsDb/descriptionsDb/DescriptionsDbImpl.h"

namespace wordsDb::descriptionsDb
{
DescriptionsDbImpl::DescriptionsDbImpl(
    std::unique_ptr<DescriptionsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void DescriptionsDbImpl::addWord(const WordDescription& word) const
{
    storage->addWord(word);
}

boost::optional<WordDescription>
DescriptionsDbImpl::getWord(const EnglishWord& englishWord) const
{
    return storage->getWord(englishWord);
}

bool DescriptionsDbImpl::contains(const EnglishWord& englishWord) const
{
    return storage->contains(englishWord);
}
}
