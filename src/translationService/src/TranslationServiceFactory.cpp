#include "TranslationServiceFactory.h"

#include "DefaultTranslationServiceFactory.h"

namespace glossary::translationService
{
std::unique_ptr<TranslationServiceFactory> TranslationServiceFactory::createTranslationServiceFactory()
{
    return std::unique_ptr<DefaultTranslationServiceFactory>();
}
}