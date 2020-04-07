#include "DefaultDictionarySynchronizer.h"

namespace glossary
{

DefaultDictionarySynchronizer::DefaultDictionarySynchronizer(
    std::shared_ptr<dictionaryService::DictionaryService> service,
    std::shared_ptr<WordDescriptionLoader> wordDescriptionLoader,
    std::shared_ptr<TranslationLoader> translationLoader)
    : dictionaryService{std::move(service)},
      wordDescriptionLoader{std::move(wordDescriptionLoader)},
      translationLoader{std::move(translationLoader)}
{
}

void DefaultDictionarySynchronizer::synchronizeDictionary(
    const dictionaryService::DictionaryName& dictionaryName)
{
    if (const auto englishWords = getEnglishWordsFromDictionary(dictionaryName))
    {
        if (dictionaryEnglishWordsNotEmpty(*englishWords))
        {
            wordDescriptionLoader->loadMissingWordsDescriptions(*englishWords);
            translationLoader->loadMissingTranslations(*englishWords);
        }
    }
}

void DefaultDictionarySynchronizer::synchronizeDictionaries()
{
    const auto englishWords = getEnglishWordsFromDictionaries();
    if (dictionaryEnglishWordsNotEmpty(englishWords))
    {
        wordDescriptionLoader->loadMissingWordsDescriptions(englishWords);
        translationLoader->loadMissingTranslations(englishWords);
    }
}

boost::optional<dictionaryService::EnglishWords> DefaultDictionarySynchronizer::getEnglishWordsFromDictionary(
    const dictionaryService::DictionaryName& dictionaryName) const
{
    return dictionaryService->getEnglishWords(dictionaryName);
}

dictionaryService::EnglishWords DefaultDictionarySynchronizer::getEnglishWordsFromDictionaries() const
{
    return dictionaryService->getEnglishWords();
}

bool DefaultDictionarySynchronizer::dictionaryEnglishWordsNotEmpty(
    const dictionaryService::EnglishWords& englishWords) const
{
    return not englishWords.empty();
}

}