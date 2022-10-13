#include "DefaultWordsApiConnectionChecker.h"

#include <boost/optional/optional_io.hpp>

#include "gtest/gtest.h"

#include "wordDescriptionDownloader/WordDescriptionDownloaderMock.h"

#include "httpClient/exceptions/ConnectionFailed.h"
#include "wordDescriptionDownloader/exceptions/InvalidApiKey.h"

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionRepository;
using namespace wordDescriptionDownloader;
using namespace wordDescriptionService;

namespace
{
const std::string apiKey{"topSecretApiKey"};
const std::string englishWord{"fish"};
const WordDescription wordDescription{englishWord, {}, {}, {}};
const auto availableStatus = WordsApiStatus::Available;
const auto unavailableStatus = WordsApiStatus::Unavailable;
const auto invalidApiKeyStatus = WordsApiStatus::InvalidApiKey;
}

class DefaultWordsApiConnectionCheckerTest : public Test
{
public:
    std::shared_ptr<WordDescriptionDownloaderMock> wordDescriptionDownloader =
        std::make_shared<StrictMock<WordDescriptionDownloaderMock>>();

    DefaultWordsApiConnectionChecker connectionChecker{wordDescriptionDownloader};
};

TEST_F(DefaultWordsApiConnectionCheckerTest,
       wordDescriptionDownloaderThrowsConnectionFailed_shouldReturnConnectionUnavailableStatus)
{
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord, apiKey))
        .WillOnce(Throw(common::httpClient::exceptions::ConnectionFailed{""}));

    const auto actualStatus = connectionChecker.connectionToWordsApiAvailable(apiKey);

    ASSERT_EQ(actualStatus, unavailableStatus);
}

TEST_F(DefaultWordsApiConnectionCheckerTest,
       wordDescriptionDownloaderThrowsInvalidApiKey_shouldReturnInvalidApiKeyStatus)
{
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord, apiKey))
        .WillOnce(Throw(wordDescriptionDownloader::exceptions::InvalidApiKey{""}));

    const auto actualStatus = connectionChecker.connectionToWordsApiAvailable(apiKey);

    ASSERT_EQ(actualStatus, invalidApiKeyStatus);
}

TEST_F(DefaultWordsApiConnectionCheckerTest,
       wordDescriptionDownloaderReturnsWordDescription_shouldReturnConnectionAvailableStatus)
{
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord, apiKey))
        .WillOnce(Return(wordDescription));

    const auto actualStatus = connectionChecker.connectionToWordsApiAvailable(apiKey);

    ASSERT_EQ(actualStatus, availableStatus);
}