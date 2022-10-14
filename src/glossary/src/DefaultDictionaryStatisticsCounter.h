#pragma once

#include "DictionaryStatisticsCounter.h"

namespace glossary
{
class DefaultDictionaryStatisticsCounter : public DictionaryStatisticsCounter
{
public:
    DictionaryStatistics countDictionaryStatistics(const dictionary::Dictionary&,
                                                   const statistics::Statistics&) const override;
    DictionariesStatistics
    countDictionariesStatistics(const dictionary::Dictionaries&,
                                const statistics::Statistics&) const override;

private:
    bool englishWordExistsInDictionary(const dictionary::std::string&,
                                       const dictionary::Dictionary&) const;
};
}