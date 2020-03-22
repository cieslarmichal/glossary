#include "DefaultWordDescriptionService.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "wordDescriptionDownloader/WordDescriptionDownloaderMock.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryMock.h"

using namespace ::testing;
using namespace wordDescriptionRepository;
using namespace wordDescriptionDownloader;

namespace
{
const EnglishWord englishWord{"englishWord"};
const WordDescription wordDescription{englishWord, {}};
}

class DefaultWordDescriptionServiceTest : public Test
{
public:
    std::unique_ptr<WordDescriptionDownloaderMock> wordDescriptionDownloaderInit =
        std::make_unique<StrictMock<WordDescriptionDownloaderMock>>();
    WordDescriptionDownloaderMock* wordDescriptionDownloader = wordDescriptionDownloaderInit.get();
    std::shared_ptr<WordDescriptionRepositoryMock> wordsDescriptionsDb =
        std::make_shared<StrictMock<WordDescriptionRepositoryMock>>();
    DefaultWordDescriptionService wordDescriptionService{std::move(wordDescriptionDownloaderInit),
                                                         wordsDescriptionsDb};
};

TEST_F(DefaultWordDescriptionServiceTest, dbContainsWordDescription_shouldReturnWordDescriptionFromDb)
{
    EXPECT_CALL(*wordsDescriptionsDb, getWordDescription(englishWord)).WillOnce(Return(wordDescription));

    const auto actualWordDescription = wordDescriptionService.getWordDescription(englishWord);

    ASSERT_EQ(*actualWordDescription, wordDescription);
}

TEST_F(
    DefaultWordDescriptionServiceTest,
    dbDoesNotContainWordDescription_shouldReturnWordDescriptionFromHttpCreatorAndSaveWordDescriptionInDatabase)
{
    EXPECT_CALL(*wordsDescriptionsDb, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, downloadWordDescription(englishWord))
        .WillOnce(Return(wordDescription));
    EXPECT_CALL(*wordsDescriptionsDb, addWordDescription(wordDescription));

    const auto actualWordDescription = wordDescriptionService.getWordDescription(englishWord);

    ASSERT_EQ(*actualWordDescription, wordDescription);
}

TEST_F(DefaultWordDescriptionServiceTest, dbAndHttpCreatorDoNotRespondWithWordDescription_shouldReturnNone)
{
    EXPECT_CALL(*wordsDescriptionsDb, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, downloadWordDescription(englishWord))
        .WillOnce(Return(boost::none));

    const auto actualWordDescription = wordDescriptionService.getWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}
