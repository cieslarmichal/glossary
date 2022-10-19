#pragma once

#include "HttpClient.h"

namespace common::httpClient
{
class CprHttpClient : public HttpClient
{
public:
    HttpResponse get(const GetPayload&) const override;
};
}
