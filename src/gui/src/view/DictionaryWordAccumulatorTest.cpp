#include "DictionaryWordAccumulator.h"



#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::gui::view;

class DictionaryWordAccumulatorTest : public Test
{
public:
    const FormattedDictionaryWord emptyDictionaryWord{"", ""};
    const FormattedDictionaryWord dictionaryWordWithTranslation{"englishWord1", "translation1"};
    const FormattedDictionaryWord dictionaryWordWithoutTranslation{"englishWord2", ""};
    const QString accumulatedDictionaryWordWithTranslation{"englishWord1 - translation1"};
    const QString accumulatedDictionaryWordWithoutTranslation{"englishWord2 - "};
    const QString accumulatedEmptyDictionaryWord{""};
    const QString accumulatedWordWithoutDash{"englishWord1"};
    const QString accumulatedTwoWordsSeparatedWithSpace{"englishWord1 translation1"};
    const QString accumulatedTwoWordsSeparatedWithColon{"englishWord1 : translation1"};
    DictionaryWordAccumulator dictionaryWordAccumulator;
};

TEST_F(DictionaryWordAccumulatorTest, givenEmptyDictionaryWord_shouldReturnEmpty)
{
    const auto actualAccumulatedDictionaryWord =
        dictionaryWordAccumulator.accumulateDictionaryWord(emptyDictionaryWord);

    ASSERT_EQ(actualAccumulatedDictionaryWord, accumulatedEmptyDictionaryWord);
}

TEST_F(DictionaryWordAccumulatorTest,
       givenDictionaryWord_shouldAccumulateToQStringWithWordAndTranslationSeparatedByDash)
{
    const auto actualAccumulatedDictionaryWord =
        dictionaryWordAccumulator.accumulateDictionaryWord(dictionaryWordWithTranslation);

    ASSERT_EQ(actualAccumulatedDictionaryWord, accumulatedDictionaryWordWithTranslation);
}

TEST_F(DictionaryWordAccumulatorTest,
       givenDictionaryWordWithoutTranslation_shouldAccumulateToQStringWithWordAndDash)
{
    const auto actualAccumulatedDictionaryWord =
        dictionaryWordAccumulator.accumulateDictionaryWord(dictionaryWordWithoutTranslation);

    ASSERT_EQ(actualAccumulatedDictionaryWord, accumulatedDictionaryWordWithoutTranslation);
}

TEST_F(DictionaryWordAccumulatorTest, givenEmptyString_shouldReturnNone)
{
    const auto actualDictionaryWord =
        dictionaryWordAccumulator.separateDictionaryWord(accumulatedEmptyDictionaryWord);

    ASSERT_EQ(actualDictionaryWord, std::nullopt);
}

TEST_F(DictionaryWordAccumulatorTest, givenWordWithoutDash_shouldReturnNone)
{
    const auto actualDictionaryWord =
        dictionaryWordAccumulator.separateDictionaryWord(accumulatedWordWithoutDash);

    ASSERT_EQ(actualDictionaryWord, std::nullopt);
}

TEST_F(DictionaryWordAccumulatorTest, givenStringWithTwoWordsSeparetedBySpaces_shouldReturnNone)
{
    const auto actualDictionaryWord =
        dictionaryWordAccumulator.separateDictionaryWord(accumulatedTwoWordsSeparatedWithSpace);

    ASSERT_EQ(actualDictionaryWord, std::nullopt);
}

TEST_F(DictionaryWordAccumulatorTest,
       givenStringWithTwoWordsSeparetedByCharacterOtherThanDash_shouldReturnNone)
{
    const auto actualDictionaryWord =
        dictionaryWordAccumulator.separateDictionaryWord(accumulatedTwoWordsSeparatedWithColon);

    ASSERT_EQ(actualDictionaryWord, std::nullopt);
}

TEST_F(DictionaryWordAccumulatorTest, givenStringWithTwoWordsSeparetedByDash_shouldReturnDictionaryWord)
{
    const auto actualDictionaryWord =
        dictionaryWordAccumulator.separateDictionaryWord(accumulatedDictionaryWordWithTranslation);

    ASSERT_EQ(*actualDictionaryWord, dictionaryWordWithTranslation);
}

TEST_F(DictionaryWordAccumulatorTest, givenStringWithWordAndDash_shouldReturnDictionaryWordWithoutTranslation)
{
    const auto actualDictionaryWord =
        dictionaryWordAccumulator.separateDictionaryWord(accumulatedDictionaryWordWithoutTranslation);

    ASSERT_EQ(*actualDictionaryWord, dictionaryWordWithoutTranslation);
}