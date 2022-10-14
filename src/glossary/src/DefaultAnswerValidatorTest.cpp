#include "DefaultAnswerValidator.h"

#include "gtest/gtest.h"


using namespace ::testing;
using namespace glossary;

namespace
{
const std::string word{"slon"};
const std::string userWordInput{"slon"};
const std::string userWordInputWithDifferentCaseSizes{"sLoN"};
const std::string userWordInputDifferentThanWord{"xxxxxxx"};
const std::string userYesInput1{"yes"};
const std::string userYesInput2{"y"};
const std::string userYesInput1WithDifferentCaseSizes{"YeS"};
const std::string userYesInput2WithDifferentCaseSizes{"Y"};
const std::string userInputOtherThanYes{"saidsjaisdaj"};
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