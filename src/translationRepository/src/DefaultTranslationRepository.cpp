#include "DefaultTranslationRepository.h"

namespace translationRepository
{

DefaultTranslationRepository::DefaultTranslationRepository(std::unique_ptr<TranslationsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void DefaultTranslationRepository::addTranslation(Translation translation)
{
    storage->addTranslation(std::move(translation));
}

boost::optional<Translation> DefaultTranslationRepository::getTranslation(const SourceText& polishWord) const
{
    return storage->getTranslation(polishWord);
}

Translations DefaultTranslationRepository::getTranslations() const
{
    return storage->getTranslations();
}

}
