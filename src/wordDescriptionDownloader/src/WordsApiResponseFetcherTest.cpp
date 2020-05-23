#include "WordsApiResponseFetcher.h"

#include "gtest/gtest.h"

#include "ApiKeyReaderMock.h"
#include "webConnection/HttpHandlerMock.h"

#include "exceptions/InvalidApiKey.h"

using namespace glossary::wordDescriptionDownloader;
using namespace ::testing;

namespace
{
const std::string englishWord{"herbal"};
const std::string apiKey{"topSecretKey"};
const std::vector<std::string> headers{"x-rapidapi-host: wordsapiv1.p.rapidapi.com",
                                       "x-rapidapi-key: " + apiKey};
const std::string wordsApiDefinitionsUrl{"https://wordsapiv1.p.rapidapi.com/words/herbal/definitions"};
const std::string wordsApiExamplesUrl{"https://wordsapiv1.p.rapidapi.com/words/herbal/examples"};
const std::string wordsApiSynonymsUrl{"https://wordsapiv1.p.rapidapi.com/words/herbal/synonyms"};
const webConnection::Response response{200, "content"};
}

class WordsApiResponseFetcherTest_Base : public Test
{
public:
    std::shared_ptr<webConnection::HttpHandlerMock> httpHandler =
        std::make_shared<StrictMock<webConnection::HttpHandlerMock>>();
    std::unique_ptr<ApiKeyReaderMock> apiKeyReaderInit = std::make_unique<StrictMock<ApiKeyReaderMock>>();
    ApiKeyReaderMock* apiKeyReader = apiKeyReaderInit.get();
};

class WordsApiResponseFetcherTest_WithApiKey_Base : public WordsApiResponseFetcherTest_Base
{
public:
    WordsApiResponseFetcherTest_WithApiKey_Base()
    {
        EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(apiKey));
    }
};

class WordsApiResponseFetcherTest_WithoutApiKey_Base : public WordsApiResponseFetcherTest_Base
{
public:
    WordsApiResponseFetcherTest_WithoutApiKey_Base()
    {
        EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(boost::none));
    }
};

class WordsApiResponseFetcherTest_WithApiKey : public WordsApiResponseFetcherTest_WithApiKey_Base
{
public:
    WordsApiResponseFetcher wordsApiResponseFetcher{httpHandler, std::move(apiKeyReaderInit)};
};

TEST_F(WordsApiResponseFetcherTest_WithApiKey, getDefinitions_shouldInvokeHttpResponseWithDefinitionsUrl)
{
    EXPECT_CALL(*httpHandler, get(wordsApiDefinitionsUrl, headers)).WillOnce(Return(response));

    const auto actualResponse = wordsApiResponseFetcher.tryGetWordDefinitionsResponse(englishWord);

    ASSERT_EQ(actualResponse, response);
}

TEST_F(WordsApiResponseFetcherTest_WithApiKey, getExamples_shouldInvokeHttpResponseWithExamplesUrl)
{
    EXPECT_CALL(*httpHandler, get(wordsApiExamplesUrl, headers)).WillOnce(Return(response));

    const auto actualResponse = wordsApiResponseFetcher.tryGetWordExamplesResponse(englishWord);

    ASSERT_EQ(actualResponse, response);
}

TEST_F(WordsApiResponseFetcherTest_WithApiKey, getSynonyms_shouldInvokeHttpResponseWithSynonymsUrl)
{
    EXPECT_CALL(*httpHandler, get(wordsApiSynonymsUrl, headers)).WillOnce(Return(response));

    const auto actualResponse = wordsApiResponseFetcher.tryGetWordSynonymsResponse(englishWord);

    ASSERT_EQ(actualResponse, response);
}

class WordsApiResponseFetcherTest_WithoutApiKey : public WordsApiResponseFetcherTest_WithoutApiKey_Base
{
public:
    WordsApiResponseFetcher wordsApiResponseFetcher{httpHandler, std::move(apiKeyReaderInit)};
};

TEST_F(WordsApiResponseFetcherTest_WithoutApiKey, getDefinitions_shouldThrowInvalidApiKey)
{
    ASSERT_THROW(wordsApiResponseFetcher.tryGetWordDefinitionsResponse(englishWord),
                 exceptions::InvalidApiKey);
}

TEST_F(WordsApiResponseFetcherTest_WithoutApiKey, getExamples_shouldThrowInvalidApiKey)
{
    ASSERT_THROW(wordsApiResponseFetcher.tryGetWordExamplesResponse(englishWord), exceptions::InvalidApiKey);
}

TEST_F(WordsApiResponseFetcherTest_WithoutApiKey, getSentences_shouldThrowInvalidApiKey)
{
    ASSERT_THROW(wordsApiResponseFetcher.tryGetWordSynonymsResponse(englishWord), exceptions::InvalidApiKey);
}