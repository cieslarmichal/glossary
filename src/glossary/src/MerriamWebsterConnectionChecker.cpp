#include "MerriamWebsterConnectionChecker.h"

#include <iostream>

#include "webConnection/exceptions/ConnectionFailed.h"

namespace glossary
{
// TODO: delete this class and add method in WdService like in TranslationService
const std::string MerriamWebsterConnectionChecker::merriamWebsterUrlAddress{
    "https://www.merriam-webster.com/dictionary/"};

MerriamWebsterConnectionChecker::MerriamWebsterConnectionChecker(
    std::shared_ptr<const webConnection::HttpHandler> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

ConnectionStatus MerriamWebsterConnectionChecker::connectionAvailable() const
{
    try
    {
        httpHandler->get(merriamWebsterUrlAddress);
        return ConnectionStatus::Available;
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Connection to " << merriamWebsterUrlAddress << " is not available: " << e.what();
        return ConnectionStatus::Unavailable;
    }
}

}