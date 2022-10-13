#pragma once

#include "gmock/gmock.h"

#include "DictionaryStatisticsCounter.h"

namespace glossary
{
class DictionaryStatisticsCounterMock : public DictionaryStatisticsCounter
{
public:
    MOCK_CONST_METHOD2(countDictionaryStatistics,
                       DictionaryStatistics(const dictionaryService::Dictionary&,
                                            const statistics::Statistics&));
    MOCK_CONST_METHOD2(countDictionariesStatistics,
                       DictionariesStatistics(const dictionaryService::Dictionaries&,
                                              const statistics::Statistics&));
};
}