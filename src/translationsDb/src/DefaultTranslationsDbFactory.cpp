#include "DefaultTranslationsDbFactory.h"

#include "DefaultTranslationsDb.h"
#include "TranslationsJsonSerializer.h"
#include "TranslationsPersistentStorage.h"

namespace translationsDb
{

DefaultTranslationsDbFactory::DefaultTranslationsDbFactory(std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<TranslationsDb> DefaultTranslationsDbFactory::createTranslationsDb() const
{
    return std::make_unique<DefaultTranslationsDb>(std::make_unique<TranslationsPersistentStorage>(
        fileAccess, std::make_shared<TranslationsJsonSerializer>()));
}

}