#include "DefaultTranslationService.h"

#include "gtest/gtest.h"

#include "../serializers/GoogleTranslateApiResponseDeserializerMock.h"
#include "httpClient/HttpClientMock.h"

#include "exceptions/InvalidApiKey.h"
#include "httpClient/exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace glossary::translation;

namespace
{
const std::string baseUrl{"https://translation.googleapis.com/language/translate/v2?"};
const std::string apiKey = {"topSecretKey"};
const std::string keyField = {"key=" + apiKey};
const auto sourceField = R"(&source=pl)";
const auto targetField = R"(&target=en)";
const std::string url = baseUrl + keyField + "&q=piwo" + sourceField + targetField;
const auto responseContent = R"({"code":200,"lang":"pl-en","text":["beer"]})";
const common::httpClient::HttpResponse successResponse{200, responseContent};
const common::httpClient::HttpResponse failureResponse{400, ""};
const std::string polishText = "piwo";
const auto englishText = "beer";
const auto expectedTranslations = std::vector<GoogleTranslateApiResponseDataTranslation>{{englishText, "en"}};

const auto expectedResult = GoogleTranslateApiResponse{{expectedTranslations}};
const auto sourceLanguage = Language::Polish;
const auto targetLanguage = Language::English;
const common::httpClient::GetPayload getPayload{url, std::nullopt};
}

class DefaultTranslatorTest : public Test
{
public:
    std::shared_ptr<common::httpClient::HttpClientMock> httpClient =
        std::make_shared<StrictMock<common::httpClient::HttpClientMock>>();
    std::unique_ptr<GoogleTranslateApiResponseDeserializerMock> deserializerInit =
        std::make_unique<StrictMock<GoogleTranslateApiResponseDeserializerMock>>();
    GoogleTranslateApiResponseDeserializerMock* deserializer = deserializerInit.get();
    DefaultTranslationService translator{httpClient, std::move(deserializerInit)};
};

TEST_F(DefaultTranslatorTest, whenConnectionFails_shouldThrowConnectionFailedException)
{
    EXPECT_CALL(*httpClient, get(getPayload))
        .WillOnce(Throw(common::httpClient::exceptions::ConnectionFailed{""}));

    ASSERT_THROW(translator.translate(polishText, sourceLanguage, targetLanguage, apiKey),
                 common::httpClient::exceptions::ConnectionFailed);
}

TEST_F(DefaultTranslatorTest, givenInvalidKeyResponseFromTranslationApi_throwInvalidApiKeyException)
{
    EXPECT_CALL(*httpClient, get(getPayload)).WillOnce(Return(failureResponse));

    ASSERT_THROW(translator.translate(polishText, sourceLanguage, targetLanguage, apiKey),
                 exceptions::InvalidApiKey);
}

TEST_F(DefaultTranslatorTest, givenSuccessResponseFromTranslationApi_shouldReturnTranslatedText)
{
    EXPECT_CALL(*httpClient, get(getPayload)).WillOnce(Return(successResponse));
    EXPECT_CALL(*deserializer, deserialize(responseContent)).WillOnce(Return(expectedResult));

    const auto translation = translator.translate(polishText, sourceLanguage, targetLanguage, apiKey);

    ASSERT_EQ(*translation, englishText);
}
