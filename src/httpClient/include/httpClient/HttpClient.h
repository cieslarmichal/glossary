#pragma once

#include <vector>

#include "GetPayload.h"
#include "HttpResponse.h"

namespace httpClient
{
class HttpClient
{
public:
    virtual ~HttpClient() = default;

    virtual HttpResponse get(const GetPayload&) const = 0;
};
}
