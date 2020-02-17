#include "HttpHandlerImpl.h"
#include "exceptions/ConnectionFailed.h"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace webConnection;

class HttpHandlerTest : public Test
{
public:
    HttpHandlerImpl httpHandler;
};

TEST_F(HttpHandlerTest,
       givenCorrectUrlAddress_shouldReturnOkAndContentOfTheHtmlFile)
{
    const std::string correctUrlAddress =
        "https://www.merriam-webster.com/dictionary/ankle";

    const auto response = httpHandler.get(correctUrlAddress);

    ASSERT_EQ(response.code, 200);
    ASSERT_TRUE(response.content.find("<!DOCTYPE html>") ||
                response.content.find("<!doctype html>"));
}

TEST_F(HttpHandlerTest,
       givenIncorrectUrlAddress_shouldThrowConnectionFailed)
{
    const auto inaccessibleUrlAddress = ".xh111ttps://aazzz.com";

    ASSERT_THROW(httpHandler.get(inaccessibleUrlAddress),
                 exceptions::ConnectionFailed);
}
