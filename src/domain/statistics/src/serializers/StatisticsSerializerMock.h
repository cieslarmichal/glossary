#pragma once

#include "gmock/gmock.h"

#include "StatisticsSerializer.h"

namespace glossary::statistics
{
class StatisticsSerializerMock : public StatisticsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const std::vector<WordStatistics>&));
    MOCK_CONST_METHOD1(deserialize, std::vector<WordStatistics>(const std::string&));
};
}
