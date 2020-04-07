#pragma once

#include <memory>

#include "DictionarySynchronizer.h"
#include "TranslationLoader.h"
#include "WordDescriptionLoader.h"
#include "dictionaryService/DictionaryService.h"

namespace glossary
{
class DefaultDictionarySynchronizer : public DictionarySynchronizer
{
public:
    DefaultDictionarySynchronizer(std::shared_ptr<dictionaryService::DictionaryService>,
                                  std::shared_ptr<WordDescriptionLoader>, std::shared_ptr<TranslationLoader>);

    void synchronizeDictionary(const dictionaryService::DictionaryName&) override;
    void synchronizeDictionaries() override;

private:
    boost::optional<dictionaryService::EnglishWords>
    getEnglishWordsFromDictionary(const dictionaryService::DictionaryName&) const;
    dictionaryService::EnglishWords getEnglishWordsFromDictionaries() const;
    bool dictionaryEnglishWordsNotEmpty(const dictionaryService::EnglishWords&) const;

    std::shared_ptr<dictionaryService::DictionaryService> dictionaryService;
    std::shared_ptr<WordDescriptionLoader> wordDescriptionLoader;
    std::shared_ptr<TranslationLoader> translationLoader;
};

}