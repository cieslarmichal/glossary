#pragma once

#include "DictionaryStatisticsCounter.h"

namespace glossary
{
class DefaultDictionaryStatisticsCounter : public DictionaryStatisticsCounter
{
public:
    DictionaryStatistics countDictionaryStatistics(const dictionary::Dictionary&,
                                                   const std::vector<statistics::WordStatistics>&) const override;
    DictionariesStatistics countDictionariesStatistics(const std::vector<dictionary::Dictionary>&,
                                                       const std::vector<statistics::WordStatistics>&) const override;

private:
    bool englishWordExistsInDictionary(const std::string&, const dictionary::Dictionary&) const;
};
}
