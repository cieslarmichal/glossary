#pragma once

#include <memory>

#include "HttpHandler.h"

namespace webConnection
{
class HttpHandlerFactory
{
public:
    virtual ~HttpHandlerFactory() = default;

    virtual std::unique_ptr<HttpHandler>
    createHttpHandler() const = 0;

    static std::unique_ptr<HttpHandlerFactory>
    createHttpHandlerFactory();
};
}