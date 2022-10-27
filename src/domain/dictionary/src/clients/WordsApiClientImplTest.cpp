#include "WordsApiClientImpl.h"

#include "gtest/gtest.h"

#include "httpClient/HttpClientMock.h"

#include "exceptions/InvalidJsonError.h"
#include "exceptions/WordsApiClientError.h"
#include "exceptions/WordsApiJsonResponseMissingRequiredFieldsError.h"
#include "httpClient/HttpStatusCode.h"

using namespace ::testing;
using namespace glossary;
using namespace dictionary;

namespace
{
const std::string definitionsResponseBody =
    R"({"word":"fetch",
"definitions":[
{"definition":"be sold for a certain price","partOfSpeech":"verb"},
{"definition":"go or come after and bring or take back","partOfSpeech":"verb"},
{"definition":"take away or remove","partOfSpeech":"verb"},
{"definition":"the action of fetching","partOfSpeech":"noun"}
]})";
const std::string definitionsResponseBodyWithoutDefinitionsField =
    R"({"word":"fetch",
"missing":[
{"definition":"be sold for a certain price","partOfSpeech":"verb"}
]})";
const std::string examplesResponseBody =
    R"({"word":"fetch",
"examples":[
"The old print fetched a high price at the auction",
"The dog fetched the hat",
"The devil will fetch you!"
]})";
const std::string examplesResponseBodyWithoutExamplesField =
    R"({"word":"fetch",
"missing":[
"The devil will fetch you!"
]})";
const std::string synonymsResponseBody =
    R"({"word":"fetch",
"synonyms":[
"bring",
"bring in",
"convey",
"get"
]})";
const std::string synonymsResponseBodyWithoutSynonymsField =
    R"({"word":"fetch",
"missing":[
"bring"
]})";
const std::vector<std::string> expectedDefinitions{"be sold for a certain price",
                                                   "go or come after and bring or take back", "take away or remove",
                                                   "the action of fetching"};
const std::vector<std::string> expectedExamples{"The old print fetched a high price at the auction",
                                                "The dog fetched the hat", "The devil will fetch you!"};
const std::vector<std::string> expectedSynonyms{"bring", "bring in", "convey", "get"};
const std::string englishWord{"fetch"};
const auto wordsApiBaseUrl = "https://wordsapiv1.p.rapidapi.com";
const auto wordsApiHost = "wordsapiv1.p.rapidapi.com";
const auto wordsApiKey = "secretKey";
const WordsApiClientConfig config{wordsApiBaseUrl, wordsApiHost, wordsApiKey};
const std::map<std::string, std::string> headers{{"x-rapidapi-host", wordsApiHost}, {"x-rapidapi-key", wordsApiKey}};
const std::string wordsApiDefinitionsUrl{"https://wordsapiv1.p.rapidapi.com/words/fetch/definitions"};
const std::string wordsApiExamplesUrl{"https://wordsapiv1.p.rapidapi.com/words/fetch/examples"};
const std::string wordsApiSynonymsUrl{"https://wordsapiv1.p.rapidapi.com/words/fetch/synonyms"};
const common::httpClient::HttpGetRequestPayload definitionsGetPayload{wordsApiDefinitionsUrl, headers};
const common::httpClient::HttpGetRequestPayload examplesGetPayload{wordsApiExamplesUrl, headers};
const common::httpClient::HttpGetRequestPayload synonymsGetPayload{wordsApiSynonymsUrl, headers};
}

class WordsApiClientImplTest : public Test
{
public:
    std::shared_ptr<common::httpClient::HttpClientMock> httpClient =
        std::make_shared<StrictMock<common::httpClient::HttpClientMock>>();
    WordsApiClientImpl wordsApiClient{httpClient, config};
};

TEST_F(WordsApiClientImplTest, givenDefinitionsResponseStatusCodeNotOk_shouldThrowError)
{
    const auto response = common::httpClient::HttpResponse{common::httpClient::HttpStatusCode::Unauthorized, ""};

    EXPECT_CALL(*httpClient, get(definitionsGetPayload)).WillOnce(Return(response));

    ASSERT_THROW(wordsApiClient.getWordDefinitions(englishWord), exceptions::WordsApiClientError);
}

TEST_F(WordsApiClientImplTest, givenDefinitionsResponseBodyWithNoDefinitionsField_shouldThrowError)
{
    const auto response = common::httpClient::HttpResponse{common::httpClient::HttpStatusCode::Ok,
                                                           definitionsResponseBodyWithoutDefinitionsField};

    EXPECT_CALL(*httpClient, get(definitionsGetPayload)).WillOnce(Return(response));

    ASSERT_THROW(wordsApiClient.getWordDefinitions(englishWord),
                 exceptions::WordsApiJsonResponseMissingRequiredFieldsError);
}

TEST_F(WordsApiClientImplTest, givenCorrectDefinitionsResponseBody_shouldReturnDefinitions)
{
    const auto response =
        common::httpClient::HttpResponse{common::httpClient::HttpStatusCode::Ok, definitionsResponseBody};

    EXPECT_CALL(*httpClient, get(definitionsGetPayload)).WillOnce(Return(response));

    const auto actualDefinitions = wordsApiClient.getWordDefinitions(englishWord);

    ASSERT_EQ(actualDefinitions, expectedDefinitions);
}

TEST_F(WordsApiClientImplTest, givenExamplesResponseStatusCodeNotOk_shouldThrowError)
{
    const auto response = common::httpClient::HttpResponse{common::httpClient::HttpStatusCode::Unauthorized, ""};

    EXPECT_CALL(*httpClient, get(examplesGetPayload)).WillOnce(Return(response));

    ASSERT_THROW(wordsApiClient.getWordExamples(englishWord), exceptions::WordsApiClientError);
}

TEST_F(WordsApiClientImplTest, givenExamplesResponseBodyWithNoExamplesField_shouldThrowError)
{
    const auto response = common::httpClient::HttpResponse{common::httpClient::HttpStatusCode::Ok,
                                                           examplesResponseBodyWithoutExamplesField};

    EXPECT_CALL(*httpClient, get(examplesGetPayload)).WillOnce(Return(response));

    ASSERT_THROW(wordsApiClient.getWordExamples(englishWord),
                 exceptions::WordsApiJsonResponseMissingRequiredFieldsError);
}

TEST_F(WordsApiClientImplTest, givenCorrectExamplesResponseBody_shouldReturnDefinitions)
{
    const auto response =
        common::httpClient::HttpResponse{common::httpClient::HttpStatusCode::Ok, examplesResponseBody};

    EXPECT_CALL(*httpClient, get(examplesGetPayload)).WillOnce(Return(response));

    const auto actualExamples = wordsApiClient.getWordExamples(englishWord);

    ASSERT_EQ(actualExamples, expectedExamples);
}

TEST_F(WordsApiClientImplTest, givenSynonymsResponseStatusCodeNotOk_shouldThrowError)
{
    const auto response = common::httpClient::HttpResponse{common::httpClient::HttpStatusCode::Unauthorized, ""};

    EXPECT_CALL(*httpClient, get(synonymsGetPayload)).WillOnce(Return(response));

    ASSERT_THROW(wordsApiClient.getWordSynonyms(englishWord), exceptions::WordsApiClientError);
}

TEST_F(WordsApiClientImplTest, givenSynonymsResponseBodyWithNoSynonymsField_shouldThrowError)
{
    const auto response = common::httpClient::HttpResponse{common::httpClient::HttpStatusCode::Ok, synonymsResponseBodyWithoutSynonymsField};

    EXPECT_CALL(*httpClient, get(synonymsGetPayload)).WillOnce(Return(response));

    ASSERT_THROW(wordsApiClient.getWordSynonyms(englishWord),
                 exceptions::WordsApiJsonResponseMissingRequiredFieldsError);
}

TEST_F(WordsApiClientImplTest, givenCorrectSynonymsResponseBody_shouldReturnDefinitions)
{
    const auto response = common::httpClient::HttpResponse{common::httpClient::HttpStatusCode::Ok, synonymsResponseBody};

    EXPECT_CALL(*httpClient, get(synonymsGetPayload)).WillOnce(Return(response));

    const auto actualSynonyms = wordsApiClient.getWordSynonyms(englishWord);

    ASSERT_EQ(actualSynonyms, expectedSynonyms);
}
