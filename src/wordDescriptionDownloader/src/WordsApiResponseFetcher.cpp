#include "WordsApiResponseFetcher.h"

#include "exceptions/InvalidApiKey.h"

namespace glossary::wordDescriptionDownloader
{
namespace
{
const std::string definitions{"definitions"};
const std::string examples{"examples"};
const std::string synonyms{"synonyms"};
const std::string hostHeader{"x-rapidapi-host: "};
const std::string host{"wordsapiv1.p.rapidapi.com"};
const std::string keyHeader{"x-rapidapi-key: "};
constexpr int invalidApiKeyCode1 = 400;
constexpr int invalidApiKeyCode2 = 401;
}

const std::string WordsApiResponseFetcher::wordsApiUrl{"https://wordsapiv1.p.rapidapi.com/words/"};

WordsApiResponseFetcher::WordsApiResponseFetcher(
    std::shared_ptr<const webConnection::HttpHandler> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

webConnection::Response
WordsApiResponseFetcher::tryGetWordDefinitionsResponse(const std::string& englishWord,
                                                       const std::string& wordsApiKey) const
{
    const auto wordDefinitionsUrl = wordsApiUrl + englishWord + "/" + definitions;
    const std::vector<std::string> headers{hostHeader + host, keyHeader + wordsApiKey};

    auto response = httpHandler->get(wordDefinitionsUrl, headers);

    if (responseFailedDueToInvalidApiKey(response.code))
    {
        throw exceptions::InvalidApiKey{"Invalid api key"};
    }
    return response;
}

webConnection::Response
WordsApiResponseFetcher::tryGetWordExamplesResponse(const std::string& englishWord,
                                                    const std::string& wordsApiKey) const
{
    const auto wordExamplesUrl = wordsApiUrl + englishWord + "/" + examples;
    const std::vector<std::string> headers{hostHeader + host, keyHeader + wordsApiKey};

    auto response = httpHandler->get(wordExamplesUrl, headers);

    if (responseFailedDueToInvalidApiKey(response.code))
    {
        throw exceptions::InvalidApiKey{"Invalid api key"};
    }
    return response;
}

webConnection::Response
WordsApiResponseFetcher::tryGetWordSynonymsResponse(const std::string& englishWord,
                                                    const std::string& wordsApiKey) const
{
    const auto wordSynonymsUrl = wordsApiUrl + englishWord + "/" + synonyms;
    const std::vector<std::string> headers{hostHeader + host, keyHeader + wordsApiKey};

    auto response = httpHandler->get(wordSynonymsUrl, headers);

    if (responseFailedDueToInvalidApiKey(response.code))
    {
        throw exceptions::InvalidApiKey{"Invalid api key"};
    }
    return response;
}

bool WordsApiResponseFetcher::responseFailedDueToInvalidApiKey(webConnection::ResponseCode responseCode) const
{
    return responseCode == invalidApiKeyCode1 || responseCode == invalidApiKeyCode2;
}

}