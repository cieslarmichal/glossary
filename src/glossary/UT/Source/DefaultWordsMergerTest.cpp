#include "DefaultWordsMerger.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordDescriptionRepository;
using namespace dictionaryRepository;

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
const DictionaryWords dictionaryWords{
    {"dog", std::string{"pies"}}, {"cat", std::string{"kot"}}, {"tea", std::string{"herbata"}}};
const Words words{{englishWord1, polishWord1, wordDescription1},
                  {englishWord3, polishWord3, wordDescription3},
                  {englishWord2, polishWord2, wordDescription2}};
const Words wordsWithOneEmptyDescription{{englishWord1, polishWord1, wordDescription1},
                                         {englishWord3, polishWord3, boost::none},
                                         {englishWord2, polishWord2, wordDescription2}};
}

class DefaultWordsMergerTest : public Test
{
public:
    DefaultWordsMerger wordsMerger;
};

TEST_F(DefaultWordsMergerTest, givenTranslationsWithWordsDescriptionsInOtherOrder_shouldBindByEnglishWords)
{
    const auto actualWords = wordsMerger.mergeWords(dictionaryWords, wordsDescriptions);

    ASSERT_EQ(actualWords, words);
}

TEST_F(DefaultWordsMergerTest,
       givenTranslationsWithoutOneWordDescription_shouldBindByEnglishWordsAndAddEmptyDescription)
{
    const auto actualWords =
        wordsMerger.mergeWords(dictionaryWords, wordsDescriptionsWithMissingWordDescription);

    ASSERT_EQ(actualWords, wordsWithOneEmptyDescription);
}