#pragma once

#include "webConnection/Response.h"

namespace glossary::wordDescriptionDownloader
{
class ApiResponseFetcher
{
public:
    virtual ~ApiResponseFetcher() = default;

    virtual webConnection::Response tryGetWordDefinitionsResponse(const std::string& englishWord) const = 0;
    virtual webConnection::Response tryGetWordExamplesResponse(const std::string& englishWord) const = 0;
    virtual webConnection::Response tryGetWordSynonymsResponse(const std::string& englishWord) const = 0;
};
}