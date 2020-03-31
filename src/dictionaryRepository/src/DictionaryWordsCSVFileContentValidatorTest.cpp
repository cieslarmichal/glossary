#include "DictionaryWordsCSVFileContentValidator.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace dictionaryRepository;

namespace
{
const std::string emptyContent{};
const std::string contentWithWordWithoutSeparator{"car"};
const std::string contentWithWordsWithoutSeparator{"car samochod"};
const std::string contentWithSeparator{",\n"};
const std::string contentWithWordOnlyAfterSeparator{",samochod\n"};
const std::string contentWithWordOnlyBeforeSeparator{"car,\n"};
const std::string contentWithWordBeforeAndAfterSeparator{"car,samochod"};
const std::string contentWithWordsBeforeAndAfterSeparator{"car,samochod\n"
                                                          "computer,komputer"};
const std::string contentWithSomeValidLinesAndOneInvalid{"car,samochod\n"
                                                         "powietrze,air\n"
                                                         ",krzeslo"};
const std::string contentWithSomeValidLinesAndEmptyLines{"\ncar,samochod\n\n\n"
                                                         "chair,krzeslo\n\n"};
}

class DictionaryWordsCSVFileContentValidatorTest : public Test
{
public:
    DictionaryWordsCSVFileContentValidator validator;
};

TEST_F(DictionaryWordsCSVFileContentValidatorTest, givenEmptyContent_shouldReturnValid)
{
    ASSERT_EQ(validator.validate(emptyContent), ValidationResult::Valid);
}

TEST_F(DictionaryWordsCSVFileContentValidatorTest,
       givenContentWithOneWordWithoutSeparator_shouldReturnInvalid)
{
    ASSERT_EQ(validator.validate(contentWithWordWithoutSeparator), ValidationResult::Invalid);
}

TEST_F(DictionaryWordsCSVFileContentValidatorTest,
       givenContentWithTwoWordsWithoutSeparator_shouldReturnInvalid)
{
    ASSERT_EQ(validator.validate(contentWithWordsWithoutSeparator), ValidationResult::Invalid);
}

TEST_F(DictionaryWordsCSVFileContentValidatorTest, givenContentWithOnlySeparator_shouldReturnInvalid)
{
    ASSERT_EQ(validator.validate(contentWithSeparator), ValidationResult::Invalid);
}

TEST_F(DictionaryWordsCSVFileContentValidatorTest, givenContentWithWordOnlyAfterSeparator_shouldReturnInvalid)
{
    ASSERT_EQ(validator.validate(contentWithWordOnlyAfterSeparator), ValidationResult::Invalid);
}

TEST_F(DictionaryWordsCSVFileContentValidatorTest, givenContentWithWordOnlyBeforeSeparator_shouldReturnValid)
{
    ASSERT_EQ(validator.validate(contentWithWordOnlyBeforeSeparator), ValidationResult::Valid);
}

TEST_F(DictionaryWordsCSVFileContentValidatorTest,
       givenContentWithWordBeforeAndAfterSeparator_shouldReturnValid)
{
    ASSERT_EQ(validator.validate(contentWithWordBeforeAndAfterSeparator), ValidationResult::Valid);
}

TEST_F(DictionaryWordsCSVFileContentValidatorTest,
       givenContentWithMultipleLineWithWordsBeforeAndAfterSeparator_shouldReturnValid)
{
    ASSERT_EQ(validator.validate(contentWithWordsBeforeAndAfterSeparator), ValidationResult::Valid);
}

TEST_F(DictionaryWordsCSVFileContentValidatorTest,
       givenContentWithSomeValidLinesAndOneInvalid_shouldReturnInvalid)
{
    ASSERT_EQ(validator.validate(contentWithSomeValidLinesAndOneInvalid), ValidationResult::Invalid);
}

TEST_F(DictionaryWordsCSVFileContentValidatorTest,
       givenContentWithSomeValidLinesAndEmptyLines_shouldReturnValid)
{
    ASSERT_EQ(validator.validate(contentWithSomeValidLinesAndEmptyLines), ValidationResult::Valid);
}