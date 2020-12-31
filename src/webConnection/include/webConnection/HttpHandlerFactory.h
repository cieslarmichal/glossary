#pragma once

#include <memory>

#include "HttpHandler.h"
#include "WebConnectionApi.h"

namespace webConnection
{
class WEB_CONNECTION_API HttpHandlerFactory
{
public:
    virtual ~HttpHandlerFactory() = default;

    virtual std::unique_ptr<HttpHandler> createHttpHandler() const = 0;

    static std::unique_ptr<HttpHandlerFactory> createHttpHandlerFactory();
};
}