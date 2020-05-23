#pragma once

#include <stdexcept>

#include "HttpHandler.h"

namespace webConnection
{

class CurlHttpHandler : public HttpHandler
{
public:
    Response get(const Request&) const override;
    Response get(const std::string& url, const std::vector<std::string>& headers) const override;
};
}
