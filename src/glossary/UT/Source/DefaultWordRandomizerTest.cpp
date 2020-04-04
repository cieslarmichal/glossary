#include "DefaultWordRandomizer.h"

#include "gtest/gtest.h"

#include "utils/RandomNumberGeneratorMock.h"

using namespace ::testing;
using namespace glossary;

namespace
{
const Word word1{"englishWord1", boost::none, boost::none};
const Word word2{"englishWord2", boost::none, boost::none};
const Word word3{"englishWord3", boost::none, boost::none};
const Words emptyWords{};
const Words wordsWithOneWord{word1};
const Words words{word1, word2, word3};
const int wordsWithOneWordLastWordIndex{0};
const int wordsLastWordIndex{2};
}

class DefaultWordRandomizerTest : public Test
{
public:
    std::shared_ptr<utils::RandomNumberGeneratorMock> randomNumberGenerator =
        std::make_shared<StrictMock<utils::RandomNumberGeneratorMock>>();
    DefaultWordRandomizer wordRandomizer{randomNumberGenerator};
};

TEST_F(DefaultWordRandomizerTest, givenNoWords_shouldThrowInvalidArgument)
{
    ASSERT_THROW(wordRandomizer.randomizeWord(emptyWords), std::invalid_argument);
}

TEST_F(DefaultWordRandomizerTest, givenOneWord_shouldReturnThisWord)
{
    EXPECT_CALL(*randomNumberGenerator, generate(0, wordsWithOneWordLastWordIndex)).WillOnce(Return(0));

    const auto actualRandomizedWord = wordRandomizer.randomizeWord(wordsWithOneWord);

    ASSERT_EQ(actualRandomizedWord, word1);
}

TEST_F(DefaultWordRandomizerTest, givenWords_shouldReturnOneOfWords)
{
    EXPECT_CALL(*randomNumberGenerator, generate(0, wordsLastWordIndex)).WillOnce(Return(2));

    const auto actualRandomizedWord = wordRandomizer.randomizeWord(words);

    ASSERT_EQ(actualRandomizedWord, word3);
}