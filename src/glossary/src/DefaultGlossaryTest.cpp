#include "DefaultGlossary.h"

#include "gtest/gtest.h"

#include "AnswerValidatorMock.h"
#include "ConnectionCheckerMock.h"
#include "DictionaryTranslationUpdaterMock.h"
#include "UserPromptMock.h"
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
const std::vector<std::string> dictionaryWordsAsString{toString(dictionaryWordWithoutTranslation),
                                                       toString(dictionaryWordWithTranslation)};
const DefinitionWithExample definitionWithExample1{"definition1", std::string{"example1"}};
const DefinitionWithExample definitionWithExample2{"definition2", std::string{"example2"}};
const DefinitionsWithExamples definitionsWithExamples{definitionWithExample1, definitionWithExample2};
const WordDescription wordDescription{EnglishWord{"computer"},
                                      Description{definitionsWithExamples, Sentences{"sentence"}}};
const WordStatistics statisticsPerWord1{EnglishWord{"cat"}, 7, 0};
const WordStatistics statisticsPerWord2{EnglishWord{"dog"}, 2, 1};
const Statistics statistics{statisticsPerWord1, statisticsPerWord2};
const std::vector<std::string> statisticsAsString{toString(statisticsPerWord1), toString(statisticsPerWord2)};
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
    std::unique_ptr<ConnectionCheckerMock> connectionCheckerInit =
        std::make_unique<StrictMock<ConnectionCheckerMock>>();
    ConnectionCheckerMock* connectionChecker = connectionCheckerInit.get();
    std::unique_ptr<AnswerValidatorMock> answerValidatorInit =
        std::make_unique<StrictMock<AnswerValidatorMock>>();
    AnswerValidatorMock* answerValidator = answerValidatorInit.get();
    std::unique_ptr<UserPromptMock> userPromptInit = std::make_unique<StrictMock<UserPromptMock>>();
    UserPromptMock* userPrompt = userPromptInit.get();
};

class DefaultGlossaryTest : public DefaultGlossaryTest_Base
{
public:
    void expectUserInputNumber(int userInput)
    {
        EXPECT_CALL(*userPrompt, getNumberInput()).WillOnce(Return(userInput));
    }

    void expectUserInputString(const std::string& userInput1)
    {
        EXPECT_CALL(*userPrompt, getStringInput()).WillOnce(Return(userInput1));
    }

    void expectUserInputTwoString(const std::string& userInput1, const std::string& userInput2)
    {
        EXPECT_CALL(*userPrompt, getStringInput()).WillOnce(Return(userInput1)).WillOnce(Return(userInput2));
    }

    void expectUserInputThreeString(const std::string& userInput1, const std::string& userInput2,
                                    const std::string& userInput3)
    {
        EXPECT_CALL(*userPrompt, getStringInput())
            .WillOnce(Return(userInput1))
            .WillOnce(Return(userInput2))
            .WillOnce(Return(userInput3));
    }

    DefaultGlossary glossary{dictionaryService,
                             translationService,
                             statisticsRepository,
                             wordDescriptionService,
                             dictionaryTranslationUpdater,
                             {},
                             std::move(connectionCheckerInit),
                             std::move(answerValidatorInit),
                             std::move(userPromptInit)};
};

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

TEST_F(DefaultGlossaryTest, givenInorrectPolishWordsTranslation_shouldAddIncorrectAnswerAndReturnFalse)
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

TEST_F(DefaultGlossaryTest, givenIncorrectSourceLanguage_shouldReturnNone)
{
    EXPECT_CALL(*translationService, retrieveSupportedLanguages()).WillOnce(Return(supportedLanguages));
    expectUserInputTwoString(textToTranslate, invalidSourceLanguage);
    EXPECT_CALL(*answerValidator, validateAnswer(invalidSourceLanguage, polishLanguageString))
        .WillOnce(Return(false));
    EXPECT_CALL(*answerValidator, validateAnswer(invalidSourceLanguage, englishLanguageString))
        .WillOnce(Return(false));

    const auto actualTranslation = glossary.translate();

    ASSERT_EQ(actualTranslation, boost::none);
}

TEST_F(DefaultGlossaryTest, givenIncorrectTargetLanguage_shouldReturnNone)
{
    EXPECT_CALL(*translationService, retrieveSupportedLanguages()).WillOnce(Return(supportedLanguages));
    expectUserInputThreeString(textToTranslate, validSourceLanguage, invalidTargetLanguage);
    EXPECT_CALL(*answerValidator, validateAnswer(validSourceLanguage, polishLanguageString))
        .WillOnce(Return(true));
    EXPECT_CALL(*answerValidator, validateAnswer(invalidTargetLanguage, polishLanguageString))
        .WillOnce(Return(false));
    EXPECT_CALL(*answerValidator, validateAnswer(invalidTargetLanguage, englishLanguageString))
        .WillOnce(Return(false));

    const auto actualTranslation = glossary.translate();

    ASSERT_EQ(actualTranslation, boost::none);
}

TEST_F(DefaultGlossaryTest, givenTranslationFromTranslationService_shouldReturnTranslation)
{
    EXPECT_CALL(*translationService, retrieveSupportedLanguages()).WillOnce(Return(supportedLanguages));
    expectUserInputThreeString(textToTranslate, validSourceLanguage, validTargetLanguage);
    EXPECT_CALL(*answerValidator, validateAnswer(validSourceLanguage, polishLanguageString))
        .WillOnce(Return(true));
    EXPECT_CALL(*answerValidator, validateAnswer(validTargetLanguage, polishLanguageString))
        .WillOnce(Return(false));
    EXPECT_CALL(*answerValidator, validateAnswer(validTargetLanguage, englishLanguageString))
        .WillOnce(Return(true));
    EXPECT_CALL(*translationService, retrieveTranslation(textToTranslate, polishLanguage, englishLanguage))
        .WillOnce(Return(translatedText));

    const auto actualTranslation = glossary.translate();

    ASSERT_EQ(*actualTranslation, translatedText);
}

TEST_F(DefaultGlossaryTest, shouldReturnNamesOfDictionaries)
{
    EXPECT_CALL(*dictionaryService, getDictionaryNames()).WillOnce(Return(dictionaryNames));

    const auto actualNamesOfDictionaries = glossary.listDictionariesByNames();

    ASSERT_EQ(actualNamesOfDictionaries, dictionaryNames);
}

TEST_F(DefaultGlossaryTest, givenNoneDictionaryWords_shouldReturnEmptyDictionaryWords)
{
    expectUserInputString(dictionaryName1);
    EXPECT_CALL(*dictionaryService, getDictionaryWords(dictionaryName1)).WillOnce(Return(boost::none));

    const auto actualDictionaryWords = glossary.listDictionaryWordsFromDictionary();

    ASSERT_TRUE(actualDictionaryWords.empty());
}

TEST_F(DefaultGlossaryTest, givenDictionaryWords_shouldReturnDictionaryWords)
{
    expectUserInputString(dictionaryName1);
    EXPECT_CALL(*dictionaryService, getDictionaryWords(dictionaryName1)).WillOnce(Return(dictionaryWords));

    const auto actualDictionaryWords = glossary.listDictionaryWordsFromDictionary();

    ASSERT_EQ(actualDictionaryWords, dictionaryWordsAsString);
}

TEST_F(DefaultGlossaryTest, shouldAddDictionaryByName)
{
    expectUserInputString(dictionaryName1);
    EXPECT_CALL(*dictionaryService, addDictionary(dictionaryName1));

    glossary.addDictionary();
}

TEST_F(DefaultGlossaryTest, shouldAddDictionaryWordToDictionary)
{
    expectUserInputTwoString(dictionaryName1, englishWord1);
    EXPECT_CALL(*dictionaryService, addWordToDictionary(dictionaryWordWithoutTranslation, dictionaryName1));

    glossary.addEnglishWordToDictionary();
}

TEST_F(DefaultGlossaryTest, shouldRemoveDictionaryByName)
{
    expectUserInputString(dictionaryName1);
    EXPECT_CALL(*dictionaryService, removeDictionary(dictionaryName1));

    glossary.removeDictionary();
}

TEST_F(DefaultGlossaryTest, shouldRemoveDictionaryWordFromDictionary)
{
    expectUserInputTwoString(dictionaryName1, englishWord1);
    EXPECT_CALL(*dictionaryService, removeWordFromDictionary(englishWord1, dictionaryName1));

    glossary.removeEnglishWordFromDictionary();
}

TEST_F(DefaultGlossaryTest, shouldAddDictionaryFromFileAndSynchronizeDictionary)
{
    expectUserInputTwoString(dictionaryName1, pathToDictionaryWords);
    EXPECT_CALL(*dictionaryService, addDictionaryFromFile(dictionaryName1, pathToDictionaryWords));

    glossary.addDictionaryFromFile();
}

TEST_F(DefaultGlossaryTest, shouldUpdateDictionaryWordTranslationByInsert)
{
    expectUserInputThreeString(dictionaryName1, englishWord2, inputTranslation);
    EXPECT_CALL(*dictionaryTranslationUpdater,
                updateDictionaryWordTranslation(englishWord2, inputTranslation, dictionaryName1));

    glossary.updateDictionaryWordTranslationManually();
}

TEST_F(DefaultGlossaryTest, shouldUpdateDictionaryWordTranslationAutomatically)
{
    expectUserInputTwoString(dictionaryName1, englishWord2);
    EXPECT_CALL(*dictionaryTranslationUpdater,
                updateDictionaryWordTranslation(englishWord2, dictionaryName1));

    glossary.updateDictionaryWordTranslationAutomatically();
}

TEST_F(DefaultGlossaryTest, shouldUpdateDictionaryTranslationsAutomatically)
{
    expectUserInputString(dictionaryName1);
    EXPECT_CALL(*dictionaryTranslationUpdater, updateDictionaryTranslations(dictionaryName1));

    glossary.updateDictionaryTranslationsAutomatically();
}

TEST_F(DefaultGlossaryTest, shouldReturnWordDescription)
{
    expectUserInputString(englishWord1);
    EXPECT_CALL(*wordDescriptionService, retrieveWordDescription(englishWord1))
        .WillOnce(Return(wordDescription));

    const auto actualWordDescription = glossary.getEnglishWordDescription();

    ASSERT_EQ(actualWordDescription, toString(wordDescription));
}

TEST_F(DefaultGlossaryTest, shouldReturnStatistics)
{
    EXPECT_CALL(*statisticsRepository, getStatistics()).WillOnce(Return(statistics));

    const auto actualStatistics = glossary.showStatistics();

    ASSERT_EQ(actualStatistics, statisticsAsString);
}

TEST_F(DefaultGlossaryTest, shouldResetStatistics)
{
    EXPECT_CALL(*statisticsRepository, resetStatistics());

    glossary.resetStatistics();
}
