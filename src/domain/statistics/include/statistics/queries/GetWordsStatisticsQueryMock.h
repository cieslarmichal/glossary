#pragma once

#include "gmock/gmock.h"

#include "GetWordsStatisticsQuery.h"

namespace glossary::statistics
{
class GetWordsStatisticsQueryMock : public GetWordsStatisticsQuery
{
public:
    MOCK_METHOD(std::vector<WordStatistics>, getWordsStatistics, (), ());
};
}
