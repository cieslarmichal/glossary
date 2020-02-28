#include "HttpHandlerFactory.h"

#include "HttpHandlerFactoryImpl.h"

namespace webConnection
{

std::unique_ptr<HttpHandlerFactory> HttpHandlerFactory::createHttpHandlerFactory()
{
    return std::make_unique<HttpHandlerFactoryImpl>();
}
}