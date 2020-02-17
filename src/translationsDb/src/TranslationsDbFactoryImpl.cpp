#include "TranslationsDbFactoryImpl.h"

#include "TranslationsDbImpl.h"
#include "TranslationsPersistentStorage.h"
#include "TranslationsSerializerImpl.h"

namespace translationsDb
{

TranslationsDbFactoryImpl::TranslationsDbFactoryImpl(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<TranslationsDb>
TranslationsDbFactoryImpl::createTranslationsDb() const
{
    return std::make_unique<TranslationsDbImpl>(
        std::make_unique<TranslationsPersistentStorage>(
            fileAccess, std::make_shared<TranslationsSerializerImpl>()));
}

}