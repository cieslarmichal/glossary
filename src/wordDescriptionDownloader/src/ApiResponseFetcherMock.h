#pragma once

#include "gmock/gmock.h"

#include "ApiResponseFetcher.h"

namespace glossary::wordDescriptionDownloader
{
class ApiResponseFetcherMock : public ApiResponseFetcher
{
public:
    MOCK_CONST_METHOD2(tryGetWordDefinitionsResponse,
                       webConnection::Response(const std::string& englishWord,
                                               const std::string& wordsApiKey));
    MOCK_CONST_METHOD2(tryGetWordExamplesResponse, webConnection::Response(const std::string& englishWord,
                                                                           const std::string& wordsApiKey));
    MOCK_CONST_METHOD2(tryGetWordSynonymsResponse, webConnection::Response(const std::string& englishWord,
                                                                           const std::string& wordsApiKey));
};
}