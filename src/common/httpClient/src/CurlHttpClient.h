#pragma once

#include <stdexcept>

#include "HttpClient.h"

namespace common::httpClient
{
class CurlHttpClient : public HttpClient
{
public:
    HttpResponse get(const GetPayload&) const override;
};
}
