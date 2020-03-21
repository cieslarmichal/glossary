#include "DefaultTranslationsDb.h"

namespace translationsDb
{

DefaultTranslationsDb::DefaultTranslationsDb(std::unique_ptr<TranslationsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void DefaultTranslationsDb::addTranslation(Translation translation)
{
    storage->addTranslation(std::move(translation));
}

boost::optional<Translation> DefaultTranslationsDb::getTranslation(const SourceText& polishWord) const
{
    return storage->getTranslation(polishWord);
}

Translations DefaultTranslationsDb::getTranslations() const
{
    return storage->getTranslations();
}

}
