#include "DefaultAnswerValidator.h"

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

class DefaultAnswerValidatorTest : public Test
{
public:
    DefaultAnswerValidator validator;
};

TEST_F(DefaultAnswerValidatorTest, givenUserInputSameAsEnglishWord_shouldReturnEqual)
{
    ASSERT_TRUE(validator.validateAnswer(userWordInput, word));
}

TEST_F(DefaultAnswerValidatorTest, givenUserInputSameAsEnglishWordButDifferentCaseSizes_shouldReturnEqual)
{
    ASSERT_TRUE(validator.validateAnswer(userWordInputWithDifferentCaseSizes, word));
}

TEST_F(DefaultAnswerValidatorTest, givenUserInputDifferentThanEnglishWord_shouldReturnNotEqual)
{
    ASSERT_FALSE(validator.validateAnswer(userWordInputDifferentThanWord, word));
}

TEST_F(DefaultAnswerValidatorTest, givenUserInputWithYes_shouldReturnYesAnswerTrue)
{
    ASSERT_TRUE(validator.validateYesAnswer(userYesInput1));
    ASSERT_TRUE(validator.validateYesAnswer(userYesInput2));
}

TEST_F(DefaultAnswerValidatorTest, givenUserInputWithYesButDifferentCaseSizes_shouldReturnYesAnswerTrue)
{
    ASSERT_TRUE(validator.validateYesAnswer(userYesInput1WithDifferentCaseSizes));
    ASSERT_TRUE(validator.validateYesAnswer(userYesInput2WithDifferentCaseSizes));
}

TEST_F(DefaultAnswerValidatorTest, givenUserInputDifferentThanYes_shouldReturYesAnswerFalse)
{
    ASSERT_FALSE(validator.validateYesAnswer(userInputOtherThanYes));
}
