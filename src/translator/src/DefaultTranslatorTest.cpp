#include "DefaultTranslator.h"

#include "gtest/gtest.h"

#include "TranslationDeserializerMock.h"
#include "TranslationRequestFormatterMock.h"
#include "webConnection/HttpHandlerMock.h"

#include "webConnection/exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace glossary::translator;

namespace
{
const webConnection::Request request =
    R"(https://translate.yandex.net/api/v1.5/tr.json/translate?key=trnsl.1.1.20200113T184314Z.f0829944dec57123.a22eb90262e3bd9a179a881dc6960e0a7f142c8d&text=piwo&lang=pl-en)";
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

TEST_F(DefaultTranslatorTest, whenConnectionFails_shouldReturnNone)
{
    EXPECT_CALL(*requestFormatter, getFormattedRequest(polishText, sourceLanguage, targetLanguage))
        .WillOnce(Return(request));
    EXPECT_CALL(*handler, get(request)).WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    const auto translation = translator.translate(polishText, sourceLanguage, targetLanguage);

    ASSERT_EQ(translation, boost::none);
}

TEST_F(DefaultTranslatorTest, givenFailureResponseFromTranslationApi_shouldReturnNone)
{
    EXPECT_CALL(*requestFormatter, getFormattedRequest(polishText, sourceLanguage, targetLanguage))
        .WillOnce(Return(request));
    EXPECT_CALL(*handler, get(request)).WillOnce(Return(failureResponse));

    const auto translation = translator.translate(polishText, sourceLanguage, targetLanguage);

    ASSERT_EQ(translation, boost::none);
}

TEST_F(DefaultTranslatorTest, givenSuccessResponseFromTranslationApi_shouldReturnTranslatedText)
{
    EXPECT_CALL(*requestFormatter, getFormattedRequest(polishText, sourceLanguage, targetLanguage))
        .WillOnce(Return(request));
    EXPECT_CALL(*handler, get(request)).WillOnce(Return(successResponse));
    EXPECT_CALL(*deserializer, deserialize(responseContent)).WillOnce(Return(englishText));

    const auto translation = translator.translate(polishText, sourceLanguage, targetLanguage);

    ASSERT_EQ(*translation, englishText);
}
