#pragma once

#include "httpClient/HttpResponse.h"

namespace glossary::wordDescriptionDownloader
{
class ApiResponseFetcher
{
public:
    virtual ~ApiResponseFetcher() = default;

    virtual common::httpClient::HttpResponse
    tryGetWordDefinitionsResponse(const std::string& englishWord, const std::string& wordsApiKey) const = 0;
    virtual common::httpClient::HttpResponse
    tryGetWordExamplesResponse(const std::string& englishWord, const std::string& wordsApiKey) const = 0;
    virtual common::httpClient::HttpResponse
    tryGetWordSynonymsResponse(const std::string& englishWord, const std::string& wordsApiKey) const = 0;
};
}