#include "CprHttpClient.h"

#include <cpr/cpr.h>

namespace common::httpClient
{
HttpResponse CprHttpClient::get(const HttpGetRequestPayload& payload) const
{
    auto queryParameters = cpr::Parameters{};

    if (payload.queries)
    {
        for (const auto& query : *payload.queries)
        {
            queryParameters.Add({query.first, query.second});
        }
    }

    cpr::Header headers;

    if (payload.headers)
    {
        for (const auto& header : *payload.headers)
        {
            headers.insert({header.first, header.second});
        }
    }

    cpr::Response response = cpr::Get(cpr::Url{payload.url}, queryParameters, headers);

    return {static_cast<int>(response.status_code), response.text};
}
}
