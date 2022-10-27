#include "DefaultDictionaryNamesRetriever.h"

namespace glossary::dictionary
{

DefaultDictionaryNamesRetriever::DefaultDictionaryNamesRetriever(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

std::vector<std::string> DefaultDictionaryNamesRetriever::retrieveDictionaryNames() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return dictionaryNameSelector.selectNames(dictionaries);
}

std::vector<std::string>
DefaultDictionaryNamesRetriever::retrieveDictionaryNamesContainingEnglishWord(const std::string& englishWord) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return wordsDictionaryMembershipFinder.findDictionariesContainingEnglishWord(englishWord, dictionaries);
}

std::vector<std::string> DefaultDictionaryNamesRetriever::retrieveDictionaryNamesContainingEnglishWordTranslation(
    const std::string& englishWordTranslation) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return wordsDictionaryMembershipFinder.findDictionariesContainingEnglishWordTranslation(englishWordTranslation,
                                                                                            dictionaries);
}
}
