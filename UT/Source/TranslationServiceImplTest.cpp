#include "TranslationServiceImpl.h"

#include "gmock/gmock.h"
#include "translation/TranslatorMock.h"
#include "wordsDb/translationsDb/TranslationsDbMock.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace translation;
using namespace wordsDb::translationsDb;

namespace
{
const PolishWord polishWord{"herbata"};
const EnglishWord englishWord{"tea"};
const boost::optional<Translation> translationFromDb{
    Translation{polishWord, englishWord}};
const auto textToTranslate{"herbata"};
const TranslatedText expectedTranslatedText{"tea"};
const boost::optional<TranslatedText> translatedTextOpt{expectedTranslatedText};
const auto sourceLanguage = SourceLanguage::Polish;
const auto targetLanguage = TargetLanguage::English;
}

class TranslationServiceImplTest : public Test
{
public:
    std::unique_ptr<translation::TranslatorMock> translatorInit =
        std::make_unique<StrictMock<translation::TranslatorMock>>();
    translation::TranslatorMock* translator = translatorInit.get();
    std::shared_ptr<wordsDb::translationsDb::TranslationsDbMock>
        translationsDb = std::make_shared<
            StrictMock<wordsDb::translationsDb::TranslationsDbMock>>();
    TranslationServiceImpl translationService{std::move(translatorInit),
                                              translationsDb};
};

TEST_F(TranslationServiceImplTest,
       dbContainsTranslation_shouldReturnTranslationFromDb)
{
    EXPECT_CALL(*translationsDb, getTranslation(textToTranslate))
        .WillOnce(Return(translationFromDb));

    const auto actualTranslation = translationService.translate(
        textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(TranslationServiceImplTest,
       dbDoesNotContainTranslation_shouldReturnTranslationTranslator)
{
    EXPECT_CALL(*translationsDb, getTranslation(textToTranslate))
        .WillOnce(Return(boost::none));
    EXPECT_CALL(*translator,
                translate(textToTranslate, sourceLanguage, targetLanguage))
        .WillOnce(Return(translatedTextOpt));

    const auto actualTranslation = translationService.translate(
        textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}
