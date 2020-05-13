#include "DefaultTranslator.h"

#include "gtest/gtest.h"

#include "TranslationDeserializerMock.h"
#include "TranslationRequestFormatterMock.h"
#include "webConnection/HttpHandlerMock.h"

#include "exceptions/InvalidApiKey.h"
#include "webConnection/exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace glossary::translator;

namespace
{
const std::string url{"https://translation.googleapis.com/language/translate/v2?"};
const std::string apiKey = {"topSecretKey"};
const std::string keyField = {"key=" + apiKey};
const auto sourceField = R"(&source=pl)";
const auto targetField = R"(&target=en)";
const webConnection::Request request = url + keyField + "&q=piwo" + sourceField + targetField;
const auto responseContent = R"({"code":200,"lang":"pl-en","text":["beer"]})";
const webConnection::Response successResponse{200, responseContent};
const webConnection::Response failureResponse{400, ""};
const auto polishText = "piwo";
const auto englishText = "beer";
const auto sourceLanguage = SourceLanguage::Polish;
const auto targetLanguage = TargetLanguage::English;
}

class DefaultTranslatorTest : public Test
{
public:
    std::shared_ptr<webConnection::HttpHandlerMock> handler =
        std::make_shared<StrictMock<webConnection::HttpHandlerMock>>();
    std::unique_ptr<TranslationDeserializerMock> deserializerInit =
        std::make_unique<StrictMock<TranslationDeserializerMock>>();
    TranslationDeserializerMock* deserializer = deserializerInit.get();
    std::unique_ptr<TranslationRequestFormatterMock> requestFormatterInit =
        std::make_unique<StrictMock<TranslationRequestFormatterMock>>();
    TranslationRequestFormatterMock* requestFormatter = requestFormatterInit.get();
    DefaultTranslator translator{handler, std::move(deserializerInit), std::move(requestFormatterInit)};
};

TEST_F(DefaultTranslatorTest, whenConnectionFails_shouldThrowConnectionFailedException)
{
    EXPECT_CALL(*requestFormatter, getFormattedRequest(polishText, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Return(request));
    EXPECT_CALL(*handler, get(request)).WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    ASSERT_THROW(translator.translate(polishText, sourceLanguage, targetLanguage, apiKey),
                 webConnection::exceptions::ConnectionFailed);
}

TEST_F(DefaultTranslatorTest, givenInvalidKeyResponseFromTranslationApi_throwInvalidApiKeyException)
{
    EXPECT_CALL(*requestFormatter, getFormattedRequest(polishText, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Return(request));
    EXPECT_CALL(*handler, get(request)).WillOnce(Return(failureResponse));

    ASSERT_THROW(translator.translate(polishText, sourceLanguage, targetLanguage, apiKey),
                 exceptions::InvalidApiKey);
}

TEST_F(DefaultTranslatorTest, givenSuccessResponseFromTranslationApi_shouldReturnTranslatedText)
{
    EXPECT_CALL(*requestFormatter, getFormattedRequest(polishText, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Return(request));
    EXPECT_CALL(*handler, get(request)).WillOnce(Return(successResponse));
    EXPECT_CALL(*deserializer, deserialize(responseContent)).WillOnce(Return(englishText));

    const auto translation = translator.translate(polishText, sourceLanguage, targetLanguage, apiKey);

    ASSERT_EQ(*translation, englishText);
}
