#pragma once

#include <stdexcept>

#include "HttpHandler.h"

namespace webConnection
{

class CurlHttpHandler : public HttpHandler
{
public:
    Response get(const Request&) const override;
};
}
