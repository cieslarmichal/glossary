#include "DictionaryFinder.h"

namespace glossary::dictionaryService
{

boost::optional<Dictionary> DictionaryFinder::findDictionary(const DictionaryName& dictionaryName,
                                                             const Dictionaries& dictionaries) const
{
    auto foundDictionary =
        std::find_if(dictionaries.begin(), dictionaries.end(),
                     [&dictionaryName](const auto& dictionary) { return dictionary.name == dictionaryName; });
    if (dictionaryExists(dictionaries, foundDictionary))
        return *foundDictionary;
    return boost::none;
}

bool DictionaryFinder::dictionaryExists(const Dictionaries& dictionaries,
                                        const Dictionaries::const_iterator& foundDictionary) const
{
    return foundDictionary != dictionaries.end();
}
}