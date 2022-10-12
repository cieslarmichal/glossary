#pragma once

#include <stdexcept>

#include "HttpClient.h"

namespace httpClient
{
class CurlHttpClient : public HttpClient
{
public:
    HttpResponse get(const GetPayload&) const override;
};
}
