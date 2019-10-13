#include "MemoryStorage.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const Word word1("xxx", {}, {});
const Word word2("yyy", {}, {});
const Words words{word1, word2};
}

class MemoryStorageTest : public Test
{
public:
    MemoryStorage storage{};
};

TEST_F(MemoryStorageTest, givenWordAddition_shouldAddWord)
{
    storage.addWord(word1);

    ASSERT_FALSE(storage.empty());
    ASSERT_EQ(storage.size(), Words::size_type{1});
}

TEST_F(MemoryStorageTest, addTwoDifferentWords_shouldAddTwoWords)
{
    storage.addWord(word1);
    storage.addWord(word2);

    const auto actualWords = storage.getWords();

    ASSERT_EQ(actualWords, words);
}

TEST_F(MemoryStorageTest, addTwoSameWords_shouldAddOnlyOne)
{
    storage.addWord(word1);
    storage.addWord(word1);

    ASSERT_EQ(storage.size(), Words::size_type{1});
}

TEST_F(MemoryStorageTest, givenEmptyStorage_getShouldNotReturnWord)
{
    const auto result = storage.getWord("someword");

    ASSERT_EQ(result, boost::none);
}

TEST_F(MemoryStorageTest, givenStorageWithExactWord_shouldReturnWord)
{
    storage.addWord(word1);

    const auto actualWord = storage.getWord("xxx");

    ASSERT_EQ(actualWord, word1);
}

TEST_F(MemoryStorageTest, givenStorageWithTwoWords_shouldReturnTwoElementsBasingOnBeginEnd)
{
    storage.addWord(word1);
    storage.addWord(word2);

    const auto amountOfWords = std::distance(storage.begin(), storage.end());

    ASSERT_EQ(amountOfWords, 2);
}

TEST_F(MemoryStorageTest, givenEmptyStorage_shouldBeEmpty)
{
    ASSERT_TRUE(storage.empty());
}

TEST_F(MemoryStorageTest, givenWordNotExistingInStorage_getShouldNotContainThisWord)
{
    const auto contains = storage.contains("someword");

    ASSERT_FALSE(contains);
}

TEST_F(MemoryStorageTest, givenWordExistingInStorage_getShouldContainThisWord)
{
    storage.addWord(word1);

    const auto contains = storage.contains(word1.englishWord);

    ASSERT_TRUE(contains);
}

