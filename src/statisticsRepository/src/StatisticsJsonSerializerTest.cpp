#include "StatisticsJsonSerializer.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace statisticsRepository;

namespace
{
// TODO: change test string jsons into json and dumpy() them
// TODO: change XsSerializer to XSerializer
const WordStatistics statisticsPerWord1{EnglishWord{"cat"}, 7, 0};
const WordStatistics statisticsPerWord2{EnglishWord{"dog"}, 2, 1};
const Statistics statisticsWithOneWord{statisticsPerWord1};
const Statistics statistics{statisticsPerWord1, statisticsPerWord2};
const Statistics emptyStatistics{};
const std::string invalidJson{"{."};
const std::string serializedTranslations{
    R"({"statistics":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"englishWord":"dog","incorrectAnswers":1}]})"};
const std::string twoSerializedTranslationsOneWithouRequiredField{
    R"({"statistics":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"incorrectAnswers":1}]})"};
const std::string serializedTranslationsWithoutRequiredFields{
    R"({"statistics":[{"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"incorrectAnswers":1}]})"};
const std::string serializedTranslationsWithoutStatisticsField{
    R"({"xxx":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"englishWord":"dog","incorrectAnswers":1}]})"};
const std::string emptySerializedStatistics{};
}

class StatisticsJsonSerializerTest : public Test
{
public:
    StatisticsJsonSerializer serializer;
};

TEST_F(StatisticsJsonSerializerTest, givenNoStatistics_shouldReturnEmptyString)
{
    const auto actualSerializedStatistics = serializer.serialize(emptyStatistics);

    EXPECT_TRUE(actualSerializedStatistics.empty());
}

TEST_F(StatisticsJsonSerializerTest, givenStatistics_shouldReturnSerializedStatistics)
{
    const auto actualSerializedStatistics = serializer.serialize(statistics);

    EXPECT_EQ(actualSerializedStatistics, serializedTranslations);
}

TEST_F(StatisticsJsonSerializerTest, givenInvalidJson_shouldReturnNoStatistics)
{
    const auto actualStatistics = serializer.deserialize(invalidJson);

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(StatisticsJsonSerializerTest, givenJsonWithoutStatisticsField_shouldReturnNoStatistics)
{
    const auto actualStatistics = serializer.deserialize(serializedTranslationsWithoutStatisticsField);

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(StatisticsJsonSerializerTest, givenSerializedStatisticsString_shouldReturnStatistics)
{
    const auto actualStatistics = serializer.deserialize(serializedTranslations);

    EXPECT_EQ(actualStatistics, statistics);
}

TEST_F(StatisticsJsonSerializerTest, givenEmptySerializedStatisticsString_shouldReturnNoStatistics)
{
    const auto actualStatistics = serializer.deserialize(emptySerializedStatistics);

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(StatisticsJsonSerializerTest,
       givenSerializedStatisticsWithoutRequiredFields_shouldReturnEmptyStatistics)
{
    const auto actualStatistics = serializer.deserialize(serializedTranslationsWithoutRequiredFields);

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(StatisticsJsonSerializerTest,
       givenTwoSerializedStatsAndOneOfThemWithoutRequiredFields_shouldReturnStatsForOneWord)
{
    const auto actualStatistics = serializer.deserialize(twoSerializedTranslationsOneWithouRequiredField);

    EXPECT_EQ(actualStatistics, statisticsWithOneWord);
}
