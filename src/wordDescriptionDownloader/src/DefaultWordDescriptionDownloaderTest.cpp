#include "DefaultWordDescriptionDownloader.h"

#include "gtest/gtest.h"

#include "ApiResponseFetcherMock.h"
#include "WordDescriptionResponseDeserializerMock.h"

#include "exceptions/InvalidApiKey.h"
#include "webConnection/exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionDownloader;
using namespace wordDescriptionRepository;

namespace
{
const EnglishWord englishWord{"englishWord"};
const webConnection::Response okResponse{200, "content"};
const webConnection::Response errorResponse{400, ""};
const Definitions definitions{"definition1", "definition2"};
const Examples examples{"example1", "example2"};
const Synonyms synonyms{"synonym1"};
const WordDescription wordDescription{englishWord, definitions, examples, synonyms};
}

class DefaultWordDescriptionDownloaderTest : public Test
{
public:
    void expectDownloadedDefinitions() const
    {
        EXPECT_CALL(*apiResponseFetcher, tryGetWordDefinitionsResponse(englishWord))
            .WillOnce(Return(okResponse));
        EXPECT_CALL(*responseDeserializer, deserializeDefinitions(okResponse.content))
            .WillOnce(Return(definitions));
    }

    void expectDownloadedExamples() const
    {
        EXPECT_CALL(*apiResponseFetcher, tryGetWordExamplesResponse(englishWord))
            .WillOnce(Return(okResponse));
        EXPECT_CALL(*responseDeserializer, deserializeExamples(okResponse.content))
            .WillOnce(Return(examples));
    }

    void expectDownloadedSynonyms() const
    {
        EXPECT_CALL(*apiResponseFetcher, tryGetWordSynonymsResponse(englishWord))
            .WillOnce(Return(okResponse));
        EXPECT_CALL(*responseDeserializer, deserializeSynonyms(okResponse.content))
            .WillOnce(Return(synonyms));
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

TEST_F(DefaultWordDescriptionDownloaderTest, getDefinitions_throwInvalidConnection_shouldReturnNone)
{
    EXPECT_CALL(*apiResponseFetcher, tryGetWordDefinitionsResponse(englishWord))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getDefinitions_throwInvalidApiKey_shouldReturnNone)
{
    EXPECT_CALL(*apiResponseFetcher, tryGetWordDefinitionsResponse(englishWord))
        .WillOnce(Throw(exceptions::InvalidApiKey{""}));

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getDefinitions_ReturnsNotOkResponseCode_shouldReturnNone)
{
    EXPECT_CALL(*apiResponseFetcher, tryGetWordDefinitionsResponse(englishWord))
        .WillOnce(Return(errorResponse));

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getExamples_throwInvalidConnection_shouldReturnNone)
{
    expectDownloadedDefinitions();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordExamplesResponse(englishWord))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getExamples_throwInvalidApiKey_shouldReturnNone)
{
    expectDownloadedDefinitions();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordExamplesResponse(englishWord))
        .WillOnce(Throw(exceptions::InvalidApiKey{""}));

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getExamples_ReturnsNotOkResponseCode_shouldReturnNone)
{
    expectDownloadedDefinitions();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordExamplesResponse(englishWord)).WillOnce(Return(errorResponse));

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getSynonyms_throwInvalidConnection_shouldReturnNone)
{
    expectDownloadedDefinitions();
    expectDownloadedExamples();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordSynonymsResponse(englishWord))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getSynonyms_throwInvalidApiKey_shouldReturnNone)
{
    expectDownloadedDefinitions();
    expectDownloadedExamples();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordSynonymsResponse(englishWord))
        .WillOnce(Throw(exceptions::InvalidApiKey{""}));

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest, getSynonyms_ReturnsNotOkResponseCode_shouldReturnNone)
{
    expectDownloadedDefinitions();
    expectDownloadedExamples();
    EXPECT_CALL(*apiResponseFetcher, tryGetWordSynonymsResponse(englishWord)).WillOnce(Return(errorResponse));

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest,
       fetchedDefinitionsExamplesAndSynonyms_shouldReturnWordDescription)
{
    expectDownloadedDefinitions();
    expectDownloadedExamples();
    expectDownloadedSynonyms();

    const auto actualWordDescription = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(*actualWordDescription, wordDescription);
}
