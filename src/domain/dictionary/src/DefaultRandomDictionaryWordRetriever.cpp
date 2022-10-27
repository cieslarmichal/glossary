#include "DefaultRandomDictionaryWordRetriever.h"

namespace glossary::dictionary
{
DefaultRandomDictionaryWordRetriever::DefaultRandomDictionaryWordRetriever(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit,
    std::unique_ptr<DictionaryWordRandomizer> randomizer)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}, dictionaryWordRandomizer{std::move(randomizer)}
{
}

std::optional<DictionaryWord> DefaultRandomDictionaryWordRetriever::getRandomDictionaryWord() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    const auto wordsFromDictionaries = dictionaryWordAccumulator.accumulateDictionaryWords(dictionaries);
    return randomizeDictionaryWord(wordsFromDictionaries);
}

std::optional<DictionaryWord>
DefaultRandomDictionaryWordRetriever::getRandomDictionaryWord(const std::string& dictionaryName) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    if (const auto dictionary = dictionaryFinder.findDictionary(dictionaryName, dictionaries))
    {
        const auto wordsFromDictionary = dictionaryWordAccumulator.accumulateDictionaryWords(*dictionary);
        return randomizeDictionaryWord(wordsFromDictionary);
    }
    return std::nullopt;
}

std::optional<DictionaryWord>
DefaultRandomDictionaryWordRetriever::randomizeDictionaryWord(const std::vector<DictionaryWord>& dictionaryWords) const
{
    try
    {
        return dictionaryWordRandomizer->randomize(dictionaryWords);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << "\n";
        return std::nullopt;
    }
}

}
