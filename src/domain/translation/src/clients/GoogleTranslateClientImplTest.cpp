#include "GoogleTranslateClientImpl.h"

#include "gtest/gtest.h"

#include "httpClient/HttpClientMock.h"

#include "exceptions/GoogleTranslateApiError.h"
#include "httpClient/HttpStatusCode.h"

using namespace ::testing;
using namespace glossary::translation;
using namespace common::httpClient;

namespace
{
const std::string responseBody = R"({
  "data": {
    "translations": [
      {
        "translatedText": "glass",
        "detectedSourceLanguage": "pl"
      }
    ]
  }
})";
const std::string responseBodyWithoutTranslations = R"({
  "data": {
    "translations": []
  }
})";
constexpr auto googleTranslateBaseUrl = "https://translation.googleapis.com";
constexpr auto apiKey = "topSecretKey";
const GoogleTranslateClientConfig config{googleTranslateBaseUrl, apiKey};
constexpr auto translateEndpoint = "/language/translate/v2";
constexpr auto polishText = "szklanka";
constexpr auto englishText = "glass";
constexpr auto sourceLanguage = Language::Polish;
constexpr auto targetLanguage = Language::English;
constexpr auto headers = std::nullopt;
const std::map<std::string, std::string> queries{
    {"key", config.googleTranslateApiKey}, {"q", polishText}, {"source", "pl"}, {"target", "en"}};

const auto urlAddress = fmt::format("{}{}", config.googleTranslateBaseUrl, translateEndpoint);
const common::httpClient::HttpGetRequestPayload getPayload{urlAddress, headers, queries};
}

class GoogleTranslateClientImplTest : public Test
{
public:
    std::shared_ptr<common::httpClient::HttpClientMock> httpClient =
        std::make_shared<StrictMock<common::httpClient::HttpClientMock>>();
    GoogleTranslateClientImpl googleTranslateClientImpl{httpClient, config};
};

TEST_F(GoogleTranslateClientImplTest, whenApiResponseStatusCodeIsNotOk_shouldThrowError)
{
    const auto response = HttpResponse{common::httpClient::HttpStatusCode::Unauthorized, ""};

    EXPECT_CALL(*httpClient, get(getPayload)).WillOnce(Return(response));

    ASSERT_THROW(googleTranslateClientImpl.translate({polishText, sourceLanguage, targetLanguage}),
                 glossary::translation::exceptions::GoogleTranslateApiError);
}

TEST_F(GoogleTranslateClientImplTest, whenApiResponseBodyDoesNotHaveAnyTranslations_shouldNone)
{
    const auto response =
        HttpResponse{common::httpClient::HttpStatusCode::Ok, responseBodyWithoutTranslations};

    EXPECT_CALL(*httpClient, get(getPayload)).WillOnce(Return(response));

    const auto result = googleTranslateClientImpl.translate({polishText, sourceLanguage, targetLanguage});

    ASSERT_EQ(result, std::nullopt);
}

TEST_F(GoogleTranslateClientImplTest, givenValidApiResponse_shouldReturnTranslatedText)
{
    const auto response = HttpResponse{common::httpClient::HttpStatusCode::Ok, responseBody};

    EXPECT_CALL(*httpClient, get(getPayload)).WillOnce(Return(response));

    const auto translation =
        googleTranslateClientImpl.translate({polishText, sourceLanguage, targetLanguage});

    ASSERT_EQ(translation, englishText);
}
