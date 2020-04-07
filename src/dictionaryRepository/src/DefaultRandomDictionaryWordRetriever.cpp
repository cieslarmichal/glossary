#include "DefaultRandomDictionaryWordRetriever.h"

namespace glossary::dictionaryService
{

DefaultRandomDictionaryWordRetriever::DefaultRandomDictionaryWordRetriever(
    std::shared_ptr<repository::DictionaryRepository> dictionaryRepositoryInit,
    std::unique_ptr<DictionaryWordRandomizer> randomizer)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)},
      dictionaryWordRandomizer{std::move(randomizer)}
{
}

boost::optional<DictionaryWord> DefaultRandomDictionaryWordRetriever::getRandomDictionaryWord() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    const auto wordsFromDictionaries = dictionaryWordAccumulator.accumulateDictionaryWords(dictionaries);
    return randomizeDictionaryWord(wordsFromDictionaries);
}

boost::optional<DictionaryWord>
DefaultRandomDictionaryWordRetriever::getRandomDictionaryWord(const DictionaryName& dictionaryName) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    if (const auto dictionary = dictionaryFinder.findDictionary(dictionaryName, dictionaries))
    {
        const auto wordsFromDictionary = dictionaryWordAccumulator.accumulateDictionaryWords(*dictionary);
        return randomizeDictionaryWord(wordsFromDictionary);
    }
    return boost::none;
}

boost::optional<DictionaryWord>
DefaultRandomDictionaryWordRetriever::randomizeDictionaryWord(const DictionaryWords& dictionaryWords) const
{
    try
    {
        return dictionaryWordRandomizer->randomize(dictionaryWords);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << "\n";
        return boost::none;
    }
}

}