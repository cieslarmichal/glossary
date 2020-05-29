#pragma once

#include "dictionaryService/Dictionary.h"
#include "statisticsRepository/Statistics.h"
#include "DictionaryStatistics.h"

namespace glossary
{
class DictionaryStatisticsCounter
{
public:
    virtual ~DictionaryStatisticsCounter() = default;

    virtual DictionaryStatistics countDictionaryStatistics(const dictionaryService::Dictionary&,
                                      const statisticsRepository::Statistics&) const = 0;
    virtual DictionariesStatistics countDictionariesStatistics(const dictionaryService::Dictionaries&,
                                                           const statisticsRepository::Statistics&) const = 0;
};
}