#pragma once

#include <memory>

#include "ApiKeyReader.h"
#include "ApiResponseFetcher.h"
#include "webConnection/HttpHandler.h"

namespace glossary::wordDescriptionDownloader
{
class WordsApiResponseFetcher : public ApiResponseFetcher
{
public:
    WordsApiResponseFetcher(std::shared_ptr<const webConnection::HttpHandler>, std::unique_ptr<ApiKeyReader>);

    webConnection::Response tryGetWordDefinitionsResponse(const std::string& englishWord) const override;
    webConnection::Response tryGetWordExamplesResponse(const std::string& englishWord) const override;
    webConnection::Response tryGetWordSynonymsResponse(const std::string& englishWord) const override;

private:
    std::shared_ptr<const webConnection::HttpHandler> httpHandler;
    std::unique_ptr<ApiKeyReader> apiKeyReader;
    boost::optional<std::string> wordsApiKey;

    static const std::string wordsApiUrl;
};
}