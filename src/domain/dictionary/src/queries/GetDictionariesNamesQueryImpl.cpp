#include "GetDictionariesNamesQueryImpl.h"

namespace glossary::dictionary
{
GetDictionariesNamesQueryImpl::GetDictionariesNamesQueryImpl(std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

std::vector<std::string> GetDictionariesNamesQueryImpl::getDictionariesNames() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();

    std::vector<std::string> dictionaryNames;

    for (const auto& dictionary : dictionaries)
    {
        dictionaryNames.emplace_back(dictionary.name);
    }

    return dictionaryNames;
}

}
