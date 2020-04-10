#pragma once

#include <memory>

#include "TranslationRetrieverService.h"
#include "translationRepository/TranslationRepository.h"
#include "translator/Translator.h"
#include "utils/FileAccess.h"

namespace glossary::translationService
{
class TranslationServiceFactory
{
public:
    virtual ~TranslationServiceFactory() = default;

    virtual std::unique_ptr<TranslationRetrieverService>
    createTranslationService(const std::shared_ptr<translator::Translator>&,
                             const std::shared_ptr<translationRepository::TranslationRepository>&) const = 0;

    static std::unique_ptr<TranslationServiceFactory>
    createTranslationServiceFactory(const std::shared_ptr<utils::FileAccess>&);
};
}