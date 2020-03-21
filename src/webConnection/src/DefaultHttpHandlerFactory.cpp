#include "DefaultHttpHandlerFactory.h"

#include "CurlHttpHandler.h"

namespace webConnection
{
std::unique_ptr<HttpHandler> DefaultHttpHandlerFactory::createHttpHandler() const
{
    return std::make_unique<CurlHttpHandler>();
}
}