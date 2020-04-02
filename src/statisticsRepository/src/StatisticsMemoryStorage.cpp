#include "StatisticsMemoryStorage.h"

namespace glossary::statisticsRepository
{

static auto& getWordStatisticsByPosition(Statistics& statistics, Statistics::const_iterator position)
{
    const auto distance = Statistics::size_type(std::distance(statistics.cbegin(), position));
    return statistics.at(distance);
}

static auto& getWordStatisticsByPosition(const Statistics& statistics, Statistics::const_iterator position)
{
    const auto distance = Statistics::size_type(std::distance(statistics.cbegin(), position));
    return statistics.at(distance);
}

boost::optional<WordStatistics>
StatisticsMemoryStorage::getWordStatistics(const EnglishWord& englishWord) const
{
    auto wordStatisticsPosition = findWordStatisticsPosition(englishWord);
    if (wordStatisticsPosition != statistics.end())
    {
        return getWordStatisticsByPosition(statistics, wordStatisticsPosition);
    }
    return boost::none;
}

Statistics StatisticsMemoryStorage::getStatistics() const
{
    return statistics;
}

void StatisticsMemoryStorage::addWordStatistics(WordStatistics wordStatistics)
{
    if (not contains(wordStatistics.getEnglishWord()))
    {
        statistics.emplace_back(std::move(wordStatistics));
    }
}

void StatisticsMemoryStorage::addCorrectAnswer(const EnglishWord& englishWord)
{
    auto wordIter = findWordStatisticsPosition(englishWord);
    if (wordIter != statistics.end())
    {
        auto& wordStats = getWordStatisticsByPosition(statistics, wordIter);
        wordStats.addCorrectAnswer();
    }
}

void StatisticsMemoryStorage::addIncorrectAnswer(const EnglishWord& englishWord)
{
    auto wordIter = findWordStatisticsPosition(englishWord);
    if (wordIter != statistics.end())
    {
        auto& wordStats = getWordStatisticsByPosition(statistics, wordIter);
        wordStats.addIncorrectAnswer();
    }
}

void StatisticsMemoryStorage::resetStatistics()
{
    for (auto& wordStats : statistics)
    {
        wordStats.resetAnswers();
    }
}

bool StatisticsMemoryStorage::contains(const EnglishWord& englishWord) const
{
    return findWordStatisticsPosition(englishWord) != statistics.end();
}

Statistics::size_type StatisticsMemoryStorage::size() const
{
    return statistics.size();
}

bool StatisticsMemoryStorage::empty() const
{
    return statistics.empty();
}

Statistics::const_iterator
StatisticsMemoryStorage::findWordStatisticsPosition(const EnglishWord& wordToFind) const
{
    return std::find_if(statistics.begin(), statistics.end(), [wordToFind](const WordStatistics& stats) {
        return stats.getEnglishWord() == wordToFind;
    });
}

}
