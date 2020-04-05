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
}