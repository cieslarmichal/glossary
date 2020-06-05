#include "DefaultDictionaryNamesRetriever.h"

namespace glossary::dictionaryService
{

DefaultDictionaryNamesRetriever::DefaultDictionaryNamesRetriever(
    std::shared_ptr<repository::DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

DictionaryNames DefaultDictionaryNamesRetriever::retrieveDictionaryNames() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return dictionaryNameSelector.selectNames(dictionaries);
}

DictionaryNames DefaultDictionaryNamesRetriever::retrieveDictionaryNamesContainingEnglishWord(
    const std::string& englishWord) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return wordsDictionaryMembershipFinder.findDictionariesContainingEnglishWord(englishWord, dictionaries);
}

DictionaryNames DefaultDictionaryNamesRetriever::retrieveDictionaryNamesContainingEnglishWordTranslation(
    const std::string& englishWordTranslation) const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();
    return wordsDictionaryMembershipFinder.findDictionariesContainingEnglishWordTranslation(
        englishWordTranslation, dictionaries);
}
}