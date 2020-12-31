#pragma once

#include <vector>

#include "Request.h"
#include "Response.h"
#include "WebConnectionApi.h"

namespace webConnection
{
class HttpHandler
{
public:
    virtual ~HttpHandler() = default;

    virtual WEB_CONNECTION_API Response get(const Request&) const = 0;
    virtual WEB_CONNECTION_API Response get(const std::string& url, const std::vector<std::string>& headers) const = 0;
};
}
