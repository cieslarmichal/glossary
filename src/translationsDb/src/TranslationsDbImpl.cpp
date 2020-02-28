#include "TranslationsDbImpl.h"

namespace translationsDb
{

TranslationsDbImpl::TranslationsDbImpl(
    std::unique_ptr<TranslationsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void TranslationsDbImpl::addTranslation(Translation translation)
{
    storage->addTranslation(std::move(translation));
}

boost::optional<Translation>
TranslationsDbImpl::getTranslation(const SourceText& polishWord) const
{
    return storage->getTranslation(polishWord);
}

Translations TranslationsDbImpl::getTranslations() const
{
    return storage->getTranslations();
}

}