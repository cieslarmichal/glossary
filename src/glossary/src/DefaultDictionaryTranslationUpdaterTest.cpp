#include "DefaultDictionaryTranslationUpdater.h"

#include <boost/optional/optional_io.hpp>

#include "gtest/gtest.h"

#include "dictionaryService/DictionaryServiceMock.h"
#include "translationService/TranslationServiceMock.h"

using namespace ::testing;
using namespace glossary;
using namespace dictionaryService;
using namespace translationService;

namespace
{
const DictionaryName dictionaryName{"dictionaryName"};
const DictionaryName nonExistingDictionaryName{"nonExisting"};
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string translation1{"translation1"};
const DictionaryWord dictionaryWord1{englishWord1, translation1};
const DictionaryWord dictionaryWord2{englishWord2, boost::none};
const DictionaryWords dictionaryWords{dictionaryWord1, dictionaryWord2};
const std::string newDictionaryWordTranslation{"newDictionaryWordTranslation"};
const std::string translationFromService1{"translationFromService1"};
const std::string translationFromService2{"translationFromService2"};
const auto sourceLanguage = translation::SourceLanguage::English;
const auto targetLanguage = translation::TargetLanguage::Polish;
}

class DefaultDictionaryTranslationUpdaterTest : public Test
{
public:
    std::shared_ptr<DictionaryServiceMock> dictionaryService =
        std::make_shared<StrictMock<DictionaryServiceMock>>();
    std::shared_ptr<TranslationServiceMock> translationService =
        std::make_shared<StrictMock<TranslationServiceMock>>();
    DefaultDictionaryTranslationUpdater updater{dictionaryService, translationService};
};

TEST_F(DefaultDictionaryTranslationUpdaterTest, shouldUpdateDictionaryWordTranslationByGivenTranslation)
{
    EXPECT_CALL(*dictionaryService, updateWordTranslationFromDictionary(
                                        englishWord1, newDictionaryWordTranslation, dictionaryName));

    updater.updateDictionaryWordTranslation(englishWord1, newDictionaryWordTranslation, dictionaryName);
}

TEST_F(DefaultDictionaryTranslationUpdaterTest,
       givenNonExistingTranslationInService_shouldNotUpdateDictionaryWordTranslation)
{
    EXPECT_CALL(*translationService, retrieveTranslation(englishWord1, sourceLanguage, targetLanguage))
        .WillOnce(Return(boost::none));

    updater.updateDictionaryWordTranslation(englishWord1, dictionaryName);
}

TEST_F(DefaultDictionaryTranslationUpdaterTest,
       givenExistingTranslationInService_shouldUpdateDictionaryWordTranslationByTranslationService)
{
    EXPECT_CALL(*translationService, retrieveTranslation(englishWord1, sourceLanguage, targetLanguage))
        .WillOnce(Return(translationFromService1));
    EXPECT_CALL(*dictionaryService,
                updateWordTranslationFromDictionary(englishWord1, translationFromService1, dictionaryName));

    updater.updateDictionaryWordTranslation(englishWord1, dictionaryName);
}

TEST_F(DefaultDictionaryTranslationUpdaterTest,
       givenNonExistingDictionaryWordsFromDictionary_shouldNotUpdateDictionaryTranslations)
{
    EXPECT_CALL(*dictionaryService, getDictionaryWords(dictionaryName)).WillOnce(Return(boost::none));

    updater.updateDictionaryTranslations(dictionaryName);
}

TEST_F(
    DefaultDictionaryTranslationUpdaterTest,
    givenExistingDictionaryWordsFromDictionary_shouldUpdateDictionaryTranslationsWithWordsWhichNotHaveTranslations)
{
    EXPECT_CALL(*dictionaryService, getDictionaryWords(dictionaryName)).WillOnce(Return(dictionaryWords));

    EXPECT_CALL(*translationService, retrieveTranslation(englishWord2, sourceLanguage, targetLanguage))
        .WillOnce(Return(translationFromService2));
    EXPECT_CALL(*dictionaryService,
                updateWordTranslationFromDictionary(englishWord2, translationFromService2, dictionaryName));

    updater.updateDictionaryTranslations(dictionaryName);
}
