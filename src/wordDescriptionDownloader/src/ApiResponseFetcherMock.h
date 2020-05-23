#pragma once

#include "gmock/gmock.h"

#include "ApiResponseFetcher.h"

namespace glossary::wordDescriptionDownloader
{
class ApiResponseFetcherMock : public ApiResponseFetcher
{
public:
    MOCK_CONST_METHOD1(tryGetWordDefinitionsResponse,
                       webConnection::Response(const std::string& englishWord));
    MOCK_CONST_METHOD1(tryGetWordExamplesResponse, webConnection::Response(const std::string& englishWord));
    MOCK_CONST_METHOD1(tryGetWordSynonymsResponse, webConnection::Response(const std::string& englishWord));
};
}