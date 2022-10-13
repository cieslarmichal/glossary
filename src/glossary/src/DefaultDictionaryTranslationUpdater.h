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
    DefaultDictionaryTranslationUpdater(std::shared_ptr<dictionaryService::DictionaryService>,
                                        std::shared_ptr<translationService::TranslationService>);

    void updateDictionaryWordTranslation(const dictionaryService::std::string&,
                                         const std::string& updatedTranslation,
                                         const dictionaryService::DictionaryName&) override;
    void updateDictionaryWordTranslation(const dictionaryService::std::string&,
                                         const dictionaryService::DictionaryName&) override;
    void updateDictionaryTranslations(const dictionaryService::DictionaryName&) override;

private:
    boost::optional<translation::TranslatedText> getTranslation(const dictionaryService::std::string&);
    bool dictionaryWordHasNoTranslation(const dictionaryService::DictionaryWord&) const;

    std::shared_ptr<dictionaryService::DictionaryService> dictionaryService;
    std::shared_ptr<translationService::TranslationService> translationService;
};
}