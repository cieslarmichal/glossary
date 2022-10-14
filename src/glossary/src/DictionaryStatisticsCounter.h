#pragma once

#include "DictionaryStatistics.h"
#include "dictionaryService/Dictionary.h"
#include "statisticsRepository/Statistics.h"

namespace glossary
{
class DictionaryStatisticsCounter
{
public:
    virtual ~DictionaryStatisticsCounter() = default;

    virtual DictionaryStatistics countDictionaryStatistics(const dictionary::Dictionary&,
                                                           const statistics::Statistics&) const = 0;
    virtual DictionariesStatistics
    countDictionariesStatistics(const dictionary::Dictionaries&,
                                const statistics::Statistics&) const = 0;
};
}