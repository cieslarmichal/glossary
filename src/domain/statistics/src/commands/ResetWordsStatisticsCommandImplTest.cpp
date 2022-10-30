#include "ResetWordsStatisticsCommandImpl.h"

#include "gtest/gtest.h"

#include "../repositories/StatisticsRepositoryMock.h"

using namespace ::testing;
using namespace glossary::statistics;

class ResetWordsStatisticsCommandImplTest : public Test
{
public:
    std::shared_ptr<StatisticsRepositoryMock> statisticsRepository =
        std::make_shared<StrictMock<StatisticsRepositoryMock>>();

    ResetWordsStatisticsCommandImpl command{statisticsRepository};
};

TEST_F(ResetWordsStatisticsCommandImplTest, addCorrectAnswer)
{
    EXPECT_CALL(*statisticsRepository, resetStatistics());

    command.resetWordsStatistics();
}
