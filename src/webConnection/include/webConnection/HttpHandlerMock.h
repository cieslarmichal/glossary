#pragma once

#include "gmock/gmock.h"

#include "HttpHandler.h"

namespace webConnection
{

class HttpHandlerMock : public HttpHandler
{
public:
    MOCK_CONST_METHOD1(get, Response(const Request&));
};
}