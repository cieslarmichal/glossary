#include "AnswersStatisticsSerializerImpl.h"

#include "gtest/gtest.h"
#include "boost/assign.hpp"

using namespace ::testing;


namespace
{
const AnswersStatisticsPerWord statisticsPerWord1{EnglishWord{"cat"}, 7, 0};
const AnswersStatisticsPerWord statisticsPerWord2{EnglishWord{"dog"}, 2, 1};
const AnswersStatistics answersStatistics = boost::assign::map_list_of
        (statisticsPerWord1.englishWord, statisticsPerWord1)
        (statisticsPerWord2.englishWord, statisticsPerWord2);
const std::string serializedAnswersStatistics{
        R"({"answersStatistics":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"englishWord":"dog","incorrectAnswers":1}]})"};
}

class AnswersStatisticsSerializerImplTest : public Test
{
public:
    AnswersStatisticsSerializerImpl serializer;
};

TEST_F(AnswersStatisticsSerializerImplTest, givenWords_shouldReturnSerializedWords)
{
    const auto actualSerializedStatistics = serializer.serialize(answersStatistics);

    EXPECT_EQ(actualSerializedStatistics, serializedAnswersStatistics);
}

TEST_F(AnswersStatisticsSerializerImplTest, givenSerializedWords_shouldReturnWords)
{
    const auto actualStatistics = serializer.deserialize(serializedAnswersStatistics);

    EXPECT_EQ(actualStatistics, answersStatistics);
}
