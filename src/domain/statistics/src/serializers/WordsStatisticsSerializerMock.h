#pragma once

#include "gmock/gmock.h"

#include "WordsStatisticsSerializer.h"

namespace glossary::statistics
{
class WordsStatisticsSerializerMock : public WordsStatisticsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const std::vector<WordStatistics>&));
    MOCK_CONST_METHOD1(deserialize, std::vector<WordStatistics>(const std::string&));
};
}
