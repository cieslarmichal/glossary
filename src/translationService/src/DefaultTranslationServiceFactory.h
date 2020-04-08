#pragma once

#include "TranslationServiceFactory.h"

namespace glossary::translationService
{
class DefaultTranslationServiceFactory : public TranslationServiceFactory
{
public:
    std::unique_ptr<TranslationRetrieverService> createTranslationService(
        const std::shared_ptr<translator::Translator>&,
        const std::shared_ptr<translationRepository::TranslationRepository>&) const override;
};
}
