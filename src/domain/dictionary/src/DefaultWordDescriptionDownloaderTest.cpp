#include "DefaultWordDescriptionDownloader.h"

#include "gtest/gtest.h"

#include "ApiResponseFetcherMock.h"
#include "WordDescriptionResponseDeserializerMock.h"

#include "../include/exceptions/InvalidApiKey.h"
#include "httpClient/exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace glossary;
using namespace dictionary;

namespace
{
const std::string apiKey{"topSecretKey"};
const std::string englishWord{"englishWord"};
const common::httpClient::HttpResponse okResponse{200, "content"};
const common::httpClient::HttpResponse errorResponse{400, ""};
const std::vector<std::string> definitions{"definition1", "definition2"};
const std::vector<std::string> examples{"example1", "example2"};
const std::vector<std::string> synonyms{"synonym1"};
const WordDescription wordDescription{englishWord, definitions, examples, synonyms};
const std::vector<std::string> emptyDefinitions{};
const std::vector<std::string> emptyExamples{};
const std::vector<std::string> emptySynonyms{};
}

class DefaultWordDescriptionDownloaderTest : public Test
{
public:
    void expectDownloadedDefinitions() const
    {
        EXPECT_CALL(*apiResponseFetcher, tryGetWordDefinitionsResponse(englishWord, apiKey))
            .WillOnce(Return(okResponse));
        EXPECT_CALL(*responseDeserializer, deserializeDefinitions(okResponse.data))
            .WillOnce(Return(definitions));
    }

    void expectDownloadedExamples() const
    {
        EXPECT_CALL(*apiResponseFetcher, tryGetWordExamplesResponse(englishWord, apiKey))
            .WillOnce(Return(okResponse));
        EXPECT_CALL(*responseDeserializer, deserializeExamples(okResponse.data)).WillOnce(Return(examples));
    }

    void expectDownloadedSynonyms() const
    {
        EXPECT_CALL(*apiResponseFetcher, tryGetWordSynonymsResponse(englishWord, apiKey))
            .WillOnce(Return(okResponse));
        EXPECT_CALL(*responseDeserializer, deserializeSynonyms(okResponse.data)).WillOnce(Return(synonyms));
    }

    void expectDownloadedEmptyDefinitions() const
    {
        EXPECT_CALL(*apiResponseFetcher, tryGetWordDefinitionsResponse(englishWord, apiKey))
            .WillOnce(Return(okResponse));
        EXPECT_CALL(*responseDeserializer, deserializeDefinitions(okResponse.data))
            .WillOnce(Return(emptyDefinitions));
    }

    void expectDownloadedEmptyExamples() const
    {
        EXPECT_CALL(*apiResponseFetcher, tryGetWordExamplesResponse(englishWord, apiKey))
            .WillOnce(Return(okResponse));
        EXPECT_CALL(*responseDeserializer, deserializeExamples(okResponse.data))
            .WillOnce(Return(emptyExamples));
    }

    void expectDownloadedEmptySynonyms() const
    {
        EXPECT_CALL(*apiResponseFetcher, tryGetWordSynonymsResponse(englishWord, apiKey))
            .WillOnce(Return(okResponse));
        EXPECT_CALL(*responseDeserializer, deserializeSynonyms(okResponse.data))
            .WillOnce(Return(emptySynonyms));
    }

    std::unique_ptr<ApiResponseFetcherMock> apiResponseFetcherInit =
        std::make_unique<StrictMock<ApiResponseFetcherMock>>();
    ApiResponseFetcherMock* apiResponseFetcher = apiResponseFetcherInit.get();
    std::unique_ptr<WordDescriptionResponseDeserializerMock> responseDeserializerInit =
        std::make_unique<StrictMock<WordDescriptionResponseDeserializerMock>>();
    WordDescriptionResponseDeserializerMock* responseDeserializer = responseDeserializerInit.get();
    DefaultWordDescriptionDownloader downloader{std::move(apiResponseFetcherInit),
                                                std::move(responseDeserializerInit)};
};

TEST_F(DefaultWordDescriptionDownloaderTest, getDefinitions_throwConnectionFailed_shouldThrowConnectionFailed)
{
    EXPECT_CALL(*apiResponseFetcher, tryGetWordDefinitionsResponse(englishWord, apiKey))
        .WillOnce(Throw(common::httpClient::exceptions::ConnectionFailed{""}));

    ASSERT_THROW(downloader.tryDownloadWordDescription(englishWord, apiKey),
                 common::httpClient::exceptions::ConnectionFailed);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getDefinitions_throwInvalidApiKey_shouldThrowInvalidApiKey)
{
    EXPECT_CALL(*apiResponseFetcher, tryGetWordDefinitionsResponse(englishWord, apiKey))
        .WillOnce(Throw(exceptions::InvalidApiKey{""}));

    ASSERT_THROW(downloader.tryDownloadWordDescription(englishWord, apiKey), exceptions::InvalidApiKey);
}

TEST_F(DefaultWordDescriptionDownloaderTest,
       getDefinitions_ReturnsNotOkResponseCode_shouldReturnEmptyWordDescription)
{
    EXPECT_CALL(*apiResponseFetcher, tryGetWordDefinitionsResponse(englishWord, apiKey))
        .WillOnce(Return(errorResponse));
    expectDownloadedEmptyExamples();
    expectDownloadedEmptySynonyms();

    const auto actualWordDescription = downloader.tryDownloadWordDescription(englishWord, apiKey);

    ASSERT_TRUE(actualWordDescription.empty());
}

TEST_F(DefaultWordDescriptionDownloaderTest, getExamples_throwConnectionFailed_shouldThrowConnectionFailed)
{
    expectDownloadedDefinitions();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordExamplesResponse(englishWord, apiKey))
        .WillOnce(Throw(common::httpClient::exceptions::ConnectionFailed{""}));

    ASSERT_THROW(downloader.tryDownloadWordDescription(englishWord, apiKey),
                 common::httpClient::exceptions::ConnectionFailed);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getExamples_throwInvalidApiKey_shouldThrowInvalidApiKey)
{
    expectDownloadedDefinitions();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordExamplesResponse(englishWord, apiKey))
        .WillOnce(Throw(exceptions::InvalidApiKey{""}));

    ASSERT_THROW(downloader.tryDownloadWordDescription(englishWord, apiKey), exceptions::InvalidApiKey);
}

TEST_F(DefaultWordDescriptionDownloaderTest,
       getExamples_ReturnsNotOkResponseCode_shouldReturnEmptyWordDescription)
{
    expectDownloadedEmptyDefinitions();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordExamplesResponse(englishWord, apiKey))
        .WillOnce(Return(errorResponse));
    expectDownloadedEmptySynonyms();

    const auto actualWordDescription = downloader.tryDownloadWordDescription(englishWord, apiKey);

    ASSERT_TRUE(actualWordDescription.empty());
}

TEST_F(DefaultWordDescriptionDownloaderTest, getSynonyms_throwConnectionFailed_shouldThrowConnectionFailed)
{
    expectDownloadedDefinitions();
    expectDownloadedExamples();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordSynonymsResponse(englishWord, apiKey))
        .WillOnce(Throw(common::httpClient::exceptions::ConnectionFailed{""}));

    ASSERT_THROW(downloader.tryDownloadWordDescription(englishWord, apiKey),
                 common::httpClient::exceptions::ConnectionFailed);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getSynonyms_throwInvalidApiKey_shouldReturnThrowInvalidApiKey)
{
    expectDownloadedDefinitions();
    expectDownloadedExamples();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordSynonymsResponse(englishWord, apiKey))
        .WillOnce(Throw(exceptions::InvalidApiKey{""}));

    ASSERT_THROW(downloader.tryDownloadWordDescription(englishWord, apiKey), exceptions::InvalidApiKey);
}

TEST_F(DefaultWordDescriptionDownloaderTest,
       getSynonyms_ReturnsNotOkResponseCode_shouldReturnEmptyWordDescription)
{
    expectDownloadedEmptyDefinitions();
    expectDownloadedEmptyExamples();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordSynonymsResponse(englishWord, apiKey))
        .WillOnce(Return(errorResponse));

    const auto actualWordDescription = downloader.tryDownloadWordDescription(englishWord, apiKey);

    ASSERT_TRUE(actualWordDescription.empty());
}

TEST_F(DefaultWordDescriptionDownloaderTest,
       fetchedDefinitionsExamplesAndSynonyms_shouldReturnWordDescription)
{
    expectDownloadedDefinitions();
    expectDownloadedExamples();
    expectDownloadedSynonyms();

    const auto actualWordDescription = downloader.tryDownloadWordDescription(englishWord, apiKey);

    ASSERT_EQ(actualWordDescription, wordDescription);
}
