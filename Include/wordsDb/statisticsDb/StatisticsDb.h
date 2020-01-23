#pragma once

#include "EnglishWord.h"
#include "Statistics.h"
#include "boost/optional.hpp"

namespace wordsDb::statisticsDb
{
class StatisticsDb
{
public:
    virtual ~StatisticsDb() = default;

    virtual boost::optional<WordStatistics>
    getWordStatistics(const EnglishWord&) const = 0;
    virtual Statistics getStatistics() const = 0;
    virtual void addWordStatistics(WordStatistics) = 0;
    virtual void addCorrectAnswer(const EnglishWord&) = 0;
    virtual void addIncorrectAnswer(const EnglishWord&) = 0;
    virtual void resetStatistics() = 0;
};
}
