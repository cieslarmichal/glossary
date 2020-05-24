#include "DefaultTranslatorConnectionChecker.h"

#include "gtest/gtest.h"

#include "translator/TranslatorMock.h"

#include "translator/exceptions/InvalidApiKey.h"
#include "webConnection/exceptions/ConnectionFailed.h"

using namespace ::testing;
using namespace glossary;
using namespace translator;
using namespace translationService;

namespace
{
const std::string examplePolishWord{"okno"};
const auto sourceLanguage = translator::Language::Polish;
const auto targetLanguage = translator::Language::English;
const std::string apiKey{"apiKey"};
const std::string translation{"translation"};
}

class DefaultTranslatorConnectionCheckerTest : public Test
{
public:
    std::shared_ptr<TranslatorMock> translator = std::make_shared<StrictMock<TranslatorMock>>();

    DefaultTranslatorConnectionChecker connectionChecker{translator};
};

TEST_F(DefaultTranslatorConnectionCheckerTest, connectionToTranslatorFailed_shouldReturnConnectionUnavailable)
{
    EXPECT_CALL(*translator, translate(examplePolishWord, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));

    const auto connectionAvailableStatus =
        connectionChecker.connectionToTranslatorWithApiKeyIsAvailable(apiKey);

    ASSERT_EQ(connectionAvailableStatus, TranslationApiStatus::Unavailable);
}

TEST_F(DefaultTranslatorConnectionCheckerTest, givenInvalidTranslatorApiKey_shouldReturnInvalidApiKey)
{
    EXPECT_CALL(*translator, translate(examplePolishWord, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Throw(translator::exceptions::InvalidApiKey{""}));

    const auto connectionAvailableStatus =
        connectionChecker.connectionToTranslatorWithApiKeyIsAvailable(apiKey);

    ASSERT_EQ(connectionAvailableStatus, TranslationApiStatus::InvalidApiKey);
}

TEST_F(DefaultTranslatorConnectionCheckerTest, givenTranslationFromTranslator_shouldReturnTrue)
{
    EXPECT_CALL(*translator, translate(examplePolishWord, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Return(translation));

    const auto connectionAvailableStatus =
        connectionChecker.connectionToTranslatorWithApiKeyIsAvailable(apiKey);

    ASSERT_EQ(connectionAvailableStatus, TranslationApiStatus::Available);
}
