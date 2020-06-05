#include "DictionaryNameSelector.h"

namespace glossary::dictionaryService
{

DictionaryNames DictionaryNameSelector::selectNames(const Dictionaries& dictionaries) const
{
    DictionaryNames dictionaryNames;
    for (const auto& dictionary : dictionaries)
    {
        dictionaryNames.emplace_back(dictionary.name);
    }
    return dictionaryNames;
}

}