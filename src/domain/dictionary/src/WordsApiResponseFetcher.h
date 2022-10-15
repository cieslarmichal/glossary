#pragma once

#include <memory>

#include "ApiResponseFetcher.h"
#include "httpClient/HttpClient.h"

namespace glossary::dictionary
{
class WordsApiResponseFetcher : public ApiResponseFetcher
{
public:
    explicit WordsApiResponseFetcher(std::shared_ptr<const common::httpClient::HttpClient>);

    common::httpClient::HttpResponse
    tryGetWordDefinitionsResponse(const std::string& englishWord,
                                  const std::string& wordsApiKey) const override;
    common::httpClient::HttpResponse
    tryGetWordExamplesResponse(const std::string& englishWord, const std::string& wordsApiKey) const override;
    common::httpClient::HttpResponse
    tryGetWordSynonymsResponse(const std::string& englishWord, const std::string& wordsApiKey) const override;

private:
    bool responseFailedDueToInvalidApiKey(int) const;

    std::shared_ptr<const common::httpClient::HttpClient> httpHandler;

    static const std::string wordsApiUrl;
};
}