#include "DefaultTranslationRepository.h"

namespace glossary::translationRepository
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

boost::optional<Translation> DefaultTranslationRepository::getTranslation(const SourceText& sourceText) const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->getTranslation(sourceText);
}

bool DefaultTranslationRepository::containsTranslation(const SourceText& sourceText) const
{
    std::lock_guard<std::mutex> lockGuard(lock);
    return storage->contains(sourceText);
}

}
