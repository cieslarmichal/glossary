#include "PersistentStorage.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "FileAccessMock.h"
#include "WordsSerializerMock.h"

using namespace ::testing;

namespace
{
const std::string fileDirectory{"../database"};
const std::string fileName{"/words.txt"};
const std::string filePath{fileDirectory + fileName};
const Word word1("xxx", {}, {});
const Word word2("yyy", {}, {});
const Words words{word1, word2};
}

class PersistentStorageTest : public Test
{
public:
    std::shared_ptr<FileAccessMock> fileAccess = std::make_shared<NiceMock<FileAccessMock>>();
    std::shared_ptr<WordsSerializerMock> serializer = std::make_shared<NiceMock<WordsSerializerMock>>();
};

TEST_F(PersistentStorageTest, givenPersistentStorageWithEmptyFile_shouldNotLoadAnyWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return(""));
    EXPECT_CALL(*serializer, deserialize("")).WillOnce(Return(Words{}));
    PersistentStorage persistentStorage{fileAccess, serializer};

    auto actualWords = persistentStorage.getWords();

    ASSERT_TRUE(actualWords.empty());
}

TEST_F(PersistentStorageTest, givenPersistentStorageWithFileWithWords_shouldNotLoadAnyWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return("some content"));
    EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(words));
    PersistentStorage persistentStorage{fileAccess, serializer};

    auto actualWords = persistentStorage.getWords();

    ASSERT_EQ(actualWords, words);
}