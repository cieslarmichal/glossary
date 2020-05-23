#pragma once

#include "gmock/gmock.h"

#include "HttpHandler.h"

namespace webConnection
{

class HttpHandlerMock : public HttpHandler
{
public:
    MOCK_CONST_METHOD1(get, Response(const Request&));
    MOCK_CONST_METHOD2(get, Response(const std::string& url, const std::vector<std::string>& headers));
};
}