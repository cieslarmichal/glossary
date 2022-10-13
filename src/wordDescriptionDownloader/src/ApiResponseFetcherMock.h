#pragma once

#include "gmock/gmock.h"

#include "ApiResponseFetcher.h"

namespace glossary::wordDescriptionDownloader
{
class ApiResponseFetcherMock : public ApiResponseFetcher
{
public:
    MOCK_CONST_METHOD2(tryGetWordDefinitionsResponse,
                       common::httpClient::HttpResponse(const std::string& englishWord,
                                                        const std::string& wordsApiKey));
    MOCK_CONST_METHOD2(tryGetWordExamplesResponse,
                       common::httpClient::HttpResponse(const std::string& englishWord,
                                                        const std::string& wordsApiKey));
    MOCK_CONST_METHOD2(tryGetWordSynonymsResponse,
                       common::httpClient::HttpResponse(const std::string& englishWord,
                                                        const std::string& wordsApiKey));
};
}