#include "PersistentStorage.h"

#include "FileAccessMock.h"
#include "WordsSerializerMock.h"

#include "Exceptions/FileNotFound.h"
#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const std::string filePath{"../database/words.txt"};
const std::string invalidFilePath{"invalidFilePath"};
const Word word1("xxx", {}, {});
const Word word2("yyy", {}, {});
const Words words{word1, word2};
const Word word3("yzzxc12yy", {}, {});
const Words wordsAfterAddition{word1, word2, word3};
}

class PersistentStorageTest : public Test
{
public:
    std::shared_ptr<FileAccessMock> fileAccess =
        std::make_shared<StrictMock<FileAccessMock>>();
    std::shared_ptr<WordsSerializerMock> serializer =
        std::make_shared<StrictMock<WordsSerializerMock>>();
};

TEST_F(PersistentStorageTest,
       givenPersistentStorageWithEmptyFile_shouldNotLoadAnyWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return(""));
    EXPECT_CALL(*serializer, deserialize("")).WillOnce(Return(Words{}));
    PersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWords();

    ASSERT_TRUE(actualWords.empty());
}

TEST_F(PersistentStorageTest,
       givenPersistentStorageWithFileWithWords_shouldLoadWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath))
        .WillOnce(Return("some content"));
    EXPECT_CALL(*serializer, deserialize("some content"))
        .WillOnce(Return(words));
    PersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWords();

    ASSERT_EQ(actualWords, words);
}

TEST_F(PersistentStorageTest, givenInvalidFile_shouldReturnNoWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath))
        .WillOnce(Throw(exceptions::FileNotFound{""}));
    PersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWords();

    EXPECT_TRUE(actualWords.empty());
}

TEST_F(PersistentStorageTest, givenWordAddition_shouldAddWordAndSerialize)
{
    EXPECT_CALL(*fileAccess, readContent(filePath))
        .WillOnce(Return("some content"));
    EXPECT_CALL(*serializer, deserialize("some content"))
        .WillOnce(Return(words));
    PersistentStorage persistentStorage{fileAccess, serializer};

    EXPECT_CALL(*fileAccess, write(filePath, "words"));
    EXPECT_CALL(*serializer, serialize(wordsAfterAddition))
        .WillOnce(Return("words"));
    persistentStorage.addWord(word3);
}
