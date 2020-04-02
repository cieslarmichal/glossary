#include "WordCreator.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionRepository;

namespace
{
const PolishWord polishWord1{"pies"};
const PolishWord polishWord2{"herbata"};
const EnglishWord englishWord1{"dog"};
const EnglishWord englishWord2{"tea"};
const WordDescription wordDescription1{
    englishWord1,
    Description{DefinitionsWithExamples{DefinitionWithExample{Definition{"doggy"}, Example{"xxx"}}}, {}}};
const Word expectedWord{polishWord1, englishWord1, wordDescription1};
const Word expectedWordWithoutWordDescription{polishWord2, englishWord2, boost::none};
}

class WordCreatorTest : public Test
{
public:
    WordCreator creator;
};

TEST_F(WordCreatorTest, createWordWithWordDescription_shouldCreateThisWord)
{
    const auto createdWord = creator.create(polishWord1, englishWord1, wordDescription1);

    ASSERT_EQ(*createdWord, expectedWord);
}

TEST_F(WordCreatorTest, createWordWithoutWordDescription_shouldCreateThisWord)
{
    const auto createdWord = creator.create(polishWord2, englishWord2, boost::none);

    ASSERT_EQ(*createdWord, expectedWordWithoutWordDescription);
}