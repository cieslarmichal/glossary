#include "wordsDb/descriptionsDb/DescriptionsDbImpl.h"

#include "wordsDb/descriptionsDb/DescriptionsStorageMock.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::descriptionsDb;

namespace
{
const EnglishWord englishWord{"englishWord"};
const WordDescription word(englishWord, "polishWord", {});
const WordsDescriptions words{word};
}

class DescriptionsDbImplTest : public Test
{
public:
    std::unique_ptr<DescriptionsStorageMock> storageInit =
        std::make_unique<StrictMock<DescriptionsStorageMock>>();
    DescriptionsStorageMock* storage = storageInit.get();
    DescriptionsDbImpl database{std::move(storageInit)};
};

TEST_F(DescriptionsDbImplTest, givenWordAddition_shouldAddWordToStorage)
{
    EXPECT_CALL(*storage, addWordDescription(word));

    database.addWordDescription(word);
}

TEST_F(DescriptionsDbImplTest,
       givenEnglishWordNotExistingInStorage_shouldReturnNone)
{
    EXPECT_CALL(*storage, getWordDescription(englishWord))
        .WillOnce(Return(boost::none));

    const auto actualWord = database.getWordDescription(englishWord);

    ASSERT_EQ(actualWord, boost::none);
}

TEST_F(DescriptionsDbImplTest,
       givenEnglishWordExistingInStorage_shouldReturnWord)
{
    EXPECT_CALL(*storage, getWordDescription(englishWord))
        .WillOnce(Return(word));

    const auto actualWord = database.getWordDescription(englishWord);

    ASSERT_EQ(actualWord, word);
}

TEST_F(DescriptionsDbImplTest, containsWords_shouldReturnWords)
{
    EXPECT_CALL(*storage, getWordsDescriptions()).WillOnce(Return(words));

    const auto actualWords = database.getWordsDescriptions();

    ASSERT_EQ(actualWords, words);
}

TEST_F(DescriptionsDbImplTest,
       givenEnglishWordExistingInStorage_shouldContainThisWord)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(true));

    ASSERT_TRUE(database.contains(englishWord));
}

TEST_F(DescriptionsDbImplTest,
       givenEnglishWordNotExistingInStorage_shouldNotContainThisWord)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(false));

    ASSERT_FALSE(database.contains(englishWord));
}
