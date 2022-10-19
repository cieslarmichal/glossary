#pragma once

#include "GetPayload.h"
#include "HttpResponse.h"

namespace common::httpClient
{
class HttpClient
{
public:
    virtual ~HttpClient() = default;

    virtual HttpResponse get(const GetPayload&) const = 0;
};
}
