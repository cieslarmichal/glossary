#pragma once

#include "gmock/gmock.h"

#include "StatisticsRepository.h"

namespace glossary::statistics
{
class StatisticsRepositoryMock : public StatisticsRepository
{
public:
    MOCK_CONST_METHOD1(getWordStatistics, std::optional<WordStatistics>(const std::string&));
    MOCK_CONST_METHOD0(getStatistics, std::vector<WordStatistics>());
    MOCK_METHOD1(addWordStatistics, void(WordStatistics));
    MOCK_METHOD1(addCorrectAnswer, void(const std::string&));
    MOCK_METHOD1(addIncorrectAnswer, void(const std::string&));
    MOCK_METHOD0(resetStatistics, void());
};
}
