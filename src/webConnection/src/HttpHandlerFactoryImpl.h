#pragma once

#include "HttpHandlerFactory.h"

namespace webConnection
{
class HttpHandlerFactoryImpl : public HttpHandlerFactory
{
public:
    std::unique_ptr<HttpHandler>
    createHttpHandler() const override;
};
}