#pragma once

#include "AnswersStatistics.h"
#include "EnglishWord.h"
#include "boost/optional.hpp"

class AnswersCounter
{
public:
    virtual ~AnswersCounter() = default;

    virtual void addCorrectAnswer(const EnglishWord&) = 0;
    virtual void addIncorrectAnswer(const EnglishWord&) = 0;
    virtual boost::optional<AnswersStatisticsPerWord>
    getAnswersStatisticsPerWord(const EnglishWord&) const = 0;
    virtual AnswersStatistics getAnswersStatistics() const = 0;
};