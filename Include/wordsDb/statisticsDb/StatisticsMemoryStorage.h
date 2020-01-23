#pragma once

#include "StatisticsStorage.h"
#include "boost/optional.hpp"

namespace wordsDb::statisticsDb
{

class StatisticsMemoryStorage : public StatisticsStorage
{
public:
    boost::optional<WordStatistics>
    getWordStatistics(const EnglishWord&) const override;
    Statistics getStatistics() const override;
    void addWordStatistics(WordStatistics) override;
    void addCorrectAnswer(const EnglishWord&) override;
    void addIncorrectAnswer(const EnglishWord&) override;
    void resetStatistics() override;
    bool contains(const EnglishWord&) const override;
    Statistics::size_type size() const override;
    bool empty() const override;
    Statistics::const_iterator begin() const override;
    Statistics::const_iterator end() const override;

private:
    Statistics::const_iterator
    findWordStatisticsPosition(const EnglishWord&) const;

    Statistics statistics;
};
}