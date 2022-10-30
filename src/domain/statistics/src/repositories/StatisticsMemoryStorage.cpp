#include "StatisticsMemoryStorage.h"

namespace glossary::statistics
{

static auto& getWordStatisticsByPosition(std::vector<WordStatistics>& statistics,
                                         std::vector<WordStatistics>::const_iterator position)
{
    const auto distance = std::vector<WordStatistics>::size_type(std::distance(statistics.cbegin(), position));
    return statistics.at(distance);
}

static auto& getWordStatisticsByPosition(const std::vector<WordStatistics>& statistics,
                                         std::vector<WordStatistics>::const_iterator position)
{
    const auto distance = std::vector<WordStatistics>::size_type(std::distance(statistics.cbegin(), position));
    return statistics.at(distance);
}

std::optional<WordStatistics> StatisticsMemoryStorage::getWordStatistics(const std::string& englishWord) const
{
    auto wordStatisticsPosition = findWordStatisticsPosition(englishWord);
    if (wordStatisticsPosition != statistics.end())
    {
        return getWordStatisticsByPosition(statistics, wordStatisticsPosition);
    }
    return std::nullopt;
}

std::vector<WordStatistics> StatisticsMemoryStorage::getStatistics() const
{
    return statistics;
}

void StatisticsMemoryStorage::addWordStatistics(WordStatistics wordStatistics)
{
    if (not contains(wordStatistics.englishWord))
    {
        statistics.emplace_back(std::move(wordStatistics));
    }
}

void StatisticsMemoryStorage::addCorrectAnswer(const std::string& englishWord)
{
    auto wordIter = findWordStatisticsPosition(englishWord);
    if (wordIter != statistics.end())
    {
        auto& wordStats = getWordStatisticsByPosition(statistics, wordIter);
        wordStats.correctAnswers++;
    }
}

void StatisticsMemoryStorage::addIncorrectAnswer(const std::string& englishWord)
{
    auto wordIter = findWordStatisticsPosition(englishWord);
    if (wordIter != statistics.end())
    {
        auto& wordStats = getWordStatisticsByPosition(statistics, wordIter);
        wordStats.incorrectAnswers++;
    }
}

void StatisticsMemoryStorage::resetStatistics()
{
    for (auto& wordStats : statistics)
    {
        wordStats.correctAnswers = 0;
        wordStats.incorrectAnswers = 0;
    }
}

bool StatisticsMemoryStorage::contains(const std::string& englishWord) const
{
    return findWordStatisticsPosition(englishWord) != statistics.end();
}

std::vector<WordStatistics>::size_type StatisticsMemoryStorage::size() const
{
    return statistics.size();
}

bool StatisticsMemoryStorage::empty() const
{
    return statistics.empty();
}

std::vector<WordStatistics>::const_iterator
StatisticsMemoryStorage::findWordStatisticsPosition(const std::string& wordToFind) const
{
    return std::find_if(statistics.begin(), statistics.end(),
                        [wordToFind](const WordStatistics& stats) { return stats.englishWord == wordToFind; });
}

}
