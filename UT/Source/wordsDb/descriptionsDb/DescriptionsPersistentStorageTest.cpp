#include "wordsDb/descriptionsDb/DescriptionsPersistentStorage.h"

#include "FileAccessMock.h"
#include "wordsDb/descriptionsDb/DescriptionsSerializerMock.h"

#include "exceptions/FileNotFound.h"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::descriptionsDb;

namespace
{
const std::string filepath{"../database/words.txt"};
const EnglishWord nonExistingWord("nonExistingWord");
const EnglishWord englishWord1("englishWord1");
const EnglishWord englishWord2("englishWord2");
const WordDescription word1(englishWord1, {}, {});
const WordDescription word2(englishWord2, {}, {});
const WordsDescriptions words{word1, word2};
const WordDescription word3("yzzxc12yy", {}, {});
const WordsDescriptions wordsAfterAddition{word1, word2, word3};
}

class DescriptionsPersistentStorageTest : public Test
{
public:
    void expectTwoWordsDescriptionsLoad()
    {
        EXPECT_CALL(*fileAccess, readContent(filepath))
            .WillOnce(Return("some content"));
        EXPECT_CALL(*serializer, deserialize("some content"))
            .WillOnce(Return(words));
    }

    std::shared_ptr<FileAccessMock> fileAccess =
        std::make_shared<NiceMock<FileAccessMock>>();
    std::shared_ptr<DescriptionsSerializerMock> serializer =
        std::make_shared<NiceMock<DescriptionsSerializerMock>>();
};

TEST_F(DescriptionsPersistentStorageTest,
       givenPersistentStorageWithEmptyFile_shouldNotLoadAnyWords)
{
    EXPECT_CALL(*fileAccess, readContent(filepath)).WillOnce(Return(""));
    EXPECT_CALL(*serializer, deserialize(""))
        .WillOnce(Return(WordsDescriptions{}));
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWordsDescriptions();

    ASSERT_TRUE(actualWords.empty());
}

TEST_F(DescriptionsPersistentStorageTest,
       givenPersistentStorageWithFileWithWords_shouldLoadWords)
{
    expectTwoWordsDescriptionsLoad();
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWordsDescriptions();

    ASSERT_EQ(actualWords, words);
}

TEST_F(DescriptionsPersistentStorageTest, givenInvalidFile_shouldReturnNoWords)
{
    EXPECT_CALL(*fileAccess, readContent(filepath))
        .WillOnce(Throw(exceptions::FileNotFound{""}));
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWordsDescriptions();

    EXPECT_TRUE(actualWords.empty());
}

TEST_F(DescriptionsPersistentStorageTest,
       givenWordAddition_shouldAddWordAndSerialize)
{
    expectTwoWordsDescriptionsLoad();
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filepath, "words"));
    EXPECT_CALL(*serializer, serialize(wordsAfterAddition))
        .WillOnce(Return("words"));

    persistentStorage.addWordDescription(word3);

    ASSERT_FALSE(persistentStorage.empty());
}

TEST_F(DescriptionsPersistentStorageTest,
       givenExistingEnglishWord_shouldReturnThisWord)
{
    expectTwoWordsDescriptionsLoad();
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWord = persistentStorage.getWordDescription(englishWord1);

    ASSERT_EQ(*actualWord, word1);
}

TEST_F(DescriptionsPersistentStorageTest,
       givenNonExistingEnglishWord_shouldReturnThisWord)
{
    expectTwoWordsDescriptionsLoad();
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWord =
        persistentStorage.getWordDescription(nonExistingWord);

    ASSERT_EQ(actualWord, boost::none);
}

TEST_F(DescriptionsPersistentStorageTest,
       givenTwoWordsDescriptions_shouldContainsThoseTwoWordsDescriptions)
{
    expectTwoWordsDescriptionsLoad();
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_TRUE(persistentStorage.contains(englishWord1));
    ASSERT_TRUE(persistentStorage.contains(englishWord2));
    ASSERT_FALSE(persistentStorage.contains(nonExistingWord));
}

TEST_F(DescriptionsPersistentStorageTest,
       given_TwoWordsDescriptions_shouldDistanceOfTwoBetweenBeginAndEnd)
{
    expectTwoWordsDescriptionsLoad();
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto distance =
        std::distance(persistentStorage.begin(), persistentStorage.end());
    ASSERT_EQ(distance, 2);
}
