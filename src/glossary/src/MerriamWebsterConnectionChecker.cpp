#include "MerriamWebsterConnectionChecker.h"

#include <iostream>

#include "webConnection/exceptions/ConnectionFailed.h"

namespace glossary
{

const std::string MerriamWebsterConnectionChecker::merriamWebsterUrlAddress{
    "https://www.merriam-webster.com/dictionary/"};

MerriamWebsterConnectionChecker::MerriamWebsterConnectionChecker(
    std::shared_ptr<const webConnection::HttpHandler> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

bool MerriamWebsterConnectionChecker::connectionAvailable() const
{
    try
    {
        httpHandler->get(merriamWebsterUrlAddress);
        return true;
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Connection to " << merriamWebsterUrlAddress << " is not available: " << e.what();
        return false;
    }
}

}