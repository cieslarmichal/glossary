#include "wordsDb/statisticsDb/StatisticsSerializerImpl.h"

#include "boost/assign.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::statisticsDb;

namespace
{
const AnswersStatisticsPerWord statisticsPerWord1{EnglishWord{"cat"}, 7, 0};
const AnswersStatisticsPerWord statisticsPerWord2{EnglishWord{"dog"}, 2, 1};
const AnswersStatistics answersStatisticsWithOneWord =
    boost::assign::map_list_of(statisticsPerWord1.englishWord,
                               statisticsPerWord1);
const AnswersStatistics answersStatistics = boost::assign::map_list_of(
    statisticsPerWord1.englishWord,
    statisticsPerWord1)(statisticsPerWord2.englishWord, statisticsPerWord2);
const AnswersStatistics emptyAnswersStatistics{};
const std::string serializedAnswersStatistics{
    R"({"answersStatistics":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"englishWord":"dog","incorrectAnswers":1}]})"};
const std::string twoSerializedAnswersStatistics{
    R"({"answersStatistics":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"incorrectAnswers":1}]})"};
const std::string serializedAnswersStatisticsWithoutRequiredFields{
    R"({"answersStatistics":[{"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"incorrectAnswers":1}]})"};
const std::string emptySerializedAnswersStatistics{};
}

class StatisticsSerializerImplTest : public Test
{
public:
    StatisticsSerializerImpl serializer;
};

TEST_F(StatisticsSerializerImplTest,
       givenNoStatistics_shouldReturnEmptyString)
{
    const auto actualSerializedStatistics =
        serializer.serialize(emptyAnswersStatistics);

    EXPECT_TRUE(actualSerializedStatistics.empty());
}

TEST_F(StatisticsSerializerImplTest,
       givenStatistics_shouldReturnSerializedStatistics)
{
    const auto actualSerializedStatistics =
        serializer.serialize(answersStatistics);

    EXPECT_EQ(actualSerializedStatistics, serializedAnswersStatistics);
}

TEST_F(StatisticsSerializerImplTest,
       givenEmptySerializedStatisticsString_shouldReturnNoStatistics)
{
    const auto actualStatistics =
        serializer.deserialize(serializedAnswersStatistics);

    EXPECT_EQ(actualStatistics, answersStatistics);
}

TEST_F(StatisticsSerializerImplTest,
       givenSerializedStatistics_shouldReturnStatistics)
{
    const auto actualStatistics =
        serializer.deserialize(emptySerializedAnswersStatistics);

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(
    StatisticsSerializerImplTest,
    givenSerializedStatisticsWithoutRequiredFields_shouldReturnEmptyStatistics)
{
    const auto actualStatistics = serializer.deserialize(
        serializedAnswersStatisticsWithoutRequiredFields);

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(
    StatisticsSerializerImplTest,
    givenTwoSerializedStatssAndOneOfThemWithoutRequiredFields_shouldReturnStatsForOneWord)
{
    const auto actualStatistics =
        serializer.deserialize(twoSerializedAnswersStatistics);

    EXPECT_EQ(actualStatistics, answersStatisticsWithOneWord);
}
