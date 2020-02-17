#pragma once

#include <stdexcept>

#include "HttpHandler.h"

namespace webConnection
{

class HttpHandlerImpl : public HttpHandler
{
public:
    Response get(const Request&) const override;
};
}
