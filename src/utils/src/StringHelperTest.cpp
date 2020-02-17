#include "StringHelper.h"

#include "gtest/gtest.h"

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
    const std::string emptyStr{};
    const std::vector<std::string> emptyVec{};
    const std::vector<std::string> vecWithOneEmptyElement{""};
};

TEST_F(StringHelperTest, givenEmptyString_shouldVectorWithOneEmptyElement)
{
    const auto actualVec = getSplitLines(emptyStr);

    ASSERT_EQ(actualVec, vecWithOneEmptyElement);
}

TEST_F(StringHelperTest, givenString_shouldSplitToVectorOfStringsByNewLines)
{
    const auto actualVec = getSplitLines(str);

    ASSERT_EQ(actualVec, strVec);
}

TEST_F(StringHelperTest, givenEmptyVector_shouldReturnEmptyString)
{
    const auto actualStr = getJoinedLines(emptyVec);

    ASSERT_EQ(actualStr, emptyStr);
}

TEST_F(StringHelperTest, givenVectorOfStrings_shouldJoinElementsToString)
{
    const auto actualStr = getJoinedLines(strVec);

    ASSERT_EQ(actualStr, str);
}

TEST_F(StringHelperTest, givenString_shouldReturnCutFromStartIndexToEndIndex)
{
    const auto actualCut =
        cutOffFromString(stringBeforeCut, startCutIndex, endCutIndex);

    ASSERT_EQ(actualCut, stringAfterCut);
}

TEST_F(StringHelperTest,
       givenString_shouldCutFromStringFromStartIndexToEndIndex)
{
    cutOffString(stringBeforeCut, startCutIndex, endCutIndex);

    ASSERT_EQ(stringBeforeCut, stringAfterCut);
}

TEST_F(StringHelperTest, givenString_shouldReturnSubstringByStartAndEndIndex)
{
    const auto actualSubstring =
        substring(stringBeforeCut, startSubstringIndex, endSubstringIndex);

    ASSERT_EQ(actualSubstring, strSubstring);
}

TEST_F(StringHelperTest, givenString_shouldLowerAllCharacters)
{
    const auto actualStringWithLowerCases = getLowerCases(stringWithUpperCases);

    ASSERT_EQ(actualStringWithLowerCases, stringWithoutUpperCases);
}
