#pragma once

#include <memory>

#include "../../wordDescriptionService/src/ApiKeyReader.h"
#include "ApiResponseFetcher.h"
#include "httpClient/HttpClient.h"

namespace glossary::wordDescriptionDownloader
{
class WordsApiResponseFetcher : public ApiResponseFetcher
{
public:
    explicit WordsApiResponseFetcher(std::shared_ptr<const httpClient::HttpClient>);

    httpClient::HttpResponse tryGetWordDefinitionsResponse(const std::string& englishWord,
                                                          const std::string& wordsApiKey) const override;
    httpClient::HttpResponse tryGetWordExamplesResponse(const std::string& englishWord,
                                                       const std::string& wordsApiKey) const override;
    httpClient::HttpResponse tryGetWordSynonymsResponse(const std::string& englishWord,
                                                       const std::string& wordsApiKey) const override;

private:
    bool responseFailedDueToInvalidApiKey(int) const;

    std::shared_ptr<const httpClient::HttpClient> httpHandler;

    static const std::string wordsApiUrl;
};
}