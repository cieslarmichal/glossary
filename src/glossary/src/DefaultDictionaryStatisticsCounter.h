#pragma once

#include "DictionaryStatisticsCounter.h"

namespace glossary
{
class DefaultDictionaryStatisticsCounter : public DictionaryStatisticsCounter
{
public:
    DictionaryStatistics countDictionaryStatistics(const dictionaryService::Dictionary&,
                                                   const statistics::Statistics&) const override;
    DictionariesStatistics
    countDictionariesStatistics(const dictionaryService::Dictionaries&,
                                const statistics::Statistics&) const override;

private:
    bool englishWordExistsInDictionary(const dictionaryService::std::string&,
                                       const dictionaryService::Dictionary&) const;
};
}