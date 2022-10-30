#include "AddIncorrectAnswerCommandImpl.h"

#include "gtest/gtest.h"

#include "../repositories/StatisticsRepositoryMock.h"

using namespace ::testing;
using namespace glossary::statistics;

namespace
{
const std::string englishWord{"englishWord"};
}

class AddIncorrectAnswerCommandImplTest : public Test
{
public:
    std::shared_ptr<StatisticsRepositoryMock> statisticsRepository =
        std::make_shared<StrictMock<StatisticsRepositoryMock>>();

    AddIncorrectAnswerCommandImpl command{statisticsRepository};
};

TEST_F(AddIncorrectAnswerCommandImplTest, addIncorrectAnswer)
{
    EXPECT_CALL(*statisticsRepository, addIncorrectAnswer(englishWord));

    command.addIncorrectAnswer(englishWord);
}
