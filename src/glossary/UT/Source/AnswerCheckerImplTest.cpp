#include "AnswerCheckerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const PolishWord word{"slon"};
const UserInput userWordInput{"slon"};
const UserInput userWordInputWithDifferentCaseSizes{"sLoN"};
const UserInput userWordInputDifferentThanWord{"xxxxxxx"};
const UserInput userYesInput1{"yes"};
const UserInput userYesInput2{"y"};
const UserInput userYesInput1WithDifferentCaseSizes{"YeS"};
const UserInput userYesInput2WithDifferentCaseSizes{"Y"};
const UserInput userInputOtherThanYes{"saidsjaisdaj"};

}

class AnswerCheckerImplTest : public Test
{
public:
    AnswerCheckerImpl checker;
};

TEST_F(AnswerCheckerImplTest, givenUserInputSameAsEnglishWord_shouldReturnEqual)
{
    ASSERT_TRUE(checker.correctWordAnswer(userWordInput, word));
}

TEST_F(AnswerCheckerImplTest,
       givenUserInputSameAsEnglishWordButDifferentCaseSizes_shouldReturnEqual)
{
    ASSERT_TRUE(
        checker.correctWordAnswer(userWordInputWithDifferentCaseSizes, word));
}

TEST_F(AnswerCheckerImplTest,
       givenUserInputDifferentThanEnglishWord_shouldReturnNotEqual)
{
    ASSERT_FALSE(
        checker.correctWordAnswer(userWordInputDifferentThanWord, word));
}

TEST_F(AnswerCheckerImplTest, givenUserInputWithYes_shouldReturnYesAnswerTrue)
{
    ASSERT_TRUE(checker.yesAnswer(userYesInput1));
    ASSERT_TRUE(checker.yesAnswer(userYesInput2));
}

TEST_F(AnswerCheckerImplTest,
       givenUserInputWithYesButDifferentCaseSizes_shouldReturnYesAnswerTrue)
{
    ASSERT_TRUE(checker.yesAnswer(userYesInput1WithDifferentCaseSizes));
    ASSERT_TRUE(checker.yesAnswer(userYesInput2WithDifferentCaseSizes));
}

TEST_F(AnswerCheckerImplTest,
       givenUserInputDifferentThanYes_shouldReturYesAnswerFalse)
{
    ASSERT_FALSE(checker.yesAnswer(userInputOtherThanYes));
}
