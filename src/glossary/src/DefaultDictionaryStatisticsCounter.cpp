#include "DefaultDictionaryStatisticsCounter.h"

#include <algorithm>

namespace glossary
{

DictionaryStatistics DefaultDictionaryStatisticsCounter::countDictionaryStatistics(
    const dictionaryService::Dictionary& dictionary, const statisticsRepository::Statistics& statistics) const
{
    DictionaryStatistics dictionaryStatistics{dictionary.name, 0, 0};

    for (const auto& wordStatistics : statistics)
    {
        auto englishWord = wordStatistics.getEnglishWord();
        if (englishWordExistsInDictionary(englishWord, dictionary))
        {
            dictionaryStatistics.correctAnswers += wordStatistics.getAmountOfCorrectAnswers();
            dictionaryStatistics.incorrectAnswers += wordStatistics.getAmountOfIncorrectAnswers();
        }
    }
    return dictionaryStatistics;
}

DictionariesStatistics DefaultDictionaryStatisticsCounter::countDictionariesStatistics(
    const dictionaryService::Dictionaries& dictionaries,
    const statisticsRepository::Statistics& statistics) const
{
    DictionariesStatistics dictionariesStatistics;
    for (const auto& dictionary : dictionaries)
    {
        auto dictionaryStatistics = countDictionaryStatistics(dictionary, statistics);
        dictionariesStatistics.emplace_back(dictionaryStatistics);
    }
    return dictionariesStatistics;
}

bool DefaultDictionaryStatisticsCounter::englishWordExistsInDictionary(
    const dictionaryService::EnglishWord& englishWord, const dictionaryService::Dictionary& dictionary) const
{
    const auto& dictionaryWords = dictionary.words;
    auto foundEnglishWord = std::find_if(
        dictionaryWords.begin(), dictionaryWords.end(),
        [&englishWord](const auto& dictionaryWord) { return dictionaryWord.englishWord == englishWord; });
    return foundEnglishWord != dictionaryWords.end();
}
}