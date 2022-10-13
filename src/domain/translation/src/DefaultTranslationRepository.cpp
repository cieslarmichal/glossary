#include "DefaultTranslationRepository.h"

namespace glossary::translation
{
DefaultTranslationRepository::DefaultTranslationRepository(std::unique_ptr<TranslationsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void DefaultTranslationRepository::addTranslation(Translation translation)
{
    std::lock_guard<std::mutex> lockGuard(lock);
    storage->addTranslation(std::move(translation));
}

std::optional<Translation> DefaultTranslationRepository::getTranslation(const std::string& sourceText) const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->getTranslation(sourceText);
}

bool DefaultTranslationRepository::containsTranslation(const std::string& sourceText) const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->contains(sourceText);
}

}
