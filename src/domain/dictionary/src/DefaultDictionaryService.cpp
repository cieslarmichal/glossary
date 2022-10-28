#include "DefaultDictionaryService.h"

namespace glossary::dictionary
{

DefaultDictionaryService::DefaultDictionaryService(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit,
    std::unique_ptr<DictionaryWordsCsvReader> dictionaryWordsReaderInit,
    std::unique_ptr<ObserverService> observerServiceInit,
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGeneratorInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)},
      dictionaryWordsCsvReader{std::move(dictionaryWordsReaderInit)},
      observerService{std::move(observerServiceInit)},
      randomNumberGenerator{std::move(randomNumberGeneratorInit)}
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
    const auto dictionaries = dictionaryRepository->getDictionaries();

    std::vector<std::string> dictionaryNames;

    for (const auto& dictionary : dictionaries)
    {
        dictionaryNames.emplace_back(dictionary.name);
    }

    return dictionaryNames;
}

std::optional<std::vector<DictionaryWord>>
DefaultDictionaryService::getDictionaryWords(const std::string& dictionaryName) const
{
    const auto dictionary = dictionaryRepository->getDictionary(dictionaryName);

    if (dictionary)
    {
        return dictionary->words;
    }

    return std::nullopt;
}

std::optional<std::vector<std::string>>
DefaultDictionaryService::getEnglishWords(const std::string& dictionaryName) const
{
    const auto dictionary = dictionaryRepository->getDictionary(dictionaryName);

    if (dictionary)
    {
        std::vector<std::string> englishWords;

        for (const auto& dictionaryWord : dictionary->words)
        {
            englishWords.emplace_back(dictionaryWord.englishWord);
        }

        return englishWords;
    }

    return std::nullopt;
}

std::vector<std::string> DefaultDictionaryService::getEnglishWords() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();

    std::vector<std::string> allDictionaryEnglishWords;

    for (const auto& dictionary : dictionaries)
    {
        std::vector<std::string> dictionaryEnglishWords;

        for (const auto& dictionaryWord : dictionary.words)
        {
            dictionaryEnglishWords.emplace_back(dictionaryWord.englishWord);
        }

        allDictionaryEnglishWords.insert(allDictionaryEnglishWords.end(), dictionaryEnglishWords.begin(),
                                         dictionaryEnglishWords.end());
    }

    return allDictionaryEnglishWords;
}

std::optional<DictionaryWord> DefaultDictionaryService::getRandomDictionaryWord() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();

    std::vector<DictionaryWord> allDictionariesWords;

    for (const auto& dictionary : dictionaries)
    {
        const auto& dictionaryWords = dictionary.words;

        allDictionariesWords.insert(allDictionariesWords.end(), dictionaryWords.begin(), dictionaryWords.end());
    }

    return randomizeDictionaryWord(allDictionariesWords);
}

std::optional<DictionaryWord> DefaultDictionaryService::getRandomDictionaryWord(const std::string& dictionaryName) const
{
    const auto dictionary = dictionaryRepository->getDictionary(dictionaryName);

    if (dictionary)
    {
        return randomizeDictionaryWord(dictionary->words);
    }

    return std::nullopt;
}

void DefaultDictionaryService::addDictionary(const std::string& dictionaryName)
{
    dictionaryRepository->addDictionary(dictionaryName);
}

void DefaultDictionaryService::addDictionaryFromFile(const std::string& dictionaryName,
                                                     const std::string& dictionaryWordsPath)
{
    const auto dictionaryWordsFromFile = dictionaryWordsCsvReader->readDictionaryWords(dictionaryWordsPath);

    dictionaryRepository->addDictionary({dictionaryName, dictionaryWordsFromFile});

    if (const auto englishWordsFromAddedDictionary = getEnglishWords(dictionaryName))
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
    notifyObservers(getEnglishWords());
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

std::optional<DictionaryWord>
DefaultDictionaryService::randomizeDictionaryWord(const std::vector<DictionaryWord>& dictionaryWords) const
{
    const auto randomIndex = randomNumberGenerator->generate(0, static_cast<int>(dictionaryWords.size() - 1));

    return dictionaryWords.at(randomIndex);
}

}
