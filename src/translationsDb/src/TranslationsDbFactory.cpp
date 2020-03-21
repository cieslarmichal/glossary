#include "TranslationsDbFactory.h"

#include "DefaultTranslationsDbFactory.h"

namespace translationsDb
{

std::unique_ptr<TranslationsDbFactory>
TranslationsDbFactory::createTranslationsDbFactory(const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultTranslationsDbFactory>(fileAccess);
}
}
