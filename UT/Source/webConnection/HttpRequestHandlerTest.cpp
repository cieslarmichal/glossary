#include "FileAccessImpl.h"
#include "exceptions/ConnectionFailed.h"
#include "gtest/gtest.h"
#include "webConnection/HttpRequestHandlerImpl.h"

using namespace ::testing;
using namespace webConnection;

class HttpRequestHandlerTest : public Test
{
public:
    HttpRequestHandlerImpl httpHandler;
    FileAccessImpl fileAccess;
};

TEST_F(HttpRequestHandlerTest,
       givenCorrectUrlAddress_shouldReturnContentOfTheHtmlFile)
{
    const std::string correctUrlAddress = "https://www.merriam-webster.com/";

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
