#include "WordStatistics.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::statistics;

class WordStatisticsTest : public Test
{
public:
    const std::string englishWord{"englishWord"};
    const int amountOfCorrectAnswers{2};
    const int amountOfIncorrectAnswers{3};
    WordStatistics wordStatisticsWithZeroAnswers{englishWord};
    WordStatistics wordStatisticsWithAnswers{englishWord, amountOfCorrectAnswers, amountOfIncorrectAnswers};
};

TEST_F(WordStatisticsTest, givenWordStatisticsWithEnglishWord_shouldHaveEnglishWordWhichIsGiven)
{
    ASSERT_EQ(wordStatisticsWithZeroAnswers.getEnglishWord(), englishWord);
}

TEST_F(WordStatisticsTest,
       createWordStatisticsWithNoAnswers_shouldHaveAmountOfCorrectAndIncorrectAnswersSetToZero)
{
    ASSERT_EQ(wordStatisticsWithZeroAnswers.getAmountOfCorrectAnswers(), 0);
    ASSERT_EQ(wordStatisticsWithZeroAnswers.getAmountOfIncorrectAnswers(), 0);
}

TEST_F(WordStatisticsTest, givenWordStatisticsWithAnswers_shoulSetAmountsToGiven)
{
    ASSERT_EQ(wordStatisticsWithAnswers.getAmountOfCorrectAnswers(), amountOfCorrectAnswers);
    ASSERT_EQ(wordStatisticsWithAnswers.getAmountOfIncorrectAnswers(), amountOfIncorrectAnswers);
}

TEST_F(WordStatisticsTest, shouldAddCorrectAnswerToWordStatistics)
{
    const auto amountOfCorrectAnswersBeforeAddition =
        wordStatisticsWithZeroAnswers.getAmountOfCorrectAnswers();

    wordStatisticsWithZeroAnswers.addCorrectAnswer();

    const auto amountOfCorrectAnswersAfterAddition =
        wordStatisticsWithZeroAnswers.getAmountOfCorrectAnswers();
    ASSERT_EQ(amountOfCorrectAnswersAfterAddition, amountOfCorrectAnswersBeforeAddition + 1);
}

TEST_F(WordStatisticsTest, shouldAddIncorrectAnswerToWordStatistics)
{
    const auto amountOfIncorrectAnswersBeforeAddition =
        wordStatisticsWithZeroAnswers.getAmountOfIncorrectAnswers();

    wordStatisticsWithZeroAnswers.addIncorrectAnswer();

    const auto amountOfIncorrectAnswersAfterAddition =
        wordStatisticsWithZeroAnswers.getAmountOfIncorrectAnswers();
    ASSERT_EQ(amountOfIncorrectAnswersAfterAddition, amountOfIncorrectAnswersBeforeAddition + 1);
}

TEST_F(WordStatisticsTest, givenwordStatisticsWithAnswers_shouldResetAmountOfAnswers)
{
    wordStatisticsWithAnswers.resetAnswers();

    ASSERT_EQ(wordStatisticsWithAnswers.getAmountOfCorrectAnswers(), 0);
    ASSERT_EQ(wordStatisticsWithAnswers.getAmountOfIncorrectAnswers(), 0);
}
