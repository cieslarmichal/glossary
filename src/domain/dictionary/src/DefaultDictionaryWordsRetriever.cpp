#include "DefaultDictionaryWordsRetriever.h"

namespace glossary::dictionary
{

DefaultDictionaryWordsRetriever::DefaultDictionaryWordsRetriever(
    std::shared_ptr<repository::DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

std::optional<std::vector<DictionaryWord>>
DefaultDictionaryWordsRetriever::retrieveDictionaryWords(const std::string& dictionaryName) const
{
    if (const auto dictionary = getDictionary(dictionaryName))
    {
        return dictionaryWordAccumulator.accumulateDictionaryWords(*dictionary);
    }
    return std::nullopt;
}

std::optional<std::vector<std::string>>
DefaultDictionaryWordsRetriever::retrieveEnglishWords(const std::string& dictionaryName) const
{
    if (const auto dictionary = getDictionary(dictionaryName))
    {
        return dictionaryWordAccumulator.accumulateEnglishWords(*dictionary);
    }
    return std::nullopt;
}

std::vector<std::string> DefaultDictionaryWordsRetriever::retrieveEnglishWords() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return dictionaryWordAccumulator.accumulateEnglishWords(dictionaries);
}

std::optional<Dictionary>
DefaultDictionaryWordsRetriever::getDictionary(const std::string& dictionaryName) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return dictionaryFinder.findDictionary(dictionaryName, dictionaries);
}

}