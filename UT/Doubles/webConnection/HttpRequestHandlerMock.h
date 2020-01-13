#pragma once

#include "gmock/gmock.h"

#include "webConnection/HttpRequestHandler.h"

namespace webConnection
{

class HttpRequestHandlerMock : public HttpRequestHandler
{
public:
    MOCK_CONST_METHOD1(get, Response(const Request&));
};
}