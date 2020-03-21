#include "DefaultTranslationService.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "translationsDb/TranslationsDbMock.h"
#include "translator/TranslatorMock.h"

using namespace ::testing;
using namespace translator;
using namespace translationsDb;

namespace
{
const SourceText polishWord{"herbata"};
const TranslatedText englishWord{"tea"};
const Translation dbTranslation{polishWord, englishWord};
const boost::optional<Translation> translationFromDb{dbTranslation};
const auto textToTranslate{"herbata"};
const TranslatedText expectedTranslatedText{"tea"};
const boost::optional<TranslatedText> translatedTextOpt{expectedTranslatedText};
const auto sourceLanguage = SourceLanguage::Polish;
const auto targetLanguage = TargetLanguage::English;
}

class DefaultTranslationServiceTest : public Test
{
public:
    std::unique_ptr<translator::TranslatorMock> translatorInit =
        std::make_unique<StrictMock<translator::TranslatorMock>>();
    translator::TranslatorMock* translator = translatorInit.get();
    std::shared_ptr<translationsDb::TranslationsDbMock> translationsDb =
        std::make_shared<StrictMock<translationsDb::TranslationsDbMock>>();
    DefaultTranslationService translationService{std::move(translatorInit), translationsDb};
};

TEST_F(DefaultTranslationServiceTest, dbContainsTranslation_shouldReturnTranslationFromDb)
{
    EXPECT_CALL(*translationsDb, getTranslation(textToTranslate)).WillOnce(Return(translationFromDb));

    const auto actualTranslation =
        translationService.translate(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(DefaultTranslationServiceTest,
       dbDoesNotContainTranslation_shouldReturnTranslationFromTranslatorAndSaveTranslationInDatabase)
{
    EXPECT_CALL(*translationsDb, getTranslation(textToTranslate)).WillOnce(Return(boost::none));
    EXPECT_CALL(*translator, translate(textToTranslate, sourceLanguage, targetLanguage))
        .WillOnce(Return(translatedTextOpt));
    EXPECT_CALL(*translationsDb, addTranslation(dbTranslation));

    const auto actualTranslation =
        translationService.translate(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(DefaultTranslationServiceTest, dbAndTranslatorDoNotRespondWithTranslation_shouldReturnNone)
{
    EXPECT_CALL(*translationsDb, getTranslation(textToTranslate)).WillOnce(Return(boost::none));
    EXPECT_CALL(*translator, translate(textToTranslate, sourceLanguage, targetLanguage))
        .WillOnce(Return(boost::none));
    const auto actualTranslation =
        translationService.translate(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(actualTranslation, boost::none);
}
