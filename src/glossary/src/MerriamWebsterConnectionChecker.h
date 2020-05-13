#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "ConnectionChecker.h"
#include "webConnection/HttpHandler.h"

namespace glossary
{
class MerriamWebsterConnectionChecker : public ConnectionChecker
{
public:
    explicit MerriamWebsterConnectionChecker(std::shared_ptr<const webConnection::HttpHandler>);

    ConnectionStatus connectionAvailable() const override;

private:
    std::shared_ptr<const webConnection::HttpHandler> httpHandler;

    static const std::string merriamWebsterUrlAddress;
};
}