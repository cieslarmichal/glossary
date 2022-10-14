#include "DictionaryWordAccumulator.h"

namespace glossary::dictionary
{

std::vector<DictionaryWord>
DictionaryWordAccumulator::accumulateDictionaryWords(const Dictionary& dictionary) const
{
    return dictionary.words;
}

std::vector<DictionaryWord>
DictionaryWordAccumulator::accumulateDictionaryWords(const std::vector<Dictionary>& dictionaries) const
{
    std::vector<DictionaryWord> selectedWords{};

    for (const auto& dictionary : dictionaries)
    {
        const auto& dictionaryWords = dictionary.words;
        selectedWords.insert(selectedWords.end(), dictionaryWords.begin(), dictionaryWords.end());
    }
    return selectedWords;
}

std::vector<std::string> DictionaryWordAccumulator::accumulateEnglishWords(const Dictionary& dictionary) const
{
    std::vector<std::string> englishWordsFromDictionary;

    for (const auto& dictionaryWord : dictionary.words)
        englishWordsFromDictionary.emplace_back(dictionaryWord.englishWord);

    return englishWordsFromDictionary;
}

std::vector<std::string>
DictionaryWordAccumulator::accumulateEnglishWords(const std::vector<Dictionary>& dictionaries) const
{
    std::vector<std::string> englishWordsFromDictionaries;

    for (const auto& dictionary : dictionaries)
    {
        const auto englishWords = accumulateEnglishWords(dictionary);
        englishWordsFromDictionaries.insert(englishWordsFromDictionaries.end(), englishWords.begin(),
                                            englishWords.end());
    }

    return englishWordsFromDictionaries;
}

}