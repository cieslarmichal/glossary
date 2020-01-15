#pragma once

#include "../../../../externals/googletest/googlemock/include/gmock/gmock.h"

#include "wordsDb/statisticsDb/StatisticsSerializer.h"

class StatisticsSerializerMock : public StatisticsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const AnswersStatistics&));
    MOCK_CONST_METHOD1(deserialize, AnswersStatistics(const std::string&));
};
