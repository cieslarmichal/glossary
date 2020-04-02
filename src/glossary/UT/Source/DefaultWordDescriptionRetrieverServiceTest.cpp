#include "DefaultWordDescriptionRetrieverService.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "wordDescriptionDownloader/WordDescriptionDownloaderMock.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryMock.h"

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionRepository;
using namespace wordDescriptionDownloader;

namespace
{
const EnglishWord englishWord{"englishWord"};
const WordDescription wordDescription{englishWord, {}};
}

class DefaultWordDescriptionRetrieverServiceTest : public Test
{
public:
    std::unique_ptr<WordDescriptionDownloaderMock> wordDescriptionDownloaderInit =
        std::make_unique<StrictMock<WordDescriptionDownloaderMock>>();
    WordDescriptionDownloaderMock* wordDescriptionDownloader = wordDescriptionDownloaderInit.get();
    std::shared_ptr<WordDescriptionRepositoryMock> wordDescriptionRepository =
        std::make_shared<StrictMock<WordDescriptionRepositoryMock>>();
    DefaultWordDescriptionRetrieverService wordDescriptionService{std::move(wordDescriptionDownloaderInit),
                                                                  wordDescriptionRepository};
};

TEST_F(DefaultWordDescriptionRetrieverServiceTest,
       dbContainsWordDescription_shouldReturnWordDescriptionFromDb)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord))
        .WillOnce(Return(wordDescription));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(*actualWordDescription, wordDescription);
}

TEST_F(
    DefaultWordDescriptionRetrieverServiceTest,
    dbDoesNotContainWordDescription_shouldReturnWordDescriptionFromHttpCreatorAndSaveWordDescriptionInDatabase)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, downloadWordDescription(englishWord))
        .WillOnce(Return(wordDescription));
    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(wordDescription));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(*actualWordDescription, wordDescription);
}

TEST_F(DefaultWordDescriptionRetrieverServiceTest,
       dbAndHttpCreatorDoNotRespondWithWordDescription_shouldReturnNone)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, downloadWordDescription(englishWord))
        .WillOnce(Return(boost::none));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}
