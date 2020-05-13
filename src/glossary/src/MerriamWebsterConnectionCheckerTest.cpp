#include "MerriamWebsterConnectionChecker.h"

#include "gtest/gtest.h"

#include "webConnection/HttpHandlerMock.h"

#include "webConnection/exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace glossary;

namespace
{
const std::string urlAddress{"https://www.merriam-webster.com/dictionary/"};
const webConnection::Response okResponse{200, {}};
}

class MerriamWebsterConnectionCheckerTest : public Test
{
public:
    std::shared_ptr<webConnection::HttpHandlerMock> httpHandler =
        std::make_shared<StrictMock<webConnection::HttpHandlerMock>>();
    MerriamWebsterConnectionChecker connectionChecker{httpHandler};
};

TEST_F(MerriamWebsterConnectionCheckerTest,
       givenConnectionFailedFromHttpHandler_shouldReturnConnectionUnavailable)
{
    EXPECT_CALL(*httpHandler, get(urlAddress))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    const auto connectionStatus = connectionChecker.connectionAvailable();

    ASSERT_EQ(connectionStatus, ConnectionStatus::Unavailable);
}

TEST_F(MerriamWebsterConnectionCheckerTest, givenOkResponseFromHttpHandler_shouldReturnConnectionAvailable)
{
    EXPECT_CALL(*httpHandler, get(urlAddress)).WillOnce(Return(okResponse));

    const auto connectionStatus = connectionChecker.connectionAvailable();

    ASSERT_EQ(connectionStatus, ConnectionStatus::Available);
}
