#include "WordDescriptionCorrespondingToEnglishWordFinder.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordDescriptionRepository;

namespace
{
const EnglishWord englishWord1{"dog"};
const EnglishWord englishWord2{"tea"};
const EnglishWord notContainedEnglishWord{"tea"};
const WordDescription wordDescription1{
    englishWord1,
    Description{DefinitionsWithExamples{DefinitionWithExample{Definition{"doggy"}, Example{"xxx"}}}, {}}};
const WordDescription wordDescription2{
    englishWord2,
    Description{DefinitionsWithExamples{DefinitionWithExample{Definition{"herbals"}, Example{"yyy"}}}, {}}};
const WordsDescriptions wordsDescriptions{wordDescription1, wordDescription2};
const WordsDescriptions emptyWordsDescriptions{};
}

class WordDescriptionCorrespondingToEnglishWordFinderTest : public Test
{
public:
    WordDescriptionCorrespondingToEnglishWordFinder finder;
};

TEST_F(WordDescriptionCorrespondingToEnglishWordFinderTest, givenEmptyWordsDescriptions_shouldReturnNone)
{
    const auto foundWordDescription =
        finder.findCorrespondingWordDescription(englishWord1, emptyWordsDescriptions);

    ASSERT_TRUE(foundWordDescription == boost::none);
}

TEST_F(WordDescriptionCorrespondingToEnglishWordFinderTest,
       givenEnglishWordNotContainedInWordsDescriptions_shouldReturnNone)
{
    const auto foundWordDescription =
        finder.findCorrespondingWordDescription(notContainedEnglishWord, emptyWordsDescriptions);

    ASSERT_TRUE(foundWordDescription == boost::none);
}

TEST_F(WordDescriptionCorrespondingToEnglishWordFinderTest,
       givenEnglishWordContainedInWordsDescriptions_shouldReturnCorrespondingWordDescription)
{
    const auto foundWordDescription =
        finder.findCorrespondingWordDescription(englishWord1, wordsDescriptions);

    ASSERT_EQ(*foundWordDescription, wordDescription1);
}
