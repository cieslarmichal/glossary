#include "DefaultTranslatorConnectionChecker.h"

#include "gtest/gtest.h"

#include "translator/TranslatorMock.h"

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

TEST_F(DefaultTranslatorConnectionCheckerTest, givenNoneTranslationFromTranslator_shouldReturnFalse)
{
    EXPECT_CALL(*translator, translate(examplePolishWord, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Return(boost::none));

    const auto connectionAvailable = connectionChecker.connectionToTranslatorWithApiKeyIsAvailable(apiKey);

    ASSERT_FALSE(connectionAvailable);
}

TEST_F(DefaultTranslatorConnectionCheckerTest, givenTranslationFromTranslator_shouldReturnTrue)
{
    EXPECT_CALL(*translator, translate(examplePolishWord, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Return(translation));

    const auto connectionAvailable = connectionChecker.connectionToTranslatorWithApiKeyIsAvailable(apiKey);

    ASSERT_TRUE(connectionAvailable);
}
