#include "WordsDatabase.h"

#include "gtest/gtest.h"
#include "StorageMock.h"

using namespace ::testing;

namespace
{
EnglishWord englishWord{"englishWord"};
Word word(englishWord, "polishTranslation", {});
}

class WordsDatabaseTest : public Test
{
public:
    std::unique_ptr<StorageMock> storageInit = std::make_unique<StrictMock<StorageMock>>();
    StorageMock * storage = storageInit.get();
    WordsDatabase database{std::move(storageInit)};
};

TEST_F(WordsDatabaseTest, givenWord_shouldAddWordToStorage)
{
    EXPECT_CALL(*storage, addWord(word));

    database.addWord(word);
}

TEST_F(WordsDatabaseTest, givenEnglishWordNotExistingInStorage_shouldReturnNone)
{
    EXPECT_CALL(*storage, getWord(englishWord)).WillOnce(Return(boost::none));

    const auto actualWord = database.getWord(englishWord);

    ASSERT_EQ(actualWord, boost::none);
}

TEST_F(WordsDatabaseTest, givenEnglishWordExistingInStorage_shouldReturnWord)
{
    EXPECT_CALL(*storage, getWord(englishWord)).WillOnce(Return(word));

    const auto actualWord = database.getWord(englishWord);

    ASSERT_EQ(actualWord, word);
}
