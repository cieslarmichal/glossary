#include "DefaultWordDescriptionRepository.h"

namespace wordDescriptionRepository
{
DefaultWordDescriptionRepository::DefaultWordDescriptionRepository(std::unique_ptr<WordsDescriptionsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void DefaultWordDescriptionRepository::addWordDescription(const WordDescription& wordDescription)
{
    std::lock_guard<std::mutex> lockGuard(lock);
    storage->addWordDescription(wordDescription);
}

boost::optional<WordDescription>
DefaultWordDescriptionRepository::getWordDescription(const EnglishWord& englishWord) const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->getWordDescription(englishWord);
}

WordsDescriptions DefaultWordDescriptionRepository::getWordsDescriptions() const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->getWordsDescriptions();
}

bool DefaultWordDescriptionRepository::contains(const EnglishWord& englishWord) const
{
    return storage->contains(englishWord);
}

}
