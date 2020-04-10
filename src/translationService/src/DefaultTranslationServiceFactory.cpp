#include "DefaultTranslationServiceFactory.h"

#include "DefaultTranslationRetrieverService.h"
#include "GoogleTranslateApiKeyFileReader.h"

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
        translator, translationRepository, std::make_unique<GoogleTranslateApiKeyFileReader>(fileAccess));
}

}