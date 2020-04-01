#include "StringHelper.h"

#include "gtest/gtest.h"

#include "StlOperators.h"

using namespace ::testing;
using namespace utils;

class StringHelperTest : public Test
{
public:
    const std::string element1{"aaa"};
    const std::string element2{"bbb"};
    const std::string element3{"ccc"};
    const std::string str{element1 + "\n" + element2 + "\n" + element3};
    const std::vector<std::string> strVec{element1, element2, element3};
    std::string stringBeforeCut{": </strong>a weapon"};
    const size_t startCutIndex{2};
    const size_t endCutIndex{10};
    const size_t startSubstringIndex{2};
    const size_t endSubstringIndex{5};
    const std::string stringAfterCut{": a weapon"};
    const std::string strSubstring{"</s"};
    const std::string stringWithUpperCases{"aaaAAAaABBBBbB"};
    const std::string stringWithoutUpperCases{"aaaaaaaabbbbbb"};
    std::string stringToTrim{"    bbb      "};
    std::string stringToTrim2{" cc bbb      "};
    const std::string stringAfterTrim{"bbb"};
    const std::string stringAfterTrim2{"cc bbb"};
    std::vector<std::string> stringsToTrim{stringToTrim, stringToTrim2};
    std::vector<std::string> stringsAfterTrim{stringAfterTrim, stringAfterTrim2};
    const std::string emptyStr{};
    const std::vector<std::string> emptyVec{};
    const std::vector<std::string> vecWithOneEmptyElement{""};
    const std::vector<std::string> vecWithEmptyElements{"", "", ""};
    std::vector<std::string> vecWithSomeEmptyElements{"", "aaa", "", "vvvv", ""};
    std::vector<std::string> vecWithDuplicates{"aaa", "aaa", "", "vvvv", "vvvv"};
    std::vector<std::string> vecWithoutDuplicates{"aaa", "", "vvvv"};
    std::vector<std::string> vecWithoutEmptyElements{"aaa", "vvvv"};
};

TEST_F(StringHelperTest, givenEmptyString_shouldVectorWithOneEmptyElement)
{
    const auto actualVec = split(emptyStr);

    ASSERT_EQ(actualVec, vecWithOneEmptyElement);
}

TEST_F(StringHelperTest, givenString_shouldSplitToVectorOfStringsByNewLines)
{
    const auto actualVec = split(str);

    ASSERT_EQ(actualVec, strVec);
}

TEST_F(StringHelperTest, givenEmptyVector_shouldReturnEmptyString)
{
    const auto actualStr = join(emptyVec);

    ASSERT_EQ(actualStr, emptyStr);
}

TEST_F(StringHelperTest, givenVectorOfStrings_shouldJoinElementsToString)
{
    const auto actualStr = join(strVec);

    ASSERT_EQ(actualStr, str);
}

TEST_F(StringHelperTest, givenString_shouldReturnCutFromStartIndexToEndIndex)
{
    const auto actualCut = cutOffFromString(stringBeforeCut, startCutIndex, endCutIndex);

    ASSERT_EQ(actualCut, stringAfterCut);
}

TEST_F(StringHelperTest, givenString_shouldCutFromStringFromStartIndexToEndIndex)
{
    cutOffString(stringBeforeCut, startCutIndex, endCutIndex);

    ASSERT_EQ(stringBeforeCut, stringAfterCut);
}

TEST_F(StringHelperTest, givenString_shouldReturnSubstringByStartAndEndIndex)
{
    const auto actualSubstring = substring(stringBeforeCut, startSubstringIndex, endSubstringIndex);

    ASSERT_EQ(actualSubstring, strSubstring);
}

TEST_F(StringHelperTest, givenString_shouldLowerAllCharacters)
{
    const auto actualStringWithLowerCases = getLowerCases(stringWithUpperCases);

    ASSERT_EQ(actualStringWithLowerCases, stringWithoutUpperCases);
}

TEST_F(StringHelperTest, givenVectorWithEmptyLines_shouldReturnEmptyVector)
{
    const auto actualNonEmptyLines = getNonEmptyLines(vecWithEmptyElements);

    ASSERT_TRUE(actualNonEmptyLines.empty());
}

TEST_F(StringHelperTest, givenVector_shouldReturnVectorWithoutEmptyStrings)
{
    const auto actualNonEmptyLines = getNonEmptyLines(vecWithSomeEmptyElements);

    ASSERT_EQ(actualNonEmptyLines, vecWithoutEmptyElements);
}

TEST_F(StringHelperTest, givenVectorWithEmptyLines_shouldRemoveEmptyLines)
{
    removeEmptyLines(vecWithSomeEmptyElements);

    ASSERT_EQ(vecWithSomeEmptyElements, vecWithoutEmptyElements);
}

TEST_F(StringHelperTest, givenVectorWithDuplicates_shouldRemoveDuplicates)
{
    removeDuplicates(vecWithDuplicates);

    ASSERT_TRUE(compareVectors(vecWithDuplicates, vecWithoutDuplicates));
}

TEST_F(StringHelperTest, givenVectorWithoutEmptyLines_shouldNotRemoveLines)
{
    const auto amountOfElementsBefore = vecWithoutEmptyElements.size();
    removeEmptyLines(vecWithoutEmptyElements);

    ASSERT_EQ(vecWithoutEmptyElements.size(), amountOfElementsBefore);
}

TEST_F(StringHelperTest, shouldTrimString)
{
    trim(stringToTrim);

    ASSERT_EQ(stringToTrim, stringAfterTrim);
}

TEST_F(StringHelperTest, shouldTrimStrings)
{
    trim(stringsToTrim);

    ASSERT_EQ(stringsToTrim, stringsAfterTrim);
}
