#pragma once

#include "gmock/gmock.h"

#include "StatisticsRepository.h"

namespace statisticsRepository
{

class StatisticsRepositoryMock : public StatisticsRepository
{
public:
    MOCK_CONST_METHOD1(getWordStatistics, boost::optional<WordStatistics>(const EnglishWord&));
    MOCK_CONST_METHOD0(getStatistics, Statistics());
    MOCK_METHOD1(addWordStatistics, void(WordStatistics));
    MOCK_METHOD1(addCorrectAnswer, void(const EnglishWord&));
    MOCK_METHOD1(addIncorrectAnswer, void(const EnglishWord&));
    MOCK_METHOD0(resetStatistics, void());
};
}
