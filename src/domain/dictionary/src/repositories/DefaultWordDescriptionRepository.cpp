#include "DefaultWordDescriptionRepository.h"

namespace glossary::dictionary
{
DefaultWordDescriptionRepository::DefaultWordDescriptionRepository(
    std::unique_ptr<WordsDescriptionsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void DefaultWordDescriptionRepository::addWordDescription(const WordDescription& wordDescription)
{
    std::lock_guard<std::mutex> lockGuard(lock);
    storage->addWordDescription(wordDescription);
}

std::optional<WordDescription>
DefaultWordDescriptionRepository::getWordDescription(const std::string& englishWord) const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->getWordDescription(englishWord);
}
bool DefaultWordDescriptionRepository::contains(const std::string& englishWord) const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->contains(englishWord);
}

}
