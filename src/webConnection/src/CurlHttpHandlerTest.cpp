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

TEST_F(CurlHttpHandlerTest, givenCorrectUrlAddress_shouldReturnOkAndContentOfResponse)
{
    const std::string correctUrlAddress = "https://www.merriam-webster.com/dictionary/ankle";

    const auto response = httpHandler.get(correctUrlAddress);

    ASSERT_EQ(response.code, 200);
    ASSERT_FALSE(response.content.empty());
}

TEST_F(CurlHttpHandlerTest, givenIncorrectUrlAddress_shouldThrowConnectionFailed)
{
    const auto inaccessibleUrlAddress = ".xh111ttps://aazzz.com";

    ASSERT_THROW(httpHandler.get(inaccessibleUrlAddress), exceptions::ConnectionFailed);
}

TEST_F(CurlHttpHandlerTest, givenCorrectUrlAddressWithHeaders_shouldReturnOkAndContentOfTheHtmlFile)
{
    const std::string correctUrlAddress = "https://wordsapiv1.p.rapidapi.com/words/fetch/synonyms";
    const std::vector<std::string> headers{"x-rapidapi-host: wordsapiv1.p.rapidapi.com"};

    const auto response = httpHandler.get(correctUrlAddress, headers);

    ASSERT_EQ(response.code, 401);
    ASSERT_FALSE(response.content.empty());
}