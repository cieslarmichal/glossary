#include "WordDescriptionServiceImpl.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "HttpWordDescriptionCreatorMock.h"
#include "wordsDescriptionsDb/WordsDescriptionsDbMock.h"

using namespace ::testing;
using namespace wordsDescriptionsDb;

namespace
{
const EnglishWord englishWord{"englishWord"};
const WordDescription wordDescription{englishWord, {}};
}

class WordDescriptionServiceImplTest : public Test
{
public:
    std::unique_ptr<HttpWordDescriptionCreatorMock> wordDescriptionCreatorInit =
        std::make_unique<StrictMock<HttpWordDescriptionCreatorMock>>();
    HttpWordDescriptionCreatorMock* wordDescriptionCreator = wordDescriptionCreatorInit.get();
    std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDbMock> wordsDescriptionsDb =
        std::make_shared<StrictMock<wordsDescriptionsDb::WordsDescriptionsDbMock>>();
    WordDescriptionServiceImpl wordDescriptionService{std::move(wordDescriptionCreatorInit),
                                                      wordsDescriptionsDb};
};

TEST_F(WordDescriptionServiceImplTest, dbContainsWordDescription_shouldReturnWordDescriptionFromDb)
{
    EXPECT_CALL(*wordsDescriptionsDb, getWordDescription(englishWord)).WillOnce(Return(wordDescription));

    const auto actualWordDescription = wordDescriptionService.getWordDescription(englishWord);

    ASSERT_EQ(*actualWordDescription, wordDescription);
}

TEST_F(
    WordDescriptionServiceImplTest,
    dbDoesNotContainWordDescription_shouldReturnWordDescriptionFromHttpCreatorAndSaveWordDescriptionInDatabase)
{
    EXPECT_CALL(*wordsDescriptionsDb, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionCreator, createWordDescription(englishWord))
        .WillOnce(Return(wordDescription));
    EXPECT_CALL(*wordsDescriptionsDb, addWordDescription(wordDescription));

    const auto actualWordDescription = wordDescriptionService.getWordDescription(englishWord);

    ASSERT_EQ(*actualWordDescription, wordDescription);
}

TEST_F(WordDescriptionServiceImplTest, dbAndHttpCreatorDoNotRespondWithWordDescription_shouldReturnNone)
{
    EXPECT_CALL(*wordsDescriptionsDb, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionCreator, createWordDescription(englishWord)).WillOnce(Return(boost::none));

    const auto actualWordDescription = wordDescriptionService.getWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}
