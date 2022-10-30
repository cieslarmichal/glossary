#include "AddCorrectAnswerCommandImpl.h"

#include "gtest/gtest.h"

#include "../repositories/StatisticsRepositoryMock.h"

using namespace ::testing;
using namespace glossary::statistics;

namespace
{
const std::string englishWord{"englishWord"};
}

class AddCorrectAnswerCommandImplTest : public Test
{
public:
    std::shared_ptr<StatisticsRepositoryMock> statisticsRepository =
        std::make_shared<StrictMock<StatisticsRepositoryMock>>();

    AddCorrectAnswerCommandImpl command{statisticsRepository};
};

TEST_F(AddCorrectAnswerCommandImplTest, addCorrectAnswer)
{
    EXPECT_CALL(*statisticsRepository, addCorrectAnswer(englishWord));

    command.addCorrectAnswer(englishWord);
}
