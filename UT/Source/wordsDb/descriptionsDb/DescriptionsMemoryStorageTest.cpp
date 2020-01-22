#include "gtest/gtest.h"
#include "wordsDb/descriptionsDb/DescriptionsMemoryStorage.h"

using namespace ::testing;

namespace
{
const WordDescription word1("xxx", {}, {});
const WordDescription word2("yyy", {}, {});
const Words words{word1, word2};
}

using namespace wordsDb::descriptionsDb;

class DescriptionsMemoryStorageTest : public Test
{
public:
    DescriptionsMemoryStorage storage{};
};

TEST_F(DescriptionsMemoryStorageTest, givenWordAddition_shouldAddWord)
{
    storage.addWord(word1);

    ASSERT_FALSE(storage.empty());
    ASSERT_EQ(storage.size(), Words::size_type{1});
}

TEST_F(DescriptionsMemoryStorageTest, addTwoDifferentWords_shouldAddTwoWords)
{
    storage.addWord(word1);
    storage.addWord(word2);

    const auto actualWords = storage.getWords();

    ASSERT_EQ(actualWords, words);
}

TEST_F(DescriptionsMemoryStorageTest, addTwoSameWords_shouldAddOnlyOne)
{
    storage.addWord(word1);
    storage.addWord(word1);

    ASSERT_EQ(storage.size(), Words::size_type{1});
}

TEST_F(DescriptionsMemoryStorageTest, givenEmptyStorage_getShouldNotReturnWord)
{
    const auto result = storage.getWord("someword");

    ASSERT_EQ(result, boost::none);
}

TEST_F(DescriptionsMemoryStorageTest, givenStorageWithExactWord_shouldReturnWord)
{
    storage.addWord(word1);

    const auto actualWord = storage.getWord("xxx");

    ASSERT_EQ(actualWord, word1);
}

TEST_F(DescriptionsMemoryStorageTest,
       givenStorageWithTwoWords_shouldReturnTwoElementsBasingOnBeginEnd)
{
    storage.addWord(word1);
    storage.addWord(word2);

    const auto amountOfWords = std::distance(storage.begin(), storage.end());

    ASSERT_EQ(amountOfWords, 2);
}

TEST_F(DescriptionsMemoryStorageTest, givenEmptyStorage_shouldBeEmpty)
{
    ASSERT_TRUE(storage.empty());
}

TEST_F(DescriptionsMemoryStorageTest,
       givenWordNotExistingInStorage_getShouldNotContainThisWord)
{
    const auto contains = storage.contains("someword");

    ASSERT_FALSE(contains);
}

TEST_F(DescriptionsMemoryStorageTest, givenWordExistingInStorage_getShouldContainThisWord)
{
    storage.addWord(word1);

    const auto contains = storage.contains(word1.englishWord);

    ASSERT_TRUE(contains);
}
