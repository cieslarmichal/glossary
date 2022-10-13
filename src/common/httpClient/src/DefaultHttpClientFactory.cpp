#include "DefaultHttpClientFactory.h"

#include "CurlHttpClient.h"

namespace common::httpClient
{
std::unique_ptr<HttpClient> DefaultHttpClientFactory::createHttpClient() const
{
    return std::make_unique<CurlHttpClient>();
}
}