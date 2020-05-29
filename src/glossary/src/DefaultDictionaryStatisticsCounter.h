#pragma once

#include "DictionaryStatisticsCounter.h"

namespace glossary
{
class DefaultDictionaryStatisticsCounter : public DictionaryStatisticsCounter
{
public:
    DictionaryStatistics countDictionaryStatistics(const dictionaryService::Dictionary&,
                                                   const statisticsRepository::Statistics&) const override;
    DictionariesStatistics
    countDictionariesStatistics(const dictionaryService::Dictionaries&,
                                const statisticsRepository::Statistics&) const override;

private:
    bool englishWordExistsInDictionary(const dictionaryService::EnglishWord&,
                                       const dictionaryService::Dictionary&) const;
};
}