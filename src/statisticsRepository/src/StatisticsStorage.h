#pragma once

#include "boost/optional.hpp"

#include "statisticsRepository/Statistics.h"

namespace statisticsRepository
{
class StatisticsStorage
{
public:
    virtual ~StatisticsStorage() = default;

    virtual boost::optional<WordStatistics> getWordStatistics(const EnglishWord&) const = 0;
    virtual Statistics getStatistics() const = 0;
    virtual void addWordStatistics(WordStatistics) = 0;
    virtual void addCorrectAnswer(const EnglishWord&) = 0;
    virtual void addIncorrectAnswer(const EnglishWord&) = 0;
    virtual void resetStatistics() = 0;
    virtual bool contains(const EnglishWord&) const = 0;
    virtual Statistics::size_type size() const = 0;
    virtual bool empty() const = 0;
};
}
