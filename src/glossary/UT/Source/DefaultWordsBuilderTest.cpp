#include "DefaultWordsBuilder.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordDescriptionRepository;
using namespace translationsDb;

namespace
{
const PolishWord polishWord1{"pies"};
const PolishWord polishWord2{"herbata"};
const PolishWord polishWord3{"kot"};
const EnglishWord englishWord1{"dog"};
const EnglishWord englishWord2{"tea"};
const EnglishWord englishWord3{"cat"};
const WordDescription wordDescription1{
    englishWord1,
    Description{DefinitionsWithExamples{DefinitionWithExample{Definition{"doggy"}, Example{"xxx"}}}, {}}};
const WordDescription wordDescription2{
    englishWord2,
    Description{DefinitionsWithExamples{DefinitionWithExample{Definition{"herbals"}, Example{"yyy"}}}, {}}};
const WordDescription wordDescription3{
    englishWord3,
    Description{DefinitionsWithExamples{DefinitionWithExample{Definition{"tiger"}, Example{"zzz"}}}, {}}};
const WordsDescriptions wordsDescriptions{wordDescription2, wordDescription1, wordDescription3};
const WordsDescriptions wordsDescriptionsWithMissingWordDescription{wordDescription1, wordDescription2};
const Translations translations{{"pies", "dog"}, {"kot", "cat"}, {"herbata", "tea"}};
const Words words{{polishWord1, englishWord1, wordDescription1},
                  {polishWord3, englishWord3, wordDescription3},
                  {polishWord2, englishWord2, wordDescription2}};
const Words wordsWithOneEmptyDescription{{polishWord1, englishWord1, wordDescription1},
                                         {polishWord3, englishWord3, WordDescription{englishWord3, {}}},
                                         {polishWord2, englishWord2, wordDescription2}};
}

class WordsBuilderImplTest : public Test
{
public:
    DefaultWordsBuilder wordsBuilder;
};

TEST_F(WordsBuilderImplTest, givenTranslationsWithWordsDescriptionsInOtherOrder_shouldBindByEnglishWords)
{
    const auto actualWords = wordsBuilder.buildWords(translations, wordsDescriptions);

    ASSERT_EQ(actualWords, words);
}

TEST_F(WordsBuilderImplTest,
       givenTranslationsWithoutOneWordDescription_shouldBindByEnglishWordsAndAddEmptyDescription)
{
    const auto actualWords =
        wordsBuilder.buildWords(translations, wordsDescriptionsWithMissingWordDescription);

    ASSERT_EQ(actualWords, wordsWithOneEmptyDescription);
}