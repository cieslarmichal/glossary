#include "CurlHttpHandler.h"

#include "gtest/gtest.h"

#include "exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace webConnection;

class CurlHttpHandlerTest : public Test
{
public:
    CurlHttpHandler httpHandler;
};

TEST_F(CurlHttpHandlerTest, givenCorrectUrlAddress_shouldReturnOkAndContentOfTheHtmlFile)
{
    const std::string correctUrlAddress = "https://www.merriam-webster.com/dictionary/ankle";

    const auto response = httpHandler.get(correctUrlAddress);

    ASSERT_EQ(response.code, 200);
    ASSERT_TRUE(response.content.find("<!DOCTYPE html>") || response.content.find("<!doctype html>"));
}

TEST_F(CurlHttpHandlerTest, givenIncorrectUrlAddress_shouldThrowConnectionFailed)
{
    const auto inaccessibleUrlAddress = ".xh111ttps://aazzz.com";

    ASSERT_THROW(httpHandler.get(inaccessibleUrlAddress), exceptions::ConnectionFailed);
}
