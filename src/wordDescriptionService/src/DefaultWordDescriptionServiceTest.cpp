#include "DefaultWordDescriptionService.h"

#include "gtest/gtest.h"

#include "ApiKeyLocationUpdaterMock.h"
#include "ApiKeyReaderMock.h"
#include "WordsApiConnectionCheckerMock.h"
#include "wordDescriptionDownloader/WordDescriptionDownloaderMock.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryMock.h"

#include "webConnection/exceptions/ConnectionFailed.h"
#include "wordDescriptionDownloader/exceptions/InvalidApiKey.h"
#include <boost/optional/optional_io.hpp>

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionRepository;
using namespace wordDescriptionDownloader;
using namespace wordDescriptionService;

namespace
{
const std::string apiKey{"apiKey"};
const EnglishWord englishWord{"englishWord1"};
const WordDescription wordDescriptionFromRepository{englishWord, {"def1"}, {}, {}};
const WordDescription wordDescriptionFromDownloader{englishWord, {"def2"}, {}, {}};
const WordDescription emptyWordDescription{englishWord, {}, {}, {}};
const auto apiAvailabilityStatus = WordsApiStatus::Available;
const auto invalidApiKeyAvailabilityStatus = WordsApiStatus::InvalidApiKey;
const std::string apiKeyLocation{"apiKeyLocation"};
}

class DefaultWordDescriptionServiceTest_Base : public Test
{
public:
    std::shared_ptr<WordDescriptionDownloaderMock> wordDescriptionDownloader =
        std::make_shared<StrictMock<WordDescriptionDownloaderMock>>();
    std::shared_ptr<WordDescriptionRepositoryMock> wordDescriptionRepository =
        std::make_shared<StrictMock<WordDescriptionRepositoryMock>>();
    std::unique_ptr<WordsApiConnectionCheckerMock> connectionCheckerInit =
        std::make_unique<StrictMock<WordsApiConnectionCheckerMock>>();
    WordsApiConnectionCheckerMock* connectionChecker = connectionCheckerInit.get();
    std::unique_ptr<ApiKeyReaderMock> apiKeyReaderInit = std::make_unique<StrictMock<ApiKeyReaderMock>>();
    ApiKeyReaderMock* apiKeyReader = apiKeyReaderInit.get();
    std::unique_ptr<ApiKeyLocationUpdaterMock> apiKeyLocationUpdaterInit =
        std::make_unique<StrictMock<ApiKeyLocationUpdaterMock>>();
    ApiKeyLocationUpdaterMock* apiKeyLocationUpdater = apiKeyLocationUpdaterInit.get();
};

class DefaultWordDescriptionServiceTest_WithApiKey_Base : public DefaultWordDescriptionServiceTest_Base
{
public:
    DefaultWordDescriptionServiceTest_WithApiKey_Base()
    {
        EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(apiKey));
    }
};

class DefaultWordDescriptionServiceTest_WithoutApiKey_Base : public DefaultWordDescriptionServiceTest_Base
{
public:
    DefaultWordDescriptionServiceTest_WithoutApiKey_Base()
    {
        EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(boost::none));
    }
};

class DefaultWordDescriptionServiceTest_WithApiKey : public DefaultWordDescriptionServiceTest_WithApiKey_Base
{
public:
    DefaultWordDescriptionService wordDescriptionService{
        wordDescriptionDownloader, wordDescriptionRepository, std::move(connectionCheckerInit),
        std::move(apiKeyReaderInit), std::move(apiKeyLocationUpdaterInit)};
};

TEST_F(DefaultWordDescriptionServiceTest_WithApiKey,
       repositoryContainsWordDescription_shouldReturnWordDescriptionFromRepository)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord))
        .WillOnce(Return(wordDescriptionFromRepository));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, wordDescriptionFromRepository);
}

TEST_F(
    DefaultWordDescriptionServiceTest_WithApiKey,
    repositoryDoesNotContainWordDescription_shouldReturnWordDescriptionFromDownloaderAndSaveWordDescriptionInRepository)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord, apiKey))
        .WillOnce(Return(wordDescriptionFromDownloader));
    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(wordDescriptionFromDownloader));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, wordDescriptionFromDownloader);
}

TEST_F(
    DefaultWordDescriptionServiceTest_WithApiKey,
    repositoryDoesNotReturnWordDescriptionAndDownloaderThrowsConnectionFailed_shouldReturnEmptyWordDescriptionWithEnglishWord)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord, apiKey))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));
    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(emptyWordDescription));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, emptyWordDescription);
}

TEST_F(
    DefaultWordDescriptionServiceTest_WithApiKey,
    repositoryDoesNotReturnWordDescriptionAndDownloaderThrowsInvalidApiKey_shouldReturnEmptyWordDescriptionWithEnglishWord)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord, apiKey))
        .WillOnce(Throw(wordDescriptionDownloader::exceptions::InvalidApiKey{""}));
    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(emptyWordDescription));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, emptyWordDescription);
}

TEST_F(DefaultWordDescriptionServiceTest_WithApiKey, shouldReturnDownloadedWordDescriptionFromDownloader)
{
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord, apiKey))
        .WillOnce(Return(wordDescriptionFromDownloader));

    const auto actualWordDescription = wordDescriptionService.downloadWordDescription(englishWord);

    ASSERT_EQ(*actualWordDescription, wordDescriptionFromDownloader);
}

TEST_F(DefaultWordDescriptionServiceTest_WithApiKey, shouldReturnWordsApiConnectionAvailabilityStatus)
{
    EXPECT_CALL(*connectionChecker, connectionToWordsApiAvailable(apiKey))
        .WillOnce(Return(apiAvailabilityStatus));

    const auto actualStatus = wordDescriptionService.connectionToWordsApiAvailable();

    ASSERT_EQ(actualStatus, apiAvailabilityStatus);
}

TEST_F(DefaultWordDescriptionServiceTest_WithApiKey, shouldUpdateApiKeyLocationAndReadNewApiKey)
{
    EXPECT_CALL(*apiKeyLocationUpdater, updateApiKeyLocation(apiKeyLocation));
    EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(apiKey));

    wordDescriptionService.updateApiKeyLocation(apiKeyLocation);
}

class DefaultWordDescriptionServiceTest_WithoutApiKey
    : public DefaultWordDescriptionServiceTest_WithoutApiKey_Base
{
public:
    DefaultWordDescriptionService wordDescriptionService{
        wordDescriptionDownloader, wordDescriptionRepository, std::move(connectionCheckerInit),
        std::move(apiKeyReaderInit), std::move(apiKeyLocationUpdaterInit)};
};

TEST_F(DefaultWordDescriptionServiceTest_WithoutApiKey,
       repositoryContainsWordDescription_shouldReturnWordDescriptionFromRepository)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord))
        .WillOnce(Return(wordDescriptionFromRepository));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, wordDescriptionFromRepository);
}

TEST_F(DefaultWordDescriptionServiceTest_WithoutApiKey,
       repositoryDoesNotContainWordDescription_shouldReturnEmptyDictionaryWord)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, emptyWordDescription);
}

TEST_F(DefaultWordDescriptionServiceTest_WithoutApiKey, downloadWordDescription_shouldReturnNone)
{
    const auto actualWordDescription = wordDescriptionService.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionServiceTest_WithoutApiKey, shouldReturnInvalidApiKeyAvailabilityStatus)
{
    const auto actualStatus = wordDescriptionService.connectionToWordsApiAvailable();

    ASSERT_EQ(actualStatus, invalidApiKeyAvailabilityStatus);
}

TEST_F(DefaultWordDescriptionServiceTest_WithoutApiKey, shouldUpdateApiKeyLocationAndReadNewApiKey)
{
    EXPECT_CALL(*apiKeyLocationUpdater, updateApiKeyLocation(apiKeyLocation));
    EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(apiKey));

    wordDescriptionService.updateApiKeyLocation(apiKeyLocation);
}