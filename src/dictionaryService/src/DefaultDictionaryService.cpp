#include "DefaultDictionaryService.h"

namespace glossary::dictionaryService
{

DefaultDictionaryService::DefaultDictionaryService(
    std::shared_ptr<repository::DictionaryRepository> dictionaryRepositoryInit,
    std::unique_ptr<DictionaryNamesRetriever> namesRetriever,
    std::unique_ptr<DictionaryWordsRetriever> wordsRetriever,
    std::unique_ptr<RandomDictionaryWordRetriever> randomWordRetriever,
    std::unique_ptr<csvFileReading::DictionaryWordsReader> dictionaryWordsReaderInit,
    std::unique_ptr<ObserverService> observerServiceInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)},
      dictionaryNamesRetriever{std::move(namesRetriever)},
      dictionaryWordsRetriever{std::move(wordsRetriever)},
      randomDictionaryWordRetriever{std::move(randomWordRetriever)},
      dictionaryWordsReader{std::move(dictionaryWordsReaderInit)},
      observerService{std::move(observerServiceInit)}
{
}

boost::optional<Dictionary> DefaultDictionaryService::getDictionary(const DictionaryName& dictionaryName) const
{
    return dictionaryRepository->getDictionary(dictionaryName);
}

Dictionaries DefaultDictionaryService::getDictionaries() const
{
    return dictionaryRepository->getDictionaries();
}

DictionaryNames DefaultDictionaryService::getDictionaryNames() const
{
    return dictionaryNamesRetriever->retrieveDictionaryNames();
}

boost::optional<DictionaryWords>
DefaultDictionaryService::getDictionaryWords(const DictionaryName& dictionaryName) const
{
    return dictionaryWordsRetriever->retrieveDictionaryWords(dictionaryName);
}

boost::optional<EnglishWords>
DefaultDictionaryService::getEnglishWords(const DictionaryName& dictionaryName) const
{
    return dictionaryWordsRetriever->retrieveEnglishWords(dictionaryName);
}

EnglishWords DefaultDictionaryService::getEnglishWords() const
{
    return dictionaryWordsRetriever->retrieveEnglishWords();
}

boost::optional<DictionaryWord> DefaultDictionaryService::getRandomDictionaryWord() const
{
    return randomDictionaryWordRetriever->getRandomDictionaryWord();
}

boost::optional<DictionaryWord>
DefaultDictionaryService::getRandomDictionaryWord(const DictionaryName& dictionaryName) const
{
    return randomDictionaryWordRetriever->getRandomDictionaryWord(dictionaryName);
}

void DefaultDictionaryService::addDictionary(const DictionaryName& dictionaryName)
{
    dictionaryRepository->addDictionary(dictionaryName);
}

void DefaultDictionaryService::addDictionaryFromFile(const DictionaryName& dictionaryName,
                                                     const std::string& dictionaryWordsPath)
{
    if (const auto dictionaryWordsFromFile = dictionaryWordsReader->readDictionaryWords(dictionaryWordsPath))
    {
        dictionaryRepository->addDictionary({dictionaryName, *dictionaryWordsFromFile});
        if (const auto englishWordsFromAddedDictionary =
                dictionaryWordsRetriever->retrieveEnglishWords(dictionaryName))
        {
            notifyObservers(*englishWordsFromAddedDictionary);
        }
    }
}

void DefaultDictionaryService::addWordToDictionary(const DictionaryWord& dictionaryWord,
                                                   const DictionaryName& dictionaryName)
{
    dictionaryRepository->addWordToDictionary(dictionaryWord, dictionaryName);
}

void DefaultDictionaryService::removeDictionary(const DictionaryName& dictionaryName)
{
    dictionaryRepository->removeDictionary(dictionaryName);
}

void DefaultDictionaryService::removeWordFromDictionary(const EnglishWord& englishWord,
                                                        const DictionaryName& dictionaryName)
{
    dictionaryRepository->removeWordFromDictionary(englishWord, dictionaryName);
}

void DefaultDictionaryService::updateWordTranslationFromDictionary(const EnglishWord& englishWord,
                                                                   const std::string& translation,
                                                                   const DictionaryName& dictionaryName)
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

void DefaultDictionaryService::notifyObservers(const EnglishWords& englishWords)
{
    observerService->notifyObservers(englishWords);
}

}