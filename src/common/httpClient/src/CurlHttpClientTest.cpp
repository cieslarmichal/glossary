#include "CurlHttpClient.h"

#include "gtest/gtest.h"

#include "exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace common::httpClient;

class CurlHttpHandlerTest : public Test
{
public:
    CurlHttpClient httpHandler;
};

TEST_F(CurlHttpHandlerTest, givenCorrectUrlAddress_shouldReturnOkAndContentOfResponse)
{
    const std::string correctUrlAddress = "https://www.merriam-webster.com/dictionary/ankle";

    const auto response = httpHandler.get({correctUrlAddress, std::nullopt});

    ASSERT_EQ(response.statusCode, 200);
    ASSERT_FALSE(response.data.empty());
}

TEST_F(CurlHttpHandlerTest, givenIncorrectUrlAddress_shouldThrowConnectionFailed)
{
    const auto inaccessibleUrlAddress = ".xh111ttps://aazzz.com";

    ASSERT_THROW(httpHandler.get({inaccessibleUrlAddress, std::nullopt}), exceptions::ConnectionFailed);
}

TEST_F(CurlHttpHandlerTest, givenCorrectUrlAddressWithHeaders_shouldReturnOkAndContentOfTheHtmlFile)
{
    const std::string correctUrlAddress = "https://wordsapiv1.p.rapidapi.com/words/fetch/synonyms";
    const std::vector<std::string> headers{};

    const auto response = httpHandler.get({correctUrlAddress, headers});

    ASSERT_EQ(response.statusCode, 401);
    ASSERT_FALSE(response.data.empty());
}