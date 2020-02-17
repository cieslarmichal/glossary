#pragma once

#include "Request.h"
#include "Response.h"

namespace webConnection
{

class HttpHandler
{
public:
    virtual ~HttpHandler() = default;

    virtual Response get(const Request&) const = 0;
};
}
