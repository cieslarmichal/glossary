#include "DictionaryFinder.h"

namespace glossary::dictionary
{
std::optional<Dictionary> DictionaryFinder::findDictionary(const std::string& dictionaryName,
                                                           const std::vector<Dictionary>& dictionaries) const
{
    auto foundDictionary =
        std::find_if(dictionaries.begin(), dictionaries.end(),
                     [&dictionaryName](const auto& dictionary) { return dictionary.name == dictionaryName; });
    if (dictionaryExists(dictionaries, foundDictionary))
        return *foundDictionary;
    return std::nullopt;
}

bool DictionaryFinder::dictionaryExists(const std::vector<Dictionary>& dictionaries,
                                        const std::vector<Dictionary>::const_iterator& foundDictionary) const
{
    return foundDictionary != dictionaries.end();
}
}