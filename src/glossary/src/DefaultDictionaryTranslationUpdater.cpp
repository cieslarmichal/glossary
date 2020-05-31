#include "DefaultDictionaryTranslationUpdater.h"

namespace glossary
{

DefaultDictionaryTranslationUpdater::DefaultDictionaryTranslationUpdater(
    std::shared_ptr<dictionaryService::DictionaryService> dictionaryServiceInit,
    std::shared_ptr<translationService::TranslationService> translationServiceInit)
    : dictionaryService{std::move(dictionaryServiceInit)},
      translationService{std::move(translationServiceInit)}
{
}

void DefaultDictionaryTranslationUpdater::updateDictionaryWordTranslation(
    const dictionaryService::EnglishWord& englishWord, const std::string& updatedTranslation,
    const dictionaryService::DictionaryName& dictionaryName)
{
    dictionaryService->updateWordTranslationFromDictionary(englishWord, updatedTranslation, dictionaryName);
}

void DefaultDictionaryTranslationUpdater::updateDictionaryWordTranslation(
    const dictionaryService::EnglishWord& englishWord,
    const dictionaryService::DictionaryName& dictionaryName)
{
    if (const auto translation = getTranslation(englishWord))
    {
        dictionaryService->updateWordTranslationFromDictionary(englishWord, *translation, dictionaryName);
    }
}

void DefaultDictionaryTranslationUpdater::updateDictionaryTranslations(
    const dictionaryService::DictionaryName& dictionaryName)
{
    if (const auto dictionaryWords = dictionaryService->getDictionaryWords(dictionaryName))
    {
        for (const auto& dictionaryWord : *dictionaryWords)
        {
            if (dictionaryWordHasNoTranslation(dictionaryWord))
            {
                updateDictionaryWordTranslation(dictionaryWord.englishWord, dictionaryName);
            }
        }
    }
}

boost::optional<translator::TranslatedText>
DefaultDictionaryTranslationUpdater::getTranslation(const dictionaryService::EnglishWord& englishWord)
{
    return translationService->retrieveTranslation(englishWord, translator::SourceLanguage::English,
                                                   translator::TargetLanguage::Polish);
}

bool DefaultDictionaryTranslationUpdater::dictionaryWordHasNoTranslation(
    const dictionaryService::DictionaryWord& dictionaryWord) const
{
    if (const auto translation = dictionaryWord.translation)
    {
        if (not translation->empty())
        {
            return false;
        }
    }
    return true;
}

}