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

    virtual void addCorrectAnswer(const EnglishWord&) = 0;
    virtual void addIncorrectAnswer(const EnglishWord&) = 0;
    virtual boost::optional<AnswersStatisticsPerWord>
    getAnswersStatisticsPerWord(const EnglishWord&) const = 0;
    virtual AnswersStatistics getAnswersStatistics() const = 0;
};
}
