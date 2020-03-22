#include "DefaultStatisticsModifierService.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "statisticsRepository/StatisticsRepositoryMock.h"

using namespace ::testing;
using namespace statisticsRepository;

namespace
{
const EnglishWord englishWord{"englishWord"};
}

class DefaultStatisticsModifierServiceTest : public Test
{
public:
    std::shared_ptr<statisticsRepository::StatisticsRepositoryMock> statisticsRepository =
        std::make_shared<StrictMock<statisticsRepository::StatisticsRepositoryMock>>();
    DefaultStatisticsModifierService statisticsModifierService{statisticsRepository};
};

TEST_F(DefaultStatisticsModifierServiceTest, shouldAddCorrectAnswer)
{
    EXPECT_CALL(*statisticsRepository, addCorrectAnswer(englishWord));

    statisticsModifierService.addCorrectAnswer(englishWord);
}

TEST_F(DefaultStatisticsModifierServiceTest, shouldAddIncorrectAnswer)
{
    EXPECT_CALL(*statisticsRepository, addIncorrectAnswer(englishWord));

    statisticsModifierService.addIncorrectAnswer(englishWord);
}