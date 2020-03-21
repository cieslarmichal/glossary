#pragma once

#include "HttpHandlerFactory.h"

namespace webConnection
{
class DefaultHttpHandlerFactory : public HttpHandlerFactory
{
public:
    std::unique_ptr<HttpHandler> createHttpHandler() const override;
};
}