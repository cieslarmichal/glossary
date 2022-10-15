#pragma once

#include <memory>

#include "DictionaryTranslationUpdater.h"
#include "dictionaryService/DictionaryService.h"
#include "translationService/TranslationService.h"

namespace glossary
{
class DefaultDictionaryTranslationUpdater : public DictionaryTranslationUpdater
{
public:
    DefaultDictionaryTranslationUpdater(std::shared_ptr<dictionary::DictionaryService>,
                                        std::shared_ptr<translationService::TranslationService>);

    void updateDictionaryWordTranslation(const std::string&,
                                         const std::string& updatedTranslation,
                                         const std::string&) override;
    void updateDictionaryWordTranslation(const std::string&,
                                         const std::string&) override;
    void updateDictionaryTranslations(const std::string&) override;

private:
    std::optional<translation::TranslatedText> getTranslation(const std::string&);
    bool dictionaryWordHasNoTranslation(const dictionary::DictionaryWord&) const;

    std::shared_ptr<dictionary::DictionaryService> dictionaryService;
    std::shared_ptr<translationService::TranslationService> translationService;
};
}