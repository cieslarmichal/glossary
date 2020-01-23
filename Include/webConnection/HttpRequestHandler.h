#pragma once

#include "Request.h"
#include "Response.h"

namespace webConnection
{

class HttpRequestHandler
{
public:
    virtual ~HttpRequestHandler() = default;

    virtual Response get(const Request&) const = 0;
};
}
