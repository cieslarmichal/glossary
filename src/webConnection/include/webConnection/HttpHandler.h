#pragma once

#include <vector>

#include "Request.h"
#include "Response.h"

namespace webConnection
{
class HttpHandler
{
public:
    virtual ~HttpHandler() = default;

    virtual Response get(const Request&) const = 0;
    virtual Response get(const std::string& url, const std::vector<std::string>& headers) const = 0;
};
}
