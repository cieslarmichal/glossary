#include "AddWordStatisticsCommandImpl.h"

#include "gtest/gtest.h"

#include "../repositories/StatisticsRepositoryMock.h"

using namespace ::testing;
using namespace glossary::statistics;

namespace
{
const std::string englishWord{"englishWord"};
const WordStatistics wordStatistics{englishWord, 7, 0};
}

class AddWordStatisticsCommandImplTest : public Test
{
public:
    std::shared_ptr<StatisticsRepositoryMock> statisticsRepository =
        std::make_shared<StrictMock<StatisticsRepositoryMock>>();

    AddWordStatisticsCommandImpl command{statisticsRepository};
};

TEST_F(AddWordStatisticsCommandImplTest, addWordStatistics)
{
    EXPECT_CALL(*statisticsRepository, addWordStatistics(wordStatistics));

    command.addWordStatistics(wordStatistics);
}
