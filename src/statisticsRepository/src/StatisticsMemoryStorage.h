#pragma once

#include "boost/optional.hpp"

#include "StatisticsStorage.h"

namespace statisticsRepository
{
class StatisticsMemoryStorage : public StatisticsStorage
{
public:
    boost::optional<WordStatistics> getWordStatistics(const EnglishWord&) const override;
    Statistics getStatistics() const override;
    void addWordStatistics(WordStatistics) override;
    void addCorrectAnswer(const EnglishWord&) override;
    void addIncorrectAnswer(const EnglishWord&) override;
    void resetStatistics() override;
    bool contains(const EnglishWord&) const override;
    Statistics::size_type size() const override;
    bool empty() const override;

private:
    Statistics::const_iterator findWordStatisticsPosition(const EnglishWord&) const;

    Statistics statistics;
};
}