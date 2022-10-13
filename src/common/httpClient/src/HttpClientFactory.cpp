#include "HttpClientFactory.h"

#include "DefaultHttpClientFactory.h"

namespace common::httpClient
{
std::unique_ptr<HttpClientFactory> HttpClientFactory::createHttpClientFactory()
{
    return std::make_unique<DefaultHttpClientFactory>();
}
}