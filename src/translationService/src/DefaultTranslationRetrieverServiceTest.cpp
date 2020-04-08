#include "DefaultTranslationRetrieverService.h"

#include "gtest/gtest.h"

#include "translationRepository/TranslationRepositoryMock.h"
#include "translator/TranslatorMock.h"

using namespace ::testing;
using namespace glossary;
using namespace translator;
using namespace translationRepository;
using namespace translationService;

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

class DefaultTranslationRetrieverServiceTest : public Test
{
public:
    std::unique_ptr<translator::TranslatorMock> translatorInit =
        std::make_unique<StrictMock<translator::TranslatorMock>>();
    translator::TranslatorMock* translator = translatorInit.get();
    std::shared_ptr<translationRepository::TranslationRepositoryMock> translationRepository =
        std::make_shared<StrictMock<translationRepository::TranslationRepositoryMock>>();
    DefaultTranslationRetrieverService translationService{std::move(translatorInit), translationRepository};
};

TEST_F(DefaultTranslationRetrieverServiceTest, dbContainsTranslation_shouldReturnTranslationFromDb)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate)).WillOnce(Return(translationFromDb));

    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(DefaultTranslationRetrieverServiceTest,
       dbDoesNotContainTranslation_shouldReturnTranslationFromTranslatorAndSaveTranslationInDatabase)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate)).WillOnce(Return(boost::none));
    EXPECT_CALL(*translator, translate(textToTranslate, sourceLanguage, targetLanguage))
        .WillOnce(Return(translatedTextOpt));
    EXPECT_CALL(*translationRepository, addTranslation(dbTranslation));

    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(DefaultTranslationRetrieverServiceTest, dbAndTranslatorDoNotRespondWithTranslation_shouldReturnNone)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate)).WillOnce(Return(boost::none));
    EXPECT_CALL(*translator, translate(textToTranslate, sourceLanguage, targetLanguage))
        .WillOnce(Return(boost::none));
    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(actualTranslation, boost::none);
}
