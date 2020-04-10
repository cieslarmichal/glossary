#include "DefaultTranslationServiceFactory.h"

#include "DefaultTranslationRetrieverService.h"
#include "DefaultTranslatorConnectionChecker.h"
#include "TranslateApiKeyFileReader.h"

namespace glossary::translationService
{

DefaultTranslationServiceFactory::DefaultTranslationServiceFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<TranslationRetrieverService> DefaultTranslationServiceFactory::createTranslationService(
    const std::shared_ptr<translator::Translator>& translator,
    const std::shared_ptr<translationRepository::TranslationRepository>& translationRepository) const
{
    return std::make_unique<DefaultTranslationRetrieverService>(
        translator, translationRepository, std::make_unique<TranslateApiKeyFileReader>(fileAccess),
        std::make_unique<DefaultTranslatorConnectionChecker>(translator));
}

}