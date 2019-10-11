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

TEST_F(MemoryStorageTest, givenEmptyStorage_getShouldReturnNone)
{
    auto result = storage.getWord("someword");

    ASSERT_EQ(result, boost::none);
}

TEST_F(MemoryStorageTest, givenWordAddition_shouldAddWord)
{
    storage.addWord(word1);

    ASSERT_FALSE(storage.empty());
    ASSERT_EQ(storage.size(), Words::size_type{1});
}

TEST_F(MemoryStorageTest, givenStorageWithWord_shouldReturnWord)
{
    storage.addWord(word1);

    auto actualWord = storage.getWord("xxx");

    ASSERT_EQ(actualWord, word1);
}

TEST_F(MemoryStorageTest, addTwoDifferentWords_shouldAddTwoWords)
{
    storage.addWord(word1);
    storage.addWord(word2);

    auto actualWords = storage.getWords();

    ASSERT_EQ(actualWords, words);
}

TEST_F(MemoryStorageTest, addTwoSameWords_shouldAddOnlyOne)
{
    storage.addWord(word1);
    storage.addWord(word1);

    ASSERT_EQ(storage.size(), Words::size_type{1});
}

TEST_F(MemoryStorageTest, givenEmptyStorage_shouldBeEmpty)
{
    ASSERT_TRUE(storage.empty());
}

TEST_F(MemoryStorageTest, givenStorageWithTwoWords_shouldReturnTwoElementsBasingOnBeginEnd)
{
    storage.addWord(word1);
    storage.addWord(word2);

    auto amountOfWords = std::distance(storage.begin(), storage.end());

    ASSERT_EQ(amountOfWords, 2);
}
