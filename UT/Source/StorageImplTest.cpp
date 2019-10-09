#include "StorageImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
Word word1("xxx", {}, {});
Word word2("yyy", {}, {});
Words words{word1, word2};
}

class StorageImplTest : public Test
{
public:

};

TEST_F(StorageImplTest, givenEmpty_getShouldReturnNone)
{
    StorageImpl emptyStorage{};

    auto result = emptyStorage.getWord("someword");

    ASSERT_EQ(result, boost::none);
}

TEST_F(StorageImplTest, givenInitializedStorage_shouldReturnWord)
{
    Words initWord{word1};
    StorageImpl storage{{initWord}};

    auto actualWord = storage.getWord("xxx");

    ASSERT_EQ(actualWord, word1);
}

TEST_F(StorageImplTest, givenEmptyStorage_shouldAddWord)
{
    StorageImpl storage;

    storage.addWord(word1);

    ASSERT_FALSE(storage.empty());
}

TEST_F(StorageImplTest, givenStorageWithTwoWords_shouldReturnTwoWords)
{
    StorageImpl storage{{word1, word2}};

    auto actualWords = storage.getWords();

    ASSERT_EQ(actualWords, words);
}

TEST_F(StorageImplTest, givenEmptyStorageThenAddOneWord_shouldIncreaseStorageSize)
{
    StorageImpl storage{};

    auto sizeBeforeAddition = storage.size();
    storage.addWord(word1);
    auto sizeAfterAddition = storage.size();

    ASSERT_TRUE(sizeAfterAddition > sizeBeforeAddition);
}

TEST_F(StorageImplTest, givenEmptyStorage_shouldReturnTrueOnEmptyCall)
{
    StorageImpl storage{};

    ASSERT_TRUE(storage.empty());
}

TEST_F(StorageImplTest, givenStorageWithTwoWords_shouldReturnTwoElementsBasingOnBeginEnd)
{
    StorageImpl storage{{word1, word2}};

    auto amountOfWords = std::distance(storage.begin(), storage.end());

    ASSERT_EQ(amountOfWords, 2);
}
