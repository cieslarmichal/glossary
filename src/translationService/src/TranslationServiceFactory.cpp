#include "TranslationServiceFactory.h"

#include "DefaultTranslationServiceFactory.h"

namespace glossary::translationService
{
std::unique_ptr<TranslationServiceFactory> TranslationServiceFactory::createTranslationServiceFactory()
{
    return std::make_unique<DefaultTranslationServiceFactory>();
}
}