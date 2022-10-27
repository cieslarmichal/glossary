#include "DefaultDictionaryService.h"

namespace glossary::dictionary
{

DefaultDictionaryService::DefaultDictionaryService(std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit,
                                                   std::unique_ptr<DictionaryNamesRetriever> namesRetriever,
                                                   std::unique_ptr<DictionaryWordsRetriever> wordsRetriever,
                                                   std::unique_ptr<RandomDictionaryWordRetriever> randomWordRetriever,
                                                   std::unique_ptr<DictionaryWordsReader> dictionaryWordsReaderInit,
                                                   std::unique_ptr<ObserverService> observerServiceInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)},
      dictionaryNamesRetriever{std::move(namesRetriever)},
      dictionaryWordsRetriever{std::move(wordsRetriever)},
      randomDictionaryWordRetriever{std::move(randomWordRetriever)},
      dictionaryWordsReader{std::move(dictionaryWordsReaderInit)},
      observerService{std::move(observerServiceInit)}
{
}

std::optional<Dictionary> DefaultDictionaryService::getDictionary(const std::string& dictionaryName) const
{
    return dictionaryRepository->getDictionary(dictionaryName);
}

std::vector<Dictionary> DefaultDictionaryService::getDictionaries() const
{
    return dictionaryRepository->getDictionaries();
}

std::vector<std::string> DefaultDictionaryService::getDictionaryNames() const
{
    return dictionaryNamesRetriever->retrieveDictionaryNames();
}

std::vector<std::string>
DefaultDictionaryService::getDictionaryNamesContainingEnglishWord(const std::string& englishWord) const
{
    return dictionaryNamesRetriever->retrieveDictionaryNamesContainingEnglishWord(englishWord);
}

std::vector<std::string> DefaultDictionaryService::getDictionaryNamesContainingEnglishWordTranslation(
    const std::string& englishWordTranslation) const
{
    return dictionaryNamesRetriever->retrieveDictionaryNamesContainingEnglishWordTranslation(englishWordTranslation);
}

std::optional<std::vector<DictionaryWord>>
DefaultDictionaryService::getDictionaryWords(const std::string& dictionaryName) const
{
    return dictionaryWordsRetriever->retrieveDictionaryWords(dictionaryName);
}

std::optional<std::vector<std::string>>
DefaultDictionaryService::getEnglishWords(const std::string& dictionaryName) const
{
    return dictionaryWordsRetriever->retrieveEnglishWords(dictionaryName);
}

std::vector<std::string> DefaultDictionaryService::getEnglishWords() const
{
    return dictionaryWordsRetriever->retrieveEnglishWords();
}

std::optional<DictionaryWord> DefaultDictionaryService::getRandomDictionaryWord() const
{
    return randomDictionaryWordRetriever->getRandomDictionaryWord();
}

std::optional<DictionaryWord> DefaultDictionaryService::getRandomDictionaryWord(const std::string& dictionaryName) const
{
    return randomDictionaryWordRetriever->getRandomDictionaryWord(dictionaryName);
}

void DefaultDictionaryService::addDictionary(const std::string& dictionaryName)
{
    dictionaryRepository->addDictionary(dictionaryName);
}

void DefaultDictionaryService::addDictionaryFromFile(const std::string& dictionaryName,
                                                     const std::string& dictionaryWordsPath)
{
    const auto dictionaryWordsFromFile = dictionaryWordsReader->readDictionaryWords(dictionaryWordsPath);
    
    dictionaryRepository->addDictionary({dictionaryName, dictionaryWordsFromFile});
    if (const auto englishWordsFromAddedDictionary = dictionaryWordsRetriever->retrieveEnglishWords(dictionaryName))
    {
        notifyObservers(*englishWordsFromAddedDictionary);
    }
}

void DefaultDictionaryService::addWordToDictionary(const DictionaryWord& dictionaryWord,
                                                   const std::string& dictionaryName)
{
    dictionaryRepository->addWordToDictionary(dictionaryWord, dictionaryName);
}

void DefaultDictionaryService::removeDictionary(const std::string& dictionaryName)
{
    dictionaryRepository->removeDictionary(dictionaryName);
}

void DefaultDictionaryService::removeWordFromDictionary(const std::string& englishWord,
                                                        const std::string& dictionaryName)
{
    dictionaryRepository->removeWordFromDictionary(englishWord, dictionaryName);
}

void DefaultDictionaryService::updateWordTranslationFromDictionary(const std::string& englishWord,
                                                                   const std::string& translation,
                                                                   const std::string& dictionaryName)
{
    dictionaryRepository->changeWordTranslationFromDictionary(englishWord, translation, dictionaryName);
}

void DefaultDictionaryService::synchronizeDictionaries()
{
    notifyObservers(dictionaryWordsRetriever->retrieveEnglishWords());
}

void DefaultDictionaryService::registerObserver(DictionaryObserver* observer)
{
    observerService->registerObserver(observer);
}

void DefaultDictionaryService::removeObserver(DictionaryObserver* observer)
{
    observerService->removeObserver(observer);
}

void DefaultDictionaryService::notifyObservers(const std::vector<std::string>& englishWords)
{
    observerService->notifyObservers(englishWords);
}

}
