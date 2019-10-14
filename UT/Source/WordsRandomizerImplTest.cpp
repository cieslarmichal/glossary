#include "WordsRandomizerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const Word word1("computer", "komputer",
                 {{{"definition", std::string{"example"}}, {"definition2", std::string{"example2"}}},
                  {"sentence"}});
const Word word2("tea", "herbata", {});
const Word word3("headphones", "sluchawki", {});
const Words words{word1, word2, word3};
const Words wordsWithOneWord{word1};
const Words emptyWords{};
}

class WordsRandomizerImplTest : public Test
{
public:
    WordsRandomizerImpl randomizer;
};

TEST_F(WordsRandomizerImplTest, givenNoWords_shouldReturnNoWords)
{
    const auto actualRandomizedWords = randomizer.randomize(emptyWords);

    ASSERT_TRUE(actualRandomizedWords.empty());
}

TEST_F(WordsRandomizerImplTest, givenWords_shouldReturnRandomizedWords)
{
    const auto actualRandomizedWords = randomizer.randomize(words);

    ASSERT_NE(actualRandomizedWords, words);
}

TEST_F(WordsRandomizerImplTest, givenOneWord_shouldReturnSameWord)
{
    const auto actualRandomizedWords = randomizer.randomize(wordsWithOneWord);

    ASSERT_EQ(actualRandomizedWords, wordsWithOneWord);
}
