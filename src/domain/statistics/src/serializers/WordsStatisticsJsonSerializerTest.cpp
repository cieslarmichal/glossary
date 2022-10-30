#include "WordsStatisticsJsonSerializer.h"

#include "gtest/gtest.h"

#include "exceptions/InvalidJsonError.h"
#include "exceptions/WordsStatisticsJsonMissingRequiredFieldsError.h"

using namespace ::testing;
using namespace glossary::statistics;

namespace
{
const WordStatistics wordStatistics1{"cat", 7, 0};
const WordStatistics wordStatistics2{"dog", 2, 1};
const std::vector<WordStatistics> wordsStatistics{wordStatistics1, wordStatistics2};
const std::vector<WordStatistics> emptyStatistics{};
const std::string invalidJson{"{."};
const std::string serializedWordsStatistics{
    R"([{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"englishWord":"dog","incorrectAnswers":1}])"};
const std::string serializedWordsStatisticsWithoutEnglishWordField{
    R"([{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"incorrectAnswers":1}])"};
const std::string serializedWordsStatisticsWithoutCorrectAnswerField{
    R"([{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"missing":2,"englishWord":"dog","incorrectAnswers":1}])"};
const std::string serializedWordsStatisticsWithoutIncorrectAnswerField{
    R"([{"correctAnswers":7,"englishWord":"cat","missing":0},{"correctAnswers":2,"englishWord":"dog","incorrectAnswers":1}])"};
const std::string emptySerializedStatistics{"[]"};
}

class WordsStatisticsJsonSerializerTest : public Test
{
public:
    WordsStatisticsJsonSerializer serializer;
};

TEST_F(WordsStatisticsJsonSerializerTest, givenNoStatistics_shouldReturnEmptyJson)
{
    const auto actualSerializedWordsStatistics = serializer.serialize(emptyStatistics);

    EXPECT_EQ(actualSerializedWordsStatistics, "[]");
}

TEST_F(WordsStatisticsJsonSerializerTest, givenStatistics_shouldReturnSerializedStatistics)
{
    const auto actualSerializedWordsStatistics = serializer.serialize(wordsStatistics);

    EXPECT_EQ(actualSerializedWordsStatistics, serializedWordsStatistics);
}

TEST_F(WordsStatisticsJsonSerializerTest, givenInvalidJson_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(invalidJson), exceptions::InvalidJsonError);
}

TEST_F(WordsStatisticsJsonSerializerTest, givenSerializedStatisticsJson_shouldReturnStatistics)
{
    const auto actualWordsStatistics = serializer.deserialize(serializedWordsStatistics);

    EXPECT_EQ(actualWordsStatistics, wordsStatistics);
}

TEST_F(WordsStatisticsJsonSerializerTest, givenEmptySerializedStatisticsString_shouldReturnNoStatistics)
{
    const auto actualStatistics = serializer.deserialize(emptySerializedStatistics);

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(WordsStatisticsJsonSerializerTest, givenSerializedStatisticsWithoutEnglishWordField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(serializedWordsStatisticsWithoutEnglishWordField),
                 exceptions::WordsStatisticsJsonMissingRequiredFieldsError);
}

TEST_F(WordsStatisticsJsonSerializerTest, givenSerializedStatisticsWithoutCorrectAnswerField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(serializedWordsStatisticsWithoutCorrectAnswerField),
                 exceptions::WordsStatisticsJsonMissingRequiredFieldsError);
}

TEST_F(WordsStatisticsJsonSerializerTest, givenSerializedStatisticsWithoutIncorrectAnswerField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(serializedWordsStatisticsWithoutIncorrectAnswerField),
                 exceptions::WordsStatisticsJsonMissingRequiredFieldsError);
}
