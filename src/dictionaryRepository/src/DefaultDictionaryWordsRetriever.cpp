#include "DefaultDictionaryWordsRetriever.h"

namespace glossary::dictionaryService
{

DefaultDictionaryWordsRetriever::DefaultDictionaryWordsRetriever(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

DictionaryWords
DefaultDictionaryWordsRetriever::retrieveDictionaryWords(const DictionaryName& dictionaryName) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    if (const auto dictionary = dictionaryFinder.findDictionary(dictionaryName, dictionaries))
        return dictionaryWordSelector.selectWords(*dictionary);
    return {};
}

}