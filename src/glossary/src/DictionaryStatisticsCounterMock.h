#pragma once

#include "gmock/gmock.h"

#include "DictionaryStatisticsCounter.h"

namespace glossary
{
class DictionaryStatisticsCounterMock : public DictionaryStatisticsCounter
{
public:
    MOCK_CONST_METHOD2(countDictionaryStatistics,
                       DictionaryStatistics(const dictionary::Dictionary&,
                                            const statistics::Statistics&));
    MOCK_CONST_METHOD2(countDictionariesStatistics,
                       DictionariesStatistics(const dictionary::Dictionaries&,
                                              const statistics::Statistics&));
};
}