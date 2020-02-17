#include "TranslationsDbFactory.h"

#include "TranslationsDbFactoryImpl.h"

namespace translationsDb
{

std::unique_ptr<TranslationsDbFactory>
TranslationsDbFactory::createTranslationsDbFactory(
    const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<TranslationsDbFactoryImpl>(fileAccess);
}
}
