#include "AnswerCheckerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const EnglishWord word{"elephant"};
const UserInput userInput{"elephant"};
const UserInput userInputWithDifferentCaseSizes{"ElEPhanT"};
const UserInput userInputDeiiferentThanWord{"xxxxxxx"};
}

class AnswerCheckerImplTest : public Test
{
public:
    AnswerCheckerImpl checker;
};

TEST_F(AnswerCheckerImplTest, givenUserInputSameAsEnglishWord_shouldReturnEqual)
{
    ASSERT_TRUE(checker.checkAnswer(userInput, word));
}

TEST_F(AnswerCheckerImplTest, givenUserInputSameAsEnglishWordButDifferentCaseSizes_shouldReturnEqual)
{
    ASSERT_TRUE(checker.checkAnswer(userInputWithDifferentCaseSizes, word));
}

TEST_F(AnswerCheckerImplTest, givenUserInputDifferentThanEnglishWord_shouldReturnNotEqual)
{
    ASSERT_FALSE(checker.checkAnswer(userInputDeiiferentThanWord, word));
}
