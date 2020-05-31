#pragma once

#include <memory>

#include "../../wordDescriptionService/src/ApiKeyReader.h"
#include "ApiResponseFetcher.h"
#include "webConnection/HttpHandler.h"

namespace glossary::wordDescriptionDownloader
{
class WordsApiResponseFetcher : public ApiResponseFetcher
{
public:
    explicit WordsApiResponseFetcher(std::shared_ptr<const webConnection::HttpHandler>);

    webConnection::Response tryGetWordDefinitionsResponse(const std::string& englishWord,
                                                          const std::string& wordsApiKey) const override;
    webConnection::Response tryGetWordExamplesResponse(const std::string& englishWord,
                                                       const std::string& wordsApiKey) const override;
    webConnection::Response tryGetWordSynonymsResponse(const std::string& englishWord,
                                                       const std::string& wordsApiKey) const override;

private:
    bool responseFailedDueToInvalidApiKey(webConnection::ResponseCode) const;

    std::shared_ptr<const webConnection::HttpHandler> httpHandler;

    static const std::string wordsApiUrl;
};
}