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
}

const std::string WordsApiResponseFetcher::wordsApiUrl{"https://wordsapiv1.p.rapidapi.com/words/"};

WordsApiResponseFetcher::WordsApiResponseFetcher(
    std::shared_ptr<const webConnection::HttpHandler> httpHandlerInit,
    std::unique_ptr<ApiKeyReader> apiKeyReaderInit)
    : httpHandler{std::move(httpHandlerInit)},
      apiKeyReader{std::move(apiKeyReaderInit)},
      wordsApiKey(apiKeyReader->readApiKey())
{
}

webConnection::Response
WordsApiResponseFetcher::tryGetWordDefinitionsResponse(const std::string& englishWord) const
{
    if (not wordsApiKey)
    {
        throw exceptions::InvalidApiKey{"Words api key not found"};
    }

    const auto wordDefinitionsUrl = wordsApiUrl + englishWord + "/" + definitions;
    const std::vector<std::string> headers{hostHeader + host, keyHeader + *wordsApiKey};

    return httpHandler->get(wordDefinitionsUrl, headers);
}

webConnection::Response
WordsApiResponseFetcher::tryGetWordExamplesResponse(const std::string& englishWord) const
{
    if (not wordsApiKey)
    {
        throw exceptions::InvalidApiKey{"Words api key not found"};
    }

    const auto wordExamplesUrl = wordsApiUrl + englishWord + "/" + examples;
    const std::vector<std::string> headers{hostHeader + host, keyHeader + *wordsApiKey};

    return httpHandler->get(wordExamplesUrl, headers);
}

webConnection::Response
WordsApiResponseFetcher::tryGetWordSynonymsResponse(const std::string& englishWord) const
{
    if (not wordsApiKey)
    {
        throw exceptions::InvalidApiKey{"Words api key not found"};
    }

    const auto wordSynonymsUrl = wordsApiUrl + englishWord + "/" + synonyms;
    const std::vector<std::string> headers{hostHeader + host, keyHeader + *wordsApiKey};

    return httpHandler->get(wordSynonymsUrl, headers);
}

}