#include "TranslationServiceFactory.h"

#include "DefaultTranslationServiceFactory.h"

namespace glossary::translationService
{
std::unique_ptr<TranslationServiceFactory> TranslationServiceFactory::createTranslationServiceFactory(
    const std::shared_ptr<utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultTranslationServiceFactory>(fileAccess);
}
}