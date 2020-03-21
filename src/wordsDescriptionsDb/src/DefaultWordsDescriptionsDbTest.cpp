#include "DefaultWordsDescriptionsDb.h"

#include "gtest/gtest.h"

#include "WordsDescriptionsStorageMock.h"

using namespace ::testing;
using namespace wordsDescriptionsDb;

namespace
{
const EnglishWord englishWord{"englishWord"};
const WordDescription wordDescription{englishWord, {}};
const WordsDescriptions wordsDescriptions{wordDescription};
}

class DefaultWordsDescriptionsDbTest : public Test
{
public:
    std::unique_ptr<WordsDescriptionsStorageMock> storageInit =
        std::make_unique<StrictMock<WordsDescriptionsStorageMock>>();
    WordsDescriptionsStorageMock* storage = storageInit.get();
    DefaultWordsDescriptionsDb database{std::move(storageInit)};
};

TEST_F(DefaultWordsDescriptionsDbTest, givenWordDescritpionAddition_shouldAddWordDescriptionToStorage)
{
    EXPECT_CALL(*storage, addWordDescription(wordDescription));

    database.addWordDescription(wordDescription);
}

TEST_F(DefaultWordsDescriptionsDbTest, givenEnglishWordDescriptionNotExistingInStorage_shouldReturnNone)
{
    EXPECT_CALL(*storage, getWordDescription(englishWord)).WillOnce(Return(boost::none));

    const auto actualWord = database.getWordDescription(englishWord);

    ASSERT_EQ(actualWord, boost::none);
}

TEST_F(DefaultWordsDescriptionsDbTest,
       givenEnglishWordDescriptionExistingInStorage_shouldReturnWordDescription)
{
    EXPECT_CALL(*storage, getWordDescription(englishWord)).WillOnce(Return(wordDescription));

    const auto actualWord = database.getWordDescription(englishWord);

    ASSERT_EQ(actualWord, wordDescription);
}

TEST_F(DefaultWordsDescriptionsDbTest, containsWordsDescriptions_shouldReturnWordsDescriptions)
{
    EXPECT_CALL(*storage, getWordsDescriptions()).WillOnce(Return(wordsDescriptions));

    const auto actualWords = database.getWordsDescriptions();

    ASSERT_EQ(actualWords, wordsDescriptions);
}

TEST_F(DefaultWordsDescriptionsDbTest, givenEnglishWordExistingInStorage_shouldContainThisWordsDescription)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(true));

    ASSERT_TRUE(database.contains(englishWord));
}

TEST_F(DefaultWordsDescriptionsDbTest,
       givenEnglishWordNotExistingInStorage_shouldNotContainThisWordDescription)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(false));

    ASSERT_FALSE(database.contains(englishWord));
}
