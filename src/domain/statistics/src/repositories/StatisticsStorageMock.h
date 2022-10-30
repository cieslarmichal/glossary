#pragma once

#include "gmock/gmock.h"

#include "StatisticsStorage.h"

namespace glossary::statistics
{
class StatisticsStorageMock : public StatisticsStorage
{
public:
    MOCK_CONST_METHOD1(getWordStatistics, std::optional<WordStatistics>(const std::string&));
    MOCK_CONST_METHOD0(getStatistics, std::vector<WordStatistics>());
    MOCK_METHOD1(addWordStatistics, void(WordStatistics));
    MOCK_METHOD1(addCorrectAnswer, void(const std::string&));
    MOCK_METHOD1(addIncorrectAnswer, void(const std::string&));
    MOCK_METHOD0(resetStatistics, void());
    MOCK_CONST_METHOD1(contains, bool(const std::string&));
    MOCK_CONST_METHOD0(size, std::vector<WordStatistics>::size_type());
    MOCK_CONST_METHOD0(empty, bool());
};
}
