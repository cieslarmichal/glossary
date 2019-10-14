#pragma once

#include "gmock/gmock.h"

#include "AnswersStatisticsSerializer.h"

class AnswersStatisticsSerializerMock : public AnswersStatisticsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const AnswersStatistics&));
    MOCK_CONST_METHOD1(deserialize, AnswersStatistics(const std::string&));
};
