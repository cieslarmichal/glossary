#include "translation/TranslatorImpl.h"

#include "translation/TranslationDeserializerMock.h"
#include "translation/TranslationRequestFormatterMock.h"
#include "webConnection/HttpRequestHandlerMock.h"

#include "exceptions/ConnectionFailed.h"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace translation;

namespace
{
const webConnection::Request request =
    R"(https://translate.yandex.net/api/v1.5/tr.json/translate?key=trnsl.1.1.20200113T184314Z.f0829944dec57123.a22eb90262e3bd9a179a881dc6960e0a7f142c8d&text=piwo&lang=pl-en)";
const auto responseContent = R"({"code":200,"lang":"pl-en","text":["beer"]})";
const webConnection::Response successResponse{200, responseContent};
const webConnection::Response failureResponse{400, ""};
const auto polishText = "piwo";
const auto englishText = "beer";
}

class TranslatorImplTest : public Test
{
public:
    std::shared_ptr<webConnection::HttpRequestHandlerMock> handler =
        std::make_shared<webConnection::HttpRequestHandlerMock>();
    std::unique_ptr<TranslationDeserializerMock> deserializerInit =
        std::make_unique<StrictMock<TranslationDeserializerMock>>();
    TranslationDeserializerMock* deserializer = deserializerInit.get();
    std::unique_ptr<TranslationRequestFormatterMock> requestFormatterInit =
        std::make_unique<StrictMock<TranslationRequestFormatterMock>>();
    TranslationRequestFormatterMock* requestFormatter =
        requestFormatterInit.get();
    TranslatorImpl translator{handler, std::move(deserializerInit),
                              std::move(requestFormatterInit)};
};

TEST_F(TranslatorImplTest, whenConnectionFails_shouldReturnNone)
{
    EXPECT_CALL(*requestFormatter,
                getFormattedRequest(polishText, SourceLanguage::Polish,
                                    TargetLanguage::English))
        .WillOnce(Return(request));
    EXPECT_CALL(*handler, get(request))
        .WillOnce(Throw(exceptions::ConnectionFailed{""}));

    const auto translation = translator.translate(
        polishText, SourceLanguage::Polish, TargetLanguage::English);

    ASSERT_EQ(translation, boost::none);
}

TEST_F(TranslatorImplTest,
       givenFailureResponseFromTranslationApi_shouldReturnNone)
{
    EXPECT_CALL(*requestFormatter,
                getFormattedRequest(polishText, SourceLanguage::Polish,
                                    TargetLanguage::English))
        .WillOnce(Return(request));
    EXPECT_CALL(*handler, get(request)).WillOnce(Return(failureResponse));

    const auto translation = translator.translate(
        polishText, SourceLanguage::Polish, TargetLanguage::English);

    ASSERT_EQ(translation, boost::none);
}

TEST_F(TranslatorImplTest,
       givenSuccessResponseFromTranslationApi_shouldReturnTranslatedText)
{
    EXPECT_CALL(*requestFormatter,
                getFormattedRequest(polishText, SourceLanguage::Polish,
                                    TargetLanguage::English))
        .WillOnce(Return(request));
    EXPECT_CALL(*handler, get(request)).WillOnce(Return(successResponse));
    EXPECT_CALL(*deserializer, deserialize(responseContent))
        .WillOnce(Return(englishText));

    const auto translation = translator.translate(
        polishText, SourceLanguage::Polish, TargetLanguage::English);

    ASSERT_EQ(*translation, englishText);
}
