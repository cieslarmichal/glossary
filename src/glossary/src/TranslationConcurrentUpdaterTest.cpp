#include "TranslationConcurrentUpdater.h"

#include "gtest/gtest.h"

#include "TranslationRepositoryMock.h"
#include "TranslationServiceMock.h"

using namespace ::testing;
using namespace glossary;
using namespace translationService;
using namespace translationRepository;
using namespace dictionary;
using namespace translator;

namespace
{
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string englishWord3{"englishWord3"};
const TranslatedText translatedText1{"translation1"};
const TranslatedText translatedText3{"translation3"};
const std::vector<std::string> englishWords{englishWord1, englishWord2, englishWord3};
const Translation translation1{englishWord1, translatedText1};
const Translation translation3{englishWord3, translatedText3};
const SourceLanguage sourceLanguage = Language::English;
const TargetLanguage targetLanguage = Language::Polish;
}

class TranslationConcurrentUpdaterTest : public Test
{
public:
    std::shared_ptr<TranslationServiceMock> translationService =
        std::make_shared<StrictMock<TranslationServiceMock>>();
    std::shared_ptr<TranslationRepositoryMock> translationRepository =
        std::make_shared<StrictMock<TranslationRepositoryMock>>();
    TranslationConcurrentUpdater updater{translationService, translationRepository};
};

TEST_F(TranslationConcurrentUpdaterTest, givenEnglishWordsExistingInRepository_shouldNotLoadAnything)
{
    EXPECT_CALL(*translationRepository, containsTranslation(englishWord1)).WillOnce(Return(true));
    EXPECT_CALL(*translationRepository, containsTranslation(englishWord2)).WillOnce(Return(true));
    EXPECT_CALL(*translationRepository, containsTranslation(englishWord3)).WillOnce(Return(true));

    updater.update(englishWords);
}

TEST_F(TranslationConcurrentUpdaterTest,
       givenEnglishWordsNonExistingInRepository_shouldLoadTranslationsFromTranslationService)
{
    EXPECT_CALL(*translationRepository, containsTranslation(englishWord1)).WillOnce(Return(false));
    EXPECT_CALL(*translationRepository, containsTranslation(englishWord2)).WillOnce(Return(false));
    EXPECT_CALL(*translationRepository, containsTranslation(englishWord3)).WillOnce(Return(false));

    EXPECT_CALL(*translationService, retrieveTranslation(englishWord1, sourceLanguage, targetLanguage))
        .WillOnce(Return(translatedText1));
    EXPECT_CALL(*translationService, retrieveTranslation(englishWord2, sourceLanguage, targetLanguage))
        .WillOnce(Return(std::nullopt));
    EXPECT_CALL(*translationService, retrieveTranslation(englishWord3, sourceLanguage, targetLanguage))
        .WillOnce(Return(translatedText3));

    updater.update(englishWords);
}
