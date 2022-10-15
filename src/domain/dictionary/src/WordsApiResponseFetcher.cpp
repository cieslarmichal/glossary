#include "WordsApiResponseFetcher.h"

#include "../include/exceptions/InvalidApiKey.h"
#include "httpClient/HttpStatusCode.h"

namespace glossary::dictionary
{
namespace
{
const std::string definitions{"definitions"};
const std::string examples{"examples"};
const std::string synonyms{"synonyms"};
const std::string hostHeader{"x-rapidapi-host: "};
const std::string host{"wordsapiv1.p.rapidapi.com"};
const std::string keyHeader{"x-rapidapi-key: "};
}

const std::string WordsApiResponseFetcher::wordsApiUrl{"https://wordsapiv1.p.rapidapi.com/words/"};

WordsApiResponseFetcher::WordsApiResponseFetcher(
    std::shared_ptr<const common::httpClient::HttpClient> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

common::httpClient::HttpResponse
WordsApiResponseFetcher::tryGetWordDefinitionsResponse(const std::string& englishWord,
                                                       const std::string& wordsApiKey) const
{
    const auto wordDefinitionsUrl = wordsApiUrl + englishWord + "/" + definitions;

    const std::vector<std::string> headers{hostHeader + host, keyHeader + wordsApiKey};

    auto response = httpHandler->get({wordDefinitionsUrl, headers});

    if (responseFailedDueToInvalidApiKey(response.statusCode))
    {
        throw exceptions::InvalidApiKey{"Invalid api key"};
    }
    return response;
}

common::httpClient::HttpResponse
WordsApiResponseFetcher::tryGetWordExamplesResponse(const std::string& englishWord,
                                                    const std::string& wordsApiKey) const
{
    const auto wordExamplesUrl = wordsApiUrl + englishWord + "/" + examples;

    const std::vector<std::string> headers{hostHeader + host, keyHeader + wordsApiKey};

    auto response = httpHandler->get({wordExamplesUrl, headers});

    if (responseFailedDueToInvalidApiKey(response.statusCode))
    {
        throw exceptions::InvalidApiKey{"Invalid api key"};
    }

    return response;
}

common::httpClient::HttpResponse
WordsApiResponseFetcher::tryGetWordSynonymsResponse(const std::string& englishWord,
                                                    const std::string& wordsApiKey) const
{
    const auto wordSynonymsUrl = wordsApiUrl + englishWord + "/" + synonyms;

    const std::vector<std::string> headers{hostHeader + host, keyHeader + wordsApiKey};

    auto response = httpHandler->get({wordSynonymsUrl, headers});

    if (responseFailedDueToInvalidApiKey(response.statusCode))
    {
        throw exceptions::InvalidApiKey{"Invalid api key"};
    }

    return response;
}

bool WordsApiResponseFetcher::responseFailedDueToInvalidApiKey(int responseCode) const
{
    return responseCode == common::httpClient::HttpStatusCode::Unauthorized ||
           responseCode == common::httpClient::HttpStatusCode::BadRequest;
}

}