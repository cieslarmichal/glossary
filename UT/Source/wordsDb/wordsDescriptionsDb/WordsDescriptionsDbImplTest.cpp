#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsDbImpl.h"

#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsStorageMock.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::wordsDescriptionsDb;

namespace
{
const EnglishWord englishWord{"englishWord"};
const WordDescription word(englishWord, "polishWord", {});
const WordsDescriptions words{word};
}

class WordsDescriptionsDbImplTest : public Test
{
public:
    std::unique_ptr<WordsDescriptionsStorageMock> storageInit =
        std::make_unique<StrictMock<WordsDescriptionsStorageMock>>();
    WordsDescriptionsStorageMock* storage = storageInit.get();
    WordsDescriptionsDbImpl database{std::move(storageInit)};
};

TEST_F(WordsDescriptionsDbImplTest, givenWordAddition_shouldAddWordToStorage)
{
    EXPECT_CALL(*storage, addWordDescription(word));

    database.addWordDescription(word);
}

TEST_F(WordsDescriptionsDbImplTest,
       givenEnglishWordNotExistingInStorage_shouldReturnNone)
{
    EXPECT_CALL(*storage, getWordDescription(englishWord))
        .WillOnce(Return(boost::none));

    const auto actualWord = database.getWordDescription(englishWord);

    ASSERT_EQ(actualWord, boost::none);
}

TEST_F(WordsDescriptionsDbImplTest,
       givenEnglishWordExistingInStorage_shouldReturnWord)
{
    EXPECT_CALL(*storage, getWordDescription(englishWord))
        .WillOnce(Return(word));

    const auto actualWord = database.getWordDescription(englishWord);

    ASSERT_EQ(actualWord, word);
}

TEST_F(WordsDescriptionsDbImplTest, containsWords_shouldReturnWords)
{
    EXPECT_CALL(*storage, getWordsDescriptions()).WillOnce(Return(words));

    const auto actualWords = database.getWordsDescriptions();

    ASSERT_EQ(actualWords, words);
}

TEST_F(WordsDescriptionsDbImplTest,
       givenEnglishWordExistingInStorage_shouldContainThisWord)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(true));

    ASSERT_TRUE(database.contains(englishWord));
}

TEST_F(WordsDescriptionsDbImplTest,
       givenEnglishWordNotExistingInStorage_shouldNotContainThisWord)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(false));

    ASSERT_FALSE(database.contains(englishWord));
}
