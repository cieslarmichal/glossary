#include "DictionaryWordSelector.h"

namespace glossary::dictionaryService
{

DictionaryWords DictionaryWordSelector::selectWords(const Dictionary& dictionary) const
{
    return dictionary.words;
}

DictionaryWords DictionaryWordSelector::selectWords(const Dictionaries& dictionaries) const
{
    DictionaryWords selectedWords{};

    for (auto& dictionary : dictionaries)
    {
        auto& dictionaryWords = dictionary.words;
        selectedWords.insert(selectedWords.end(), dictionaryWords.begin(), dictionaryWords.end());
    }
    return selectedWords;
}

}