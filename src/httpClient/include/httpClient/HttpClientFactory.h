#pragma once

#include <memory>

#include "HttpClient.h"

namespace httpClient
{
class HttpClientFactory
{
public:
    virtual ~HttpClientFactory() = default;

    virtual std::unique_ptr<HttpClient> createHttpClient() const = 0;

    static std::unique_ptr<HttpClientFactory> createHttpClientFactory();
};
}