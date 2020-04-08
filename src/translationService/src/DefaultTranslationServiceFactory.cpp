#include "DefaultTranslationServiceFactory.h"

#include "DefaultTranslationRetrieverService.h"

namespace glossary::translationService
{

std::unique_ptr<TranslationRetrieverService> DefaultTranslationServiceFactory::createTranslationService(
    const std::shared_ptr<translator::Translator>& translator,
    const std::shared_ptr<translationRepository::TranslationRepository>& translationRepository) const
{
    return std::make_unique<DefaultTranslationRetrieverService>(translator, translationRepository);
}

}