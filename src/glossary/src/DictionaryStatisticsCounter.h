#pragma once

#include "dictionary/Dictionary.h"
#include "DictionaryStatistics.h"
#include "statistics/WordStatistics.h"

namespace glossary
{
class DictionaryStatisticsCounter
{
public:
    virtual ~DictionaryStatisticsCounter() = default;

    virtual DictionaryStatistics countDictionaryStatistics(const dictionary::Dictionary&,
                                                           const std::vector<statistics::WordStatistics>&) const = 0;
    virtual DictionariesStatistics
    countDictionariesStatistics(const std::vector<dictionary::Dictionary>&,
                                const std::vector<statistics::WordStatistics>&) const = 0;
};
}
