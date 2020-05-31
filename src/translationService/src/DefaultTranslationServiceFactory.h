#pragma once

#include "TranslationServiceFactory.h"
#include "utils/FileAccess.h"

namespace glossary::translationService
{
class DefaultTranslationServiceFactory : public TranslationServiceFactory
{
public:
    explicit DefaultTranslationServiceFactory(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<TranslationService> createTranslationService(
        const std::shared_ptr<translator::Translator>&,
        const std::shared_ptr<translationRepository::TranslationRepository>&) const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}
