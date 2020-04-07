#include "DictionaryWithWordDescriptionsSynchronizer.h"

namespace glossary
{

DictionaryWithWordDescriptionsSynchronizer::DictionaryWithWordDescriptionsSynchronizer(
    std::shared_ptr<dictionaryService::DictionaryService> service,
    std::shared_ptr<WordDescriptionLoader> loader)
    : dictionaryService{std::move(service)}, wordDescriptionLoader{std::move(loader)}
{
}

void DictionaryWithWordDescriptionsSynchronizer::synchronizeDictionary(
    const dictionaryService::DictionaryName& dictionaryName)
{
    if (const auto englishWords = getEnglishWordsFromDictionary(dictionaryName))
    {
        if (dictionaryEnglishWordsNotEmpty(*englishWords))
            wordDescriptionLoader->loadWordsDescriptions(*englishWords);
    }
}

void DictionaryWithWordDescriptionsSynchronizer::synchronizeDictionaries()
{
    const auto englishWords = getEnglishWordsFromDictionaries();
    if (dictionaryEnglishWordsNotEmpty(englishWords))
        wordDescriptionLoader->loadWordsDescriptions(englishWords);
}

boost::optional<dictionaryService::EnglishWords>
DictionaryWithWordDescriptionsSynchronizer::getEnglishWordsFromDictionary(
    const dictionaryService::DictionaryName& dictionaryName) const
{
    return dictionaryService->getEnglishWords(dictionaryName);
}

dictionaryService::EnglishWords
DictionaryWithWordDescriptionsSynchronizer::getEnglishWordsFromDictionaries() const
{
    return dictionaryService->getEnglishWords();
}

bool DictionaryWithWordDescriptionsSynchronizer::dictionaryEnglishWordsNotEmpty(
    const dictionaryService::EnglishWords& englishWords) const
{
    return not englishWords.empty();
}

}