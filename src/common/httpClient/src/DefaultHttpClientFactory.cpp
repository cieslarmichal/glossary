#include "DefaultHttpClientFactory.h"

#include "CprHttpClient.h"

namespace common::httpClient
{
std::unique_ptr<HttpClient> DefaultHttpClientFactory::createHttpClient() const
{
    return std::make_unique<CprHttpClient>();
}
}