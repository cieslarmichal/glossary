#include "DefaultTranslationServiceFactory.h"

#include "DefaultApiKeyLocationUpdater.h"
#include "DefaultTranslationService.h"
#include "DefaultTranslatorConnectionChecker.h"
#include "TranslateApiKeyFileReader.h"

namespace glossary::translationService
{

DefaultTranslationServiceFactory::DefaultTranslationServiceFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<TranslationService> DefaultTranslationServiceFactory::createTranslationService(
    const std::shared_ptr<translator::Translator>& translator,
    const std::shared_ptr<translationRepository::TranslationRepository>& translationRepository) const
{
    return std::make_unique<DefaultTranslationService>(
        translator, translationRepository, std::make_unique<TranslateApiKeyFileReader>(fileAccess),
        std::make_unique<DefaultTranslatorConnectionChecker>(translator),
        std::make_unique<DefaultApiKeyLocationUpdater>(fileAccess));
}

}