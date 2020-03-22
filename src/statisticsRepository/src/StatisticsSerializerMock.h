#pragma once

#include "gmock/gmock.h"

#include "StatisticsSerializer.h"

namespace statisticsRepository
{
class StatisticsSerializerMock : public StatisticsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const Statistics&));
    MOCK_CONST_METHOD1(deserialize, Statistics(const std::string&));
};
}
