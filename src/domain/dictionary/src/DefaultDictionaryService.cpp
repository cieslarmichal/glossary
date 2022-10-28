#include "DefaultDictionaryService.h"

namespace glossary::dictionary
{

DefaultDictionaryService::DefaultDictionaryService(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit,
    std::unique_ptr<DictionaryWordsCsvReader> dictionaryWordsReaderInit,
    std::unique_ptr<ObserverService> observerServiceInit,
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGeneratorInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)},
      dictionaryWordsReader{std::move(dictionaryWordsReaderInit)},
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

std::vector<std::string>
DefaultDictionaryService::getDictionaryNamesContainingEnglishWord(const std::string& englishWord) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();

    std::vector<std::string> dictionaryNamesContainingEnglishWord;

    for (const auto& dictionary : dictionaries)
    {
        if (englishWordExistsInDictionary(englishWord, dictionary))
        {
            dictionaryNamesContainingEnglishWord.emplace_back(dictionary.name);
        }
    }

    return dictionaryNamesContainingEnglishWord;
}

std::vector<std::string> DefaultDictionaryService::getDictionaryNamesContainingEnglishWordTranslation(
    const std::string& englishWordTranslation) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();

    std::vector<std::string> dictionaryNamesContainingEnglishWordTranslation;

    for (const auto& dictionary : dictionaries)
    {
        if (englishWordTranslationExistsInDictionary(englishWordTranslation, dictionary))
        {
            dictionaryNamesContainingEnglishWordTranslation.emplace_back(dictionary.name);
        }
    }

    return dictionaryNamesContainingEnglishWordTranslation;
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
    const auto dictionaryWordsFromFile = dictionaryWordsReader->readDictionaryWords(dictionaryWordsPath);

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

bool DefaultDictionaryService::englishWordExistsInDictionary(const std::string& englishWordToFind,
                                                             const Dictionary& dictionary) const
{
    auto englishWordExists = std::find_if(dictionary.words.begin(), dictionary.words.end(),
                                          [&englishWordToFind](const DictionaryWord& dictionaryWord)
                                          { return dictionaryWord.englishWord == englishWordToFind; });

    return englishWordExists != dictionary.words.end();
}

bool DefaultDictionaryService::englishWordTranslationExistsInDictionary(const std::string& englishWordTranslation,
                                                                        const Dictionary& dictionary) const
{
    auto englishWordTranslationExists =
        std::find_if(dictionary.words.begin(), dictionary.words.end(),
                     [&englishWordTranslation](const DictionaryWord& dictionaryWord)
                     { return dictionaryWord.translation && (*dictionaryWord.translation == englishWordTranslation); });

    return englishWordTranslationExists != dictionary.words.end();
}

std::optional<DictionaryWord>
DefaultDictionaryService::randomizeDictionaryWord(const std::vector<DictionaryWord>& dictionaryWords) const
{
    const auto randomIndex = randomNumberGenerator->generate(0, static_cast<int>(dictionaryWords.size() - 1));

    return dictionaryWords.at(randomIndex);
}

}
