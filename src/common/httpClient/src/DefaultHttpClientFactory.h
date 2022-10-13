#pragma once

#include "HttpClientFactory.h"

namespace common::httpClient
{
class DefaultHttpClientFactory : public HttpClientFactory
{
public:
    std::unique_ptr<HttpClient> createHttpClient() const override;
};
}