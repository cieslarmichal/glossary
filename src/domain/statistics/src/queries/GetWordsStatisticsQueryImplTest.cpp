#include "GetWordsStatisticsQueryImpl.h"

#include "gtest/gtest.h"

#include "../repositories/StatisticsRepositoryMock.h"

using namespace ::testing;
using namespace glossary::statistics;

namespace
{
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const WordStatistics wordStatistics1{englishWord1, 7, 0};
const WordStatistics wordStatistics2{englishWord2, 8, 0};
const std::vector<WordStatistics> wordsStatistics{wordStatistics1, wordStatistics2};
}

class GetWordsStatisticsQueryImplTest : public Test
{
public:
    std::shared_ptr<StatisticsRepositoryMock> statisticsRepository =
        std::make_shared<StrictMock<StatisticsRepositoryMock>>();

    GetWordsStatisticsQueryImpl command{statisticsRepository};
};

TEST_F(GetWordsStatisticsQueryImplTest, getStatistics)
{
    EXPECT_CALL(*statisticsRepository, getStatistics()).WillOnce(Return(wordsStatistics));

    const auto actualWordsStatistics = command.getWordsStatistics();

    ASSERT_EQ(actualWordsStatistics, wordsStatistics);
}
