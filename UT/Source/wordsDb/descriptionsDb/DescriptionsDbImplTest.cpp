#include "wordsDb/descriptionsDb/DescriptionsStorageMock.h"

#include "gtest/gtest.h"
#include "wordsDb/descriptionsDb/DescriptionsDbImpl.h"

using namespace ::testing;
using namespace wordsDb::descriptionsDb;

namespace
{
const EnglishWord englishWord{"englishWord"};
const WordDescription word(englishWord, "polishTranslation", {});
}

class WordsDatabaseTest : public Test
{
public:
    std::unique_ptr<DescriptionsStorageMock> storageInit =
        std::make_unique<StrictMock<DescriptionsStorageMock>>();
    DescriptionsStorageMock* storage = storageInit.get();
    DescriptionsDbImpl database{std::move(storageInit)};
};

TEST_F(WordsDatabaseTest, givenWordAddition_shouldAddWordToStorage)
{
    EXPECT_CALL(*storage, addWord(word));

    database.addWord(word);
}

TEST_F(WordsDatabaseTest, givenEnglishWordNotExistingInStorage_shouldReturnNone)
{
    EXPECT_CALL(*storage, getWord(englishWord)).WillOnce(Return(boost::none));

    const auto actualWord = database.getWord(englishWord);

    ASSERT_FALSE(actualWord);
}

TEST_F(WordsDatabaseTest, givenEnglishWordExistingInStorage_shouldReturnWord)
{
    EXPECT_CALL(*storage, getWord(englishWord)).WillOnce(Return(word));

    const auto actualWord = database.getWord(englishWord);

    ASSERT_EQ(actualWord, word);
}

TEST_F(WordsDatabaseTest,
       givenEnglishWordExistingInStorage_shouldContainThisWord)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(true));

    const auto contains = database.contains(englishWord);

    ASSERT_TRUE(contains);
}

TEST_F(WordsDatabaseTest,
       givenEnglishWordNotExistingInStorage_shouldNotContainThisWord)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(false));

    const auto contains = database.contains(englishWord);

    ASSERT_FALSE(contains);
}
