#include "DictionaryNameSelector.h"

namespace glossary::dictionary
{

std::vector<std::string>
DictionaryNameSelector::selectNames(const std::vector<Dictionary>& dictionaries) const
{
    std::vector<std::string> dictionaryNames;
    for (const auto& dictionary : dictionaries)
    {
        dictionaryNames.emplace_back(dictionary.name);
    }
    return dictionaryNames;
}

}