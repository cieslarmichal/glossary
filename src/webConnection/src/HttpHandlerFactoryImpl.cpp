#include "HttpHandlerFactoryImpl.h"

#include "HttpHandlerImpl.h"

namespace webConnection
{
std::unique_ptr<HttpHandler> HttpHandlerFactoryImpl::createHttpHandler() const
{
    return std::make_unique<HttpHandlerImpl>();
}
}