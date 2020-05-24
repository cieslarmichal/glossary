#include "DefaultWordDescriptionRetrieverService.h"

#include "gtest/gtest.h"

#include "wordDescriptionDownloader/WordDescriptionDownloaderMock.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryMock.h"
#include "webConnection/exceptions/ConnectionFailed.h"
#include "wordDescriptionDownloader/exceptions/InvalidApiKey.h"
#include "WordsApiConnectionCheckerMock.h"

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionRepository;
using namespace wordDescriptionDownloader;
using namespace wordDescriptionService;

namespace
{
const EnglishWord englishWord{"englishWord1"};
const WordDescription wordDescriptionFromRepository{englishWord, {"def1"}, {}, {}};
const WordDescription wordDescriptionFromDownloader{englishWord, {"def2"}, {}, {}};
const WordDescription emptyWordDescription{englishWord, {}, {}, {}};
const auto apiAvailabilityStatus = WordsApiStatus::Available;
}

class DefaultWordDescriptionRetrieverServiceTest : public Test
{
public:
    std::shared_ptr<WordDescriptionDownloaderMock> wordDescriptionDownloader =
        std::make_shared<StrictMock<WordDescriptionDownloaderMock>>();
    std::shared_ptr<WordDescriptionRepositoryMock> wordDescriptionRepository =
        std::make_shared<StrictMock<WordDescriptionRepositoryMock>>();
    std::unique_ptr<WordsApiConnectionCheckerMock> connectionCheckerInit =
        std::make_unique<StrictMock<WordsApiConnectionCheckerMock>>();
    WordsApiConnectionCheckerMock* connectionChecker = connectionCheckerInit.get();
    DefaultWordDescriptionRetrieverService wordDescriptionService{wordDescriptionDownloader,
                                                                  wordDescriptionRepository, std::move(connectionCheckerInit)};
};

TEST_F(DefaultWordDescriptionRetrieverServiceTest,
       repositoryContainsWordDescription_shouldReturnWordDescriptionFromRepository)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord))
        .WillOnce(Return(wordDescriptionFromRepository));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, wordDescriptionFromRepository);
}

TEST_F(
    DefaultWordDescriptionRetrieverServiceTest,
    repositoryDoesNotContainWordDescription_shouldReturnWordDescriptionFromDownloaderAndSaveWordDescriptionInRepository)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord))
        .WillOnce(Return(wordDescriptionFromDownloader));
    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(wordDescriptionFromDownloader));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, wordDescriptionFromDownloader);
}

TEST_F(DefaultWordDescriptionRetrieverServiceTest,
       repositoryDoesNotReturnWordDescriptionAndDownloaderThrowsConnectionFailed_shouldReturnEmptyWordDescriptionWithEnglishWord)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));
    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(emptyWordDescription));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, emptyWordDescription);
}

TEST_F(DefaultWordDescriptionRetrieverServiceTest,
       repositoryDoesNotReturnWordDescriptionAndDownloaderThrowsInvalidApiKey_shouldReturnEmptyWordDescriptionWithEnglishWord)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord))
        .WillOnce(Throw(wordDescriptionDownloader::exceptions::InvalidApiKey{""}));
    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(emptyWordDescription));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, emptyWordDescription);
}

TEST_F(DefaultWordDescriptionRetrieverServiceTest,
       shouldReturnWordsApiConnectionAvailabilityStatus)
{
    EXPECT_CALL(*connectionChecker, connectionToWordsApiAvailable()).WillOnce(Return(apiAvailabilityStatus));

    const auto actualStatus = wordDescriptionService.connectionToWordsApiAvailable();

    ASSERT_EQ(actualStatus, apiAvailabilityStatus);
}
