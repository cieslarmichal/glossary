#include "DefaultGlossary.h"

#include "gtest/gtest.h"

#include "AnswerValidatorMock.h"
#include "ConnectionCheckerMock.h"
#include "DictionaryTranslationUpdaterMock.h"
#include "GlossaryMock.h"
#include "dictionaryService/DictionaryServiceMock.h"
#include "statisticsRepository/StatisticsRepositoryMock.h"
#include "translationService/TranslationRetrieverServiceMock.h"
#include "wordDescriptionService/WordDescriptionRetrieverServiceMock.h"

using namespace ::testing;
using namespace glossary;
using namespace dictionaryService;
using namespace translationService;
using namespace statisticsRepository;
using namespace wordDescriptionService;
using namespace wordDescriptionRepository;

namespace
{
const std::vector<std::string> supportedLanguages{"Polish", "English"};
const std::string invalidSourceLanguage{"invalidSourceLanguage"};
const std::string invalidTargetLanguage{"invalidTargetLanguage"};
const std::string validSourceLanguage{"validSourceLanguage"};
const std::string validTargetLanguage{"validTargetLanguage"};
const std::string polishLanguageString{"Polish"};
const std::string englishLanguageString{"English"};
const auto polishLanguage = translator::Language::Polish;
const auto englishLanguage = translator::Language::English;
const std::string textToTranslate{"textToTranslate"};
const std::string translatedText{"translatedText"};
const DictionaryName dictionaryName1{"dictionary1"};
const DictionaryName dictionaryName2{"dictionary2"};
const DictionaryNames dictionaryNames{dictionaryName1, dictionaryName2};
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string polishWord{"polishWord"};
const std::string wordTranslation{"wordTranslation"};
const std::string inputTranslation{"inputTranslation"};
const std::string pathToDictionaryWords{"/home/words.txt"};
const DictionaryWord dictionaryWordWithoutTranslation{englishWord1, boost::none};
const DictionaryWord dictionaryWordWithTranslation{englishWord2, wordTranslation};
const DictionaryWords dictionaryWords{dictionaryWordWithoutTranslation, dictionaryWordWithTranslation};
const Definitions definitions{"definition1", "definition2"};
const Examples examples{"example1", "example2"};
const Synonyms synonyms{"synonym1", "synonym2", "synonym1000000"};
const WordDescription wordDescription{EnglishWord{"computer"}, definitions, examples, synonyms};
const WordStatistics statisticsPerWord1{EnglishWord{"cat"}, 7, 0};
const WordStatistics statisticsPerWord2{EnglishWord{"dog"}, 2, 1};
const Statistics statistics{statisticsPerWord1, statisticsPerWord2};
auto availableStatus =
    ExternalServicesStatus{WordsApiStatus::Available, TranslationApiStatus::Available};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", boost::none};
const DictionaryWords dictionaryWords1{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const DictionaryWords dictionaryWords2{dictionaryWord1, dictionaryWord2};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionaries dictionaries{dictionary1, dictionary2};
}

class DefaultGlossaryTest_Base : public Test
{
public:
    DefaultGlossaryTest_Base()
    {
        EXPECT_CALL(*dictionaryService, synchronizeDictionaries());
    }

    std::shared_ptr<DictionaryServiceMock> dictionaryService =
        std::make_shared<StrictMock<DictionaryServiceMock>>();
    std::shared_ptr<TranslationRetrieverServiceMock> translationService =
        std::make_shared<StrictMock<TranslationRetrieverServiceMock>>();
    std::shared_ptr<StatisticsRepositoryMock> statisticsRepository =
        std::make_shared<StrictMock<StatisticsRepositoryMock>>();
    std::shared_ptr<WordDescriptionRetrieverServiceMock> wordDescriptionService =
        std::make_shared<StrictMock<WordDescriptionRetrieverServiceMock>>();
    std::shared_ptr<DictionaryTranslationUpdaterMock> dictionaryTranslationUpdater =
        std::make_shared<StrictMock<DictionaryTranslationUpdaterMock>>();
    std::unique_ptr<ConnectionCheckerMock> externalServicesConnectionCheckerInit =
        std::make_unique<StrictMock<ConnectionCheckerMock>>();
    ConnectionCheckerMock* externalServicesConnectionChecker =
        externalServicesConnectionCheckerInit.get();
    std::unique_ptr<AnswerValidatorMock> answerValidatorInit =
        std::make_unique<StrictMock<AnswerValidatorMock>>();
    AnswerValidatorMock* answerValidator = answerValidatorInit.get();
};

class DefaultGlossaryTest : public DefaultGlossaryTest_Base
{
public:
    DefaultGlossary glossary{dictionaryService,
                             translationService,
                             statisticsRepository,
                             wordDescriptionService,
                             dictionaryTranslationUpdater,
                             {},
                             std::move(externalServicesConnectionCheckerInit),
                             std::move(answerValidatorInit)};
};

TEST_F(DefaultGlossaryTest, shouldReturnExternalServicesAvailabilityStatus)
{
    EXPECT_CALL(*externalServicesConnectionChecker, checkExternalServicesAvailabilityStatus())
        .WillOnce(Return(availableStatus));

    const auto actualAvailabilityStatus = glossary.checkConnectionToExternalServices();

    ASSERT_EQ(actualAvailabilityStatus, availableStatus);
}

TEST_F(DefaultGlossaryTest, givenNoneRandomDictionaryWord_shouldReturnNone)
{
    EXPECT_CALL(*dictionaryService, getRandomDictionaryWord()).WillOnce(Return(boost::none));

    const auto actualPolishWord = glossary.getRandomPolishWord();

    ASSERT_EQ(actualPolishWord, boost::none);
}

TEST_F(DefaultGlossaryTest,
       givenRandomDictionaryWordWithoutTranslation_shouldReturnTranslationFromTranslationService)
{
    EXPECT_CALL(*dictionaryService, getRandomDictionaryWord())
        .WillOnce(Return(dictionaryWordWithoutTranslation));
    EXPECT_CALL(*translationService, retrieveTranslation(dictionaryWordWithoutTranslation.englishWord,
                                                         englishLanguage, polishLanguage))
        .WillOnce(Return(polishWord));

    const auto actualPolishWord = glossary.getRandomPolishWord();

    ASSERT_EQ(*actualPolishWord, polishWord);
}

TEST_F(DefaultGlossaryTest, givenRandomDictionaryWordWithTranslation_shouldReturnWordTranslation)
{
    EXPECT_CALL(*dictionaryService, getRandomDictionaryWord())
        .WillOnce(Return(dictionaryWordWithTranslation));

    const auto actualPolishWord = glossary.getRandomPolishWord();

    ASSERT_EQ(*actualPolishWord, *dictionaryWordWithTranslation.translation);
}

TEST_F(DefaultGlossaryTest, givenNoneRandomDictionaryWordFromSpecificDictionary_shouldReturnNone)
{
    EXPECT_CALL(*dictionaryService, getRandomDictionaryWord(dictionaryName1)).WillOnce(Return(boost::none));

    const auto actualPolishWord = glossary.getRandomPolishWord(dictionaryName1);

    ASSERT_EQ(actualPolishWord, boost::none);
}

TEST_F(
    DefaultGlossaryTest,
    givenRandomDictionaryWordFromSpecificDictionaryWithoutTranslation_shouldReturnTranslationFromTranslationService)
{
    EXPECT_CALL(*dictionaryService, getRandomDictionaryWord(dictionaryName1))
        .WillOnce(Return(dictionaryWordWithoutTranslation));
    EXPECT_CALL(*translationService, retrieveTranslation(dictionaryWordWithoutTranslation.englishWord,
                                                         englishLanguage, polishLanguage))
        .WillOnce(Return(polishWord));

    const auto actualPolishWord = glossary.getRandomPolishWord(dictionaryName1);

    ASSERT_EQ(*actualPolishWord, polishWord);
}

TEST_F(DefaultGlossaryTest,
       givenRandomDictionaryWordFromSpecificDictionaryWithTranslation_shouldReturnWordTranslation)
{
    EXPECT_CALL(*dictionaryService, getRandomDictionaryWord(dictionaryName1))
        .WillOnce(Return(dictionaryWordWithTranslation));

    const auto actualPolishWord = glossary.getRandomPolishWord(dictionaryName1);

    ASSERT_EQ(*actualPolishWord, *dictionaryWordWithTranslation.translation);
}

TEST_F(DefaultGlossaryTest, givenCorrectPolishWordsTranslation_shouldAddCorrectAnswerAndReturnTrue)
{
    EXPECT_CALL(*translationService, retrieveTranslation(polishWord, polishLanguage, englishLanguage))
        .WillOnce(Return(wordTranslation));
    EXPECT_CALL(*answerValidator, validateAnswer(wordTranslation, englishWord1)).WillOnce(Return(true));
    EXPECT_CALL(*statisticsRepository, addCorrectAnswer(englishWord1));

    const auto verificationResult = glossary.verifyPolishWordTranslation(polishWord, englishWord1);

    ASSERT_TRUE(verificationResult);
}

TEST_F(DefaultGlossaryTest, givenIncorrectPolishWordsTranslation_shouldAddIncorrectAnswerAndReturnFalse)
{
    EXPECT_CALL(*translationService, retrieveTranslation(polishWord, polishLanguage, englishLanguage))
        .WillOnce(Return(wordTranslation));
    EXPECT_CALL(*answerValidator, validateAnswer(wordTranslation, englishWord1)).WillOnce(Return(false));
    EXPECT_CALL(*statisticsRepository, addIncorrectAnswer(englishWord1));

    const auto verificationResult = glossary.verifyPolishWordTranslation(polishWord, englishWord1);

    ASSERT_FALSE(verificationResult);
}

TEST_F(DefaultGlossaryTest, givenNoneTranslationFromTranslationService_shouldNotModifyAnswersAndReturnFalse)
{
    EXPECT_CALL(*translationService, retrieveTranslation(polishWord, polishLanguage, englishLanguage))
        .WillOnce(Return(boost::none));

    const auto verificationResult = glossary.verifyPolishWordTranslation(polishWord, englishWord1);

    ASSERT_FALSE(verificationResult);
}

TEST_F(DefaultGlossaryTest, shouldReturnDictionaries)
{
    EXPECT_CALL(*dictionaryService, getDictionaries).WillOnce(Return(dictionaries));

    const auto actualDictionaries= glossary.getDictionaries();

    ASSERT_EQ(actualDictionaries, dictionaries);
}

TEST_F(DefaultGlossaryTest, shouldReturnNamesOfDictionaries)
{
    EXPECT_CALL(*dictionaryService, getDictionaryNames()).WillOnce(Return(dictionaryNames));

    const auto actualNamesOfDictionaries = glossary.getDictionariesNames();

    ASSERT_EQ(actualNamesOfDictionaries, dictionaryNames);
}

TEST_F(DefaultGlossaryTest, givenNoneDictionaryWords_shouldReturnEmptyDictionaryWords)
{
    EXPECT_CALL(*dictionaryService, getDictionaryWords(dictionaryName1)).WillOnce(Return(boost::none));

    const auto actualDictionaryWords = glossary.getDictionaryWords(dictionaryName1);

    ASSERT_TRUE(actualDictionaryWords.empty());
}

TEST_F(DefaultGlossaryTest, givenDictionaryWords_shouldReturnDictionaryWords)
{
    EXPECT_CALL(*dictionaryService, getDictionaryWords(dictionaryName1)).WillOnce(Return(dictionaryWords));

    const auto actualDictionaryWords = glossary.getDictionaryWords(dictionaryName1);

    ASSERT_EQ(actualDictionaryWords, dictionaryWords);
}

TEST_F(DefaultGlossaryTest, shouldAddDictionaryByName)
{
    EXPECT_CALL(*dictionaryService, addDictionary(dictionaryName1));

    glossary.addDictionary(dictionaryName1);
}

TEST_F(DefaultGlossaryTest, shouldRemoveDictionaryByName)
{
    EXPECT_CALL(*dictionaryService, removeDictionary(dictionaryName1));

    glossary.removeDictionary(dictionaryName1);
}

TEST_F(DefaultGlossaryTest, shouldAddDictionaryWordToDictionary)
{
    EXPECT_CALL(*dictionaryService, addWordToDictionary(dictionaryWordWithTranslation, dictionaryName1));

    glossary.addEnglishWordToDictionary(englishWord2, wordTranslation, dictionaryName1);
}

TEST_F(DefaultGlossaryTest, shouldRemoveDictionaryWordFromDictionary)
{
    EXPECT_CALL(*dictionaryService, removeWordFromDictionary(englishWord1, dictionaryName1));

    glossary.removeEnglishWordFromDictionary(englishWord1, dictionaryName1);
}

TEST_F(DefaultGlossaryTest, shouldAddDictionaryFromFile)
{
    EXPECT_CALL(*dictionaryService, addDictionaryFromFile(dictionaryName1, pathToDictionaryWords));

    glossary.addDictionaryFromFile(dictionaryName1, pathToDictionaryWords);
}

TEST_F(DefaultGlossaryTest, shouldUpdateDictionaryWordTranslationByInput)
{
    EXPECT_CALL(*dictionaryTranslationUpdater,
                updateDictionaryWordTranslation(englishWord2, inputTranslation, dictionaryName1));

    glossary.updateDictionaryWordTranslationManually(dictionaryName1, englishWord2, inputTranslation);
}

TEST_F(DefaultGlossaryTest, shouldUpdateDictionaryWordTranslationAutomatically)
{
    EXPECT_CALL(*dictionaryTranslationUpdater,
                updateDictionaryWordTranslation(englishWord2, dictionaryName1));

    glossary.updateDictionaryWordTranslationAutomatically(dictionaryName1, englishWord2);
}

TEST_F(DefaultGlossaryTest, shouldUpdateDictionaryTranslationsAutomatically)
{
    EXPECT_CALL(*dictionaryTranslationUpdater, updateDictionaryTranslations(dictionaryName1));

    glossary.updateDictionaryTranslationsAutomatically(dictionaryName1);
}

TEST_F(DefaultGlossaryTest, shouldReturnSupportedLanguagesFromTranslationService)
{
    EXPECT_CALL(*translationService, retrieveSupportedLanguages()).WillOnce(Return(supportedLanguages));

    const auto actualSupportedLanguages = glossary.getSupportedTranslatorLanguages();

    ASSERT_EQ(actualSupportedLanguages, supportedLanguages);
}

TEST_F(DefaultGlossaryTest, givenIncorrectSourceLanguage_shouldReturnNone)
{
    EXPECT_CALL(*answerValidator, validateAnswer(invalidSourceLanguage, polishLanguageString))
        .WillOnce(Return(false));
    EXPECT_CALL(*answerValidator, validateAnswer(invalidSourceLanguage, englishLanguageString))
        .WillOnce(Return(false));

    const auto actualTranslation =
        glossary.translate(textToTranslate, invalidSourceLanguage, validTargetLanguage);

    ASSERT_EQ(actualTranslation, boost::none);
}

TEST_F(DefaultGlossaryTest, givenIncorrectTargetLanguage_shouldReturnNone)
{
    EXPECT_CALL(*answerValidator, validateAnswer(validSourceLanguage, polishLanguageString))
        .WillOnce(Return(true));
    EXPECT_CALL(*answerValidator, validateAnswer(invalidTargetLanguage, polishLanguageString))
        .WillOnce(Return(false));
    EXPECT_CALL(*answerValidator, validateAnswer(invalidTargetLanguage, englishLanguageString))
        .WillOnce(Return(false));

    const auto actualTranslation =
        glossary.translate(textToTranslate, validSourceLanguage, invalidTargetLanguage);

    ASSERT_EQ(actualTranslation, boost::none);
}

TEST_F(DefaultGlossaryTest, givenTranslationFromTranslationService_shouldReturnTranslation)
{
    EXPECT_CALL(*answerValidator, validateAnswer(validSourceLanguage, polishLanguageString))
        .WillOnce(Return(true));
    EXPECT_CALL(*answerValidator, validateAnswer(validTargetLanguage, polishLanguageString))
        .WillOnce(Return(false));
    EXPECT_CALL(*answerValidator, validateAnswer(validTargetLanguage, englishLanguageString))
        .WillOnce(Return(true));
    EXPECT_CALL(*translationService, retrieveTranslation(textToTranslate, polishLanguage, englishLanguage))
        .WillOnce(Return(translatedText));

    const auto actualTranslation =
        glossary.translate(textToTranslate, validSourceLanguage, validTargetLanguage);

    ASSERT_EQ(*actualTranslation, translatedText);
}

TEST_F(DefaultGlossaryTest, shouldReturnWordDescription)
{
    EXPECT_CALL(*wordDescriptionService, retrieveWordDescription(englishWord1))
        .WillOnce(Return(wordDescription));

    const auto actualWordDescription = glossary.getEnglishWordDescription(englishWord1);

    ASSERT_EQ(actualWordDescription, wordDescription);
}

TEST_F(DefaultGlossaryTest, shouldReturnStatistics)
{
    EXPECT_CALL(*statisticsRepository, getStatistics()).WillOnce(Return(statistics));

    const auto actualStatistics = glossary.getStatistics();

    ASSERT_EQ(actualStatistics, statistics);
}

TEST_F(DefaultGlossaryTest, shouldResetStatistics)
{
    EXPECT_CALL(*statisticsRepository, resetStatistics());

    glossary.resetStatistics();
}
