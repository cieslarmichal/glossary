#pragma once

#include "HttpGetRequestPayload.h"
#include "HttpResponse.h"

namespace common::httpClient
{
class HttpClient
{
public:
    virtual ~HttpClient() = default;

    virtual HttpResponse get(const HttpGetRequestPayload&) const = 0;
};
}
