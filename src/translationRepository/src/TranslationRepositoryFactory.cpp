#include "TranslationRepositoryFactory.h"

#include "DefaultTranslationRepositoryFactory.h"

namespace translationRepository
{

std::unique_ptr<TranslationRepositoryFactory> TranslationRepositoryFactory::createTranslationRepositoryFactory(
    const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultTranslationRepositoryFactory>(fileAccess);
}
}
