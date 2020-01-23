#include "wordsDb/statisticsDb/StatisticsSerializerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::statisticsDb;

namespace
{
const WordStatistics statisticsPerWord1{EnglishWord{"cat"}, 7, 0};
const WordStatistics statisticsPerWord2{EnglishWord{"dog"}, 2, 1};
const Statistics statisticsWithOneWord{statisticsPerWord1};
const Statistics statistics{statisticsPerWord1, statisticsPerWord2};
const Statistics emptyStatistics{};
const std::string serializedStatistics{
    R"({"statistics":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"englishWord":"dog","incorrectAnswers":1}]})"};
const std::string twoSerializedStatistics{
    R"({"statistics":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"incorrectAnswers":1}]})"};
const std::string serializedStatisticsWithoutRequiredFields{
    R"({"statistics":[{"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"incorrectAnswers":1}]})"};
const std::string emptySerializedStatistics{};
}

class StatisticsSerializerImplTest : public Test
{
public:
    StatisticsSerializerImpl serializer;
};

TEST_F(StatisticsSerializerImplTest, givenNoStatistics_shouldReturnEmptyString)
{
    const auto actualSerializedStatistics =
        serializer.serialize(emptyStatistics);

    EXPECT_TRUE(actualSerializedStatistics.empty());
}

TEST_F(StatisticsSerializerImplTest,
       givenStatistics_shouldReturnSerializedStatistics)
{
    const auto actualSerializedStatistics = serializer.serialize(statistics);

    EXPECT_EQ(actualSerializedStatistics, serializedStatistics);
}

TEST_F(StatisticsSerializerImplTest,
       givenEmptySerializedStatisticsString_shouldReturnNoStatistics)
{
    const auto actualStatistics = serializer.deserialize(serializedStatistics);

    EXPECT_EQ(actualStatistics, statistics);
}

TEST_F(StatisticsSerializerImplTest,
       givenSerializedStatistics_shouldReturnStatistics)
{
    const auto actualStatistics =
        serializer.deserialize(emptySerializedStatistics);

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(
    StatisticsSerializerImplTest,
    givenSerializedStatisticsWithoutRequiredFields_shouldReturnEmptyStatistics)
{
    const auto actualStatistics =
        serializer.deserialize(serializedStatisticsWithoutRequiredFields);

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(
    StatisticsSerializerImplTest,
    givenTwoSerializedStatssAndOneOfThemWithoutRequiredFields_shouldReturnStatsForOneWord)
{
    const auto actualStatistics =
        serializer.deserialize(twoSerializedStatistics);

    EXPECT_EQ(actualStatistics, statisticsWithOneWord);
}
