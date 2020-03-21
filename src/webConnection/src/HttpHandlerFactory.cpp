#include "HttpHandlerFactory.h"

#include "DefaultHttpHandlerFactory.h"

namespace webConnection
{

std::unique_ptr<HttpHandlerFactory> HttpHandlerFactory::createHttpHandlerFactory()
{
    return std::make_unique<DefaultHttpHandlerFactory>();
}
}