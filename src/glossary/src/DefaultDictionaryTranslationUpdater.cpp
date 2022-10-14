#include "DefaultDictionaryTranslationUpdater.h"

namespace glossary
{

DefaultDictionaryTranslationUpdater::DefaultDictionaryTranslationUpdater(
    std::shared_ptr<dictionary::DictionaryService> dictionaryServiceInit,
    std::shared_ptr<translationService::TranslationService> translationServiceInit)
    : dictionaryService{std::move(dictionaryServiceInit)},
      translationService{std::move(translationServiceInit)}
{
}

void DefaultDictionaryTranslationUpdater::updateDictionaryWordTranslation(
    const dictionary::std::string& englishWord, const std::string& updatedTranslation,
    const dictionary::std::string& dictionaryName)
{
    dictionaryService->updateWordTranslationFromDictionary(englishWord, updatedTranslation, dictionaryName);
}

void DefaultDictionaryTranslationUpdater::updateDictionaryWordTranslation(
    const dictionary::std::string& englishWord,
    const dictionary::std::string& dictionaryName)
{
    if (const auto translation = getTranslation(englishWord))
    {
        dictionaryService->updateWordTranslationFromDictionary(englishWord, *translation, dictionaryName);
    }
}

void DefaultDictionaryTranslationUpdater::updateDictionaryTranslations(
    const dictionary::std::string& dictionaryName)
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

std::optional<translation::TranslatedText>
DefaultDictionaryTranslationUpdater::getTranslation(const dictionary::std::string& englishWord)
{
    return translationService->retrieveTranslation(englishWord, translation::SourceLanguage::English,
                                                   translation::TargetLanguage::Polish);
}

bool DefaultDictionaryTranslationUpdater::dictionaryWordHasNoTranslation(
    const dictionary::DictionaryWord& dictionaryWord) const
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