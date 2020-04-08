#include "DictionaryWordAccumulator.h"

namespace glossary::dictionaryService
{

DictionaryWords DictionaryWordAccumulator::accumulateDictionaryWords(const Dictionary& dictionary) const
{
    return dictionary.words;
}

DictionaryWords DictionaryWordAccumulator::accumulateDictionaryWords(const Dictionaries& dictionaries) const
{
    DictionaryWords selectedWords{};

    for (const auto& dictionary : dictionaries)
    {
        const auto& dictionaryWords = dictionary.words;
        selectedWords.insert(selectedWords.end(), dictionaryWords.begin(), dictionaryWords.end());
    }
    return selectedWords;
}

EnglishWords DictionaryWordAccumulator::accumulateEnglishWords(const Dictionary& dictionary) const
{
    EnglishWords englishWordsFromDictionary;

    for (const auto& dictionaryWord : dictionary.words)
        englishWordsFromDictionary.emplace_back(dictionaryWord.englishWord);

    return englishWordsFromDictionary;
}

EnglishWords DictionaryWordAccumulator::accumulateEnglishWords(const Dictionaries& dictionaries) const
{
    EnglishWords englishWordsFromDictionaries;

    for (const auto& dictionary : dictionaries)
    {
        const auto englishWords = accumulateEnglishWords(dictionary);
        englishWordsFromDictionaries.insert(englishWordsFromDictionaries.end(), englishWords.begin(),
                                            englishWords.end());
    }

    return englishWordsFromDictionaries;
}

}