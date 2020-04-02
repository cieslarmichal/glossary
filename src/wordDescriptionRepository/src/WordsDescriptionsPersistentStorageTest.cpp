#include "WordsDescriptionsPersistentStorage.h"

#include "gtest/gtest.h"

#include "WordsDescriptionsSerializerMock.h"
#include "utils/FileAccessMock.h"

#include "utils/GetProjectPath.h"
#include "utils/exceptions/FileNotFound.h"

using namespace ::testing;
using namespace glossary::wordDescriptionRepository;

namespace
{
const std::string filePath{utils::getProjectPath("glossary") + "database/wordsDescriptions.txt"};
const EnglishWord nonExistingWord("nonExistingWord");
const EnglishWord englishWord1("englishWord1");
const EnglishWord englishWord2("englishWord2");
const WordDescription word1(englishWord1, {});
const WordDescription word2(englishWord2, {});
const WordsDescriptions words{word1, word2};
const WordDescription word3("yzzxc12yy", {});
const WordsDescriptions wordsAfterAddition{word1, word2, word3};
}

class WordsDescriptionsPersistentStorageTest : public Test
{
public:
    void expectTwoWordsDescriptionsLoad()
    {
        EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return("some content"));
        EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(words));
    }

    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    std::shared_ptr<WordsDescriptionsSerializerMock> serializer =
        std::make_shared<StrictMock<WordsDescriptionsSerializerMock>>();
};

TEST_F(WordsDescriptionsPersistentStorageTest, givenPersistentStorageWithEmptyFile_shouldBeEmpty)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return(""));
    EXPECT_CALL(*serializer, deserialize("")).WillOnce(Return(WordsDescriptions{}));
    WordsDescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_TRUE(persistentStorage.empty());
}

TEST_F(WordsDescriptionsPersistentStorageTest, givenPersistentStorageWithFileWithWords_shouldLoadWords)
{
    expectTwoWordsDescriptionsLoad();
    WordsDescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWordsDescriptions();

    ASSERT_EQ(actualWords, words);
}

TEST_F(WordsDescriptionsPersistentStorageTest, givenInvalidFile_shouldReturnNoWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Throw(utils::exceptions::FileNotFound{""}));
    WordsDescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWordsDescriptions();

    EXPECT_TRUE(actualWords.empty());
}

TEST_F(WordsDescriptionsPersistentStorageTest, givenWordAddition_shouldAddWordAndSerialize)
{
    expectTwoWordsDescriptionsLoad();
    WordsDescriptionsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filePath, "words"));
    EXPECT_CALL(*serializer, serialize(wordsAfterAddition)).WillOnce(Return("words"));

    persistentStorage.addWordDescription(word3);

    ASSERT_EQ(persistentStorage.size(), 3);
}

TEST_F(WordsDescriptionsPersistentStorageTest,
       givenWordAdditionAndNonExistingFile_shouldAddWordAndNotSerialize)
{
    expectTwoWordsDescriptionsLoad();
    WordsDescriptionsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filePath, "words")).WillOnce(Throw(utils::exceptions::FileNotFound{""}));
    EXPECT_CALL(*serializer, serialize(wordsAfterAddition)).WillOnce(Return("words"));

    persistentStorage.addWordDescription(word3);

    ASSERT_EQ(persistentStorage.size(), 3);
}

TEST_F(WordsDescriptionsPersistentStorageTest, givenExistingEnglishWord_shouldReturnThisWord)
{
    expectTwoWordsDescriptionsLoad();
    WordsDescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWord = persistentStorage.getWordDescription(englishWord1);

    ASSERT_EQ(*actualWord, word1);
}

TEST_F(WordsDescriptionsPersistentStorageTest, givenNonExistingEnglishWord_shouldReturnNone)
{
    expectTwoWordsDescriptionsLoad();
    WordsDescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWord = persistentStorage.getWordDescription(nonExistingWord);

    ASSERT_EQ(actualWord, boost::none);
}

TEST_F(WordsDescriptionsPersistentStorageTest,
       givenTwoWordsDescriptions_shouldContainThoseTwoWordsDescriptions)
{
    expectTwoWordsDescriptionsLoad();
    WordsDescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_TRUE(persistentStorage.contains(englishWord1));
    ASSERT_TRUE(persistentStorage.contains(englishWord2));
    ASSERT_FALSE(persistentStorage.contains(nonExistingWord));
}