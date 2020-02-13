#include "gtest/gtest.h"
#include "webConnection/HttpRequestHandlerImpl.h"
#include "webConnection/exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace webConnection;

class HttpRequestHandlerTest : public Test
{
public:
    HttpRequestHandlerImpl httpHandler;
};

TEST_F(HttpRequestHandlerTest,
       givenCorrectUrlAddress_shouldReturnOkAndContentOfTheHtmlFile)
{
    const std::string correctUrlAddress =
        "https://www.merriam-webster.com/dictionary/ankle";

    const auto response = httpHandler.get(correctUrlAddress);

    ASSERT_EQ(response.code, 200);
    ASSERT_TRUE(response.content.find("<!DOCTYPE html>") ||
                response.content.find("<!doctype html>"));
}

TEST_F(HttpRequestHandlerTest,
       givenIncorrectUrlAddress_shouldThrowConnectionFailed)
{
    const auto inaccessibleUrlAddress = ".xh111ttps://aazzz.com";

    ASSERT_THROW(httpHandler.get(inaccessibleUrlAddress),
                 exceptions::ConnectionFailed);
}
