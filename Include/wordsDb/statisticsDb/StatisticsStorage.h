#pragma once

#include "Statistics.h"
#include "boost/optional.hpp"

namespace wordsDb::statisticsDb
{

//TODO: add return type const ref

class StatisticsStorage
{
public:
    virtual ~StatisticsStorage() = default;

    virtual boost::optional<WordStatistics>
    getWordStatistics(const EnglishWord&) const = 0;
    virtual Statistics getStatistics() const = 0;
    virtual void addWordStatistics(WordStatistics) = 0;
    virtual void addCorrectAnswer(const EnglishWord&) = 0;
    virtual void addIncorrectAnswer(const EnglishWord&) = 0;
    virtual void resetStatistics() = 0;
    virtual bool contains(const EnglishWord&) const = 0;
    virtual Statistics::size_type size() const = 0;
    virtual bool empty() const = 0;
    virtual Statistics::const_iterator begin() const = 0;
    virtual Statistics::const_iterator end() const = 0;
};
}
