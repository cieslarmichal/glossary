#include "TranslationsDbImpl.h"

#include "plog/Log.h"

namespace translationsDb
{

TranslationsDbImpl::TranslationsDbImpl(std::unique_ptr<TranslationsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

void TranslationsDbImpl::addTranslation(Translation translation)
{
    LOG_DEBUG << "Adding translation: " << translation << " to database";
    storage->addTranslation(std::move(translation));
}

boost::optional<Translation> TranslationsDbImpl::getTranslation(const SourceText& polishWord) const
{
    LOG_DEBUG << "Getting translation for text: " << polishWord;
    return storage->getTranslation(polishWord);
}

Translations TranslationsDbImpl::getTranslations() const
{
    LOG_DEBUG << "Getting all stored translations";
    return storage->getTranslations();
}

}
