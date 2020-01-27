#pragma once

#include "gmock/gmock.h"

#include "wordsDb/statisticsDb/StatisticsStorage.h"

namespace wordsDb::statisticsDb
{

class StatisticsStorageMock : public StatisticsStorage
{
public:
    MOCK_CONST_METHOD1(getWordStatistics,
                       boost::optional<WordStatistics>(const EnglishWord&));
    MOCK_CONST_METHOD0(getStatistics, Statistics());
    MOCK_METHOD1(addWordStatistics, void(WordStatistics));
    MOCK_METHOD1(addCorrectAnswer, void(const EnglishWord&));
    MOCK_METHOD1(addIncorrectAnswer, void(const EnglishWord&));
    MOCK_METHOD0(resetStatistics, void());
    MOCK_CONST_METHOD1(contains, bool(const EnglishWord&));
    MOCK_CONST_METHOD0(size, Statistics::size_type());
    MOCK_CONST_METHOD0(empty, bool());
    MOCK_CONST_METHOD0(begin, Statistics::const_iterator());
    MOCK_CONST_METHOD0(end, Statistics::const_iterator());
};
}
