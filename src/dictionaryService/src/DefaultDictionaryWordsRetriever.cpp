#include "DefaultDictionaryWordsRetriever.h"

namespace glossary::dictionaryService
{

DefaultDictionaryWordsRetriever::DefaultDictionaryWordsRetriever(
    std::shared_ptr<repository::DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

boost::optional<DictionaryWords>
DefaultDictionaryWordsRetriever::retrieveDictionaryWords(const DictionaryName& dictionaryName) const
{
    if (const auto dictionary = getDictionary(dictionaryName))
    {
        return dictionaryWordAccumulator.accumulateDictionaryWords(*dictionary);
    }
    return boost::none;
}

boost::optional<EnglishWords>
DefaultDictionaryWordsRetriever::retrieveEnglishWords(const DictionaryName& dictionaryName) const
{
    if (const auto dictionary = getDictionary(dictionaryName))
    {
        return dictionaryWordAccumulator.accumulateEnglishWords(*dictionary);
    }
    return boost::none;
}

EnglishWords DefaultDictionaryWordsRetriever::retrieveEnglishWords() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return dictionaryWordAccumulator.accumulateEnglishWords(dictionaries);
}

boost::optional<Dictionary>
DefaultDictionaryWordsRetriever::getDictionary(const DictionaryName& dictionaryName) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return dictionaryFinder.findDictionary(dictionaryName, dictionaries);
}

}