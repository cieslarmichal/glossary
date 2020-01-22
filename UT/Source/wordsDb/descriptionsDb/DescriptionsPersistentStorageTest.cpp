#include "FileAccessMock.h"
#include "wordsDb/descriptionsDb/DescriptionsSerializerMock.h"

#include "exceptions/FileNotFound.h"
#include "gtest/gtest.h"
#include "wordsDb/descriptionsDb/DescriptionsPersistentStorage.h"

using namespace ::testing;
using namespace wordsDb::descriptionsDb;

namespace
{
const std::string filePath{"../database/words.txt"};
const std::string invalidFilePath{"invalidFilePath"};
const WordDescription word1("xxx", {}, {});
const WordDescription word2("yyy", {}, {});
const Words words{word1, word2};
const WordDescription word3("yzzxc12yy", {}, {});
const Words wordsAfterAddition{word1, word2, word3};
}

class DescriptionsPersistentStorageTest : public Test
{
public:
    std::shared_ptr<FileAccessMock> fileAccess =
        std::make_shared<StrictMock<FileAccessMock>>();
    std::shared_ptr<DescriptionsSerializerMock> serializer =
        std::make_shared<StrictMock<DescriptionsSerializerMock>>();
};

TEST_F(DescriptionsPersistentStorageTest,
       givenPersistentStorageWithEmptyFile_shouldNotLoadAnyWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return(""));
    EXPECT_CALL(*serializer, deserialize("")).WillOnce(Return(Words{}));
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWords();

    ASSERT_TRUE(actualWords.empty());
}

TEST_F(DescriptionsPersistentStorageTest,
       givenPersistentStorageWithFileWithWords_shouldLoadWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath))
        .WillOnce(Return("some content"));
    EXPECT_CALL(*serializer, deserialize("some content"))
        .WillOnce(Return(words));
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWords();

    ASSERT_EQ(actualWords, words);
}

TEST_F(DescriptionsPersistentStorageTest, givenInvalidFile_shouldReturnNoWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath))
        .WillOnce(Throw(exceptions::FileNotFound{""}));
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWords = persistentStorage.getWords();

    EXPECT_TRUE(actualWords.empty());
}

TEST_F(DescriptionsPersistentStorageTest, givenWordAddition_shouldAddWordAndSerialize)
{
    EXPECT_CALL(*fileAccess, readContent(filePath))
        .WillOnce(Return("some content"));
    EXPECT_CALL(*serializer, deserialize("some content"))
        .WillOnce(Return(words));
    DescriptionsPersistentStorage persistentStorage{fileAccess, serializer};

    EXPECT_CALL(*fileAccess, write(filePath, "words"));
    EXPECT_CALL(*serializer, serialize(wordsAfterAddition))
        .WillOnce(Return("words"));
    persistentStorage.addWord(word3);
}
