#pragma once

#include <stdexcept>

#include "HttpRequestHandler.h"

namespace webConnection
{

class HttpRequestHandlerImpl : public HttpRequestHandler
{
public:
    Response get(const Request&) const override;
};
}
