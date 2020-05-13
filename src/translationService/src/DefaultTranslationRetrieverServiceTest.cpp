#include "DefaultTranslationRetrieverService.h"

#include "gtest/gtest.h"

#include "ApiKeyFileReaderMock.h"
#include "TranslatorConnectionCheckerMock.h"
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
const Translation repositoryTranslation{polishWord, englishWord};
const boost::optional<Translation> translationFromRepository{repositoryTranslation};
const auto textToTranslate{"herbata"};
const TranslatedText expectedTranslatedText{"tea"};
const boost::optional<TranslatedText> translatedTextOpt{expectedTranslatedText};
const auto sourceLanguage = SourceLanguage::Polish;
const auto targetLanguage = TargetLanguage::English;
const std::vector<std::string> supportedLanguages{"Polish", "English"};
const std::string apiKey{"topSecretKey"};
}

class DefaultTranslationRetrieverServiceTest_Base : public Test
{
public:
    std::shared_ptr<TranslatorMock> translator = std::make_shared<StrictMock<TranslatorMock>>();
    std::shared_ptr<TranslationRepositoryMock> translationRepository =
        std::make_shared<StrictMock<TranslationRepositoryMock>>();
    std::unique_ptr<ApiKeyFileReaderMock> apiKeyReaderInit =
        std::make_unique<StrictMock<ApiKeyFileReaderMock>>();
    ApiKeyFileReaderMock* apiKeyReader = apiKeyReaderInit.get();
    std::unique_ptr<TranslatorConnectionCheckerMock> connectionCheckerInit =
        std::make_unique<StrictMock<TranslatorConnectionCheckerMock>>();
    TranslatorConnectionCheckerMock* translatorConnectionChecker = connectionCheckerInit.get();
};

class DefaultTranslationRetrieverServiceTest_WithApiKey_Base
    : public DefaultTranslationRetrieverServiceTest_Base
{
public:
    DefaultTranslationRetrieverServiceTest_WithApiKey_Base()
    {
        EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(apiKey));
    }
};

class DefaultTranslationRetrieverServiceTest_WithoutApiKey_Base
    : public DefaultTranslationRetrieverServiceTest_Base
{
public:
    DefaultTranslationRetrieverServiceTest_WithoutApiKey_Base()
    {
        EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(boost::none));
    }
};

class DefaultTranslationRetrieverServiceTest_WithApiKey
    : public DefaultTranslationRetrieverServiceTest_WithApiKey_Base
{
public:
    DefaultTranslationRetrieverService translationService{
        translator, translationRepository, std::move(apiKeyReaderInit), std::move(connectionCheckerInit)};
};

TEST_F(DefaultTranslationRetrieverServiceTest_WithApiKey,
       repositoryContainsTranslation_shouldReturnTranslationFromRepository)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate))
        .WillOnce(Return(translationFromRepository));

    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(
    DefaultTranslationRetrieverServiceTest_WithApiKey,
    repositoryDoesNotContainTranslation_shouldReturnTranslationFromTranslatorAndSaveTranslationInRepository)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate)).WillOnce(Return(boost::none));
    EXPECT_CALL(*translator, translate(textToTranslate, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Return(translatedTextOpt));
    EXPECT_CALL(*translationRepository, addTranslation(repositoryTranslation));

    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(DefaultTranslationRetrieverServiceTest_WithApiKey,
       repositoryAndTranslatorReturnNoneTranslation_shouldReturnNone)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate)).WillOnce(Return(boost::none));
    EXPECT_CALL(*translator, translate(textToTranslate, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Return(boost::none));
    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(actualTranslation, boost::none);
}

TEST_F(DefaultTranslationRetrieverServiceTest_WithApiKey, shouldReturnSupportedLanguages)
{
    const auto actualSupportedLanguages = translationService.retrieveSupportedLanguages();

    ASSERT_EQ(actualSupportedLanguages, supportedLanguages);
}

TEST_F(DefaultTranslationRetrieverServiceTest_WithApiKey,
       givenConnectionNotAvailableFromTranslatorConnectionChecker_shouldReturnConnectionUnavailableStatus)
{
    EXPECT_CALL(*translatorConnectionChecker, connectionToTranslatorWithApiKeyIsAvailable(_))
        .WillOnce(Return(TranslationApiConnectionStatus::Unavailable));

    const auto connectionAvailableStatus = translationService.connectionToTranslateApiAvailable();

    ASSERT_EQ(connectionAvailableStatus, TranslationApiConnectionStatus::Unavailable);
}

TEST_F(DefaultTranslationRetrieverServiceTest_WithApiKey,
       givenConnectionAvailableFromTranslatorConnectionChecker_shouldReturnConnectionAvailableStatus)
{
    EXPECT_CALL(*translatorConnectionChecker, connectionToTranslatorWithApiKeyIsAvailable(_))
        .WillOnce(Return(TranslationApiConnectionStatus::Available));

    const auto connectionAvailableStatus = translationService.connectionToTranslateApiAvailable();

    ASSERT_EQ(connectionAvailableStatus, TranslationApiConnectionStatus::Available);
}

TEST_F(DefaultTranslationRetrieverServiceTest_WithApiKey,
       givenInvalidApiKeyStatusFromTranslatorConnectionChecker_shouldReturnInvalidApiKeyStatus)
{
    EXPECT_CALL(*translatorConnectionChecker, connectionToTranslatorWithApiKeyIsAvailable(_))
        .WillOnce(Return(TranslationApiConnectionStatus::InvalidApiKey));

    const auto connectionAvailableStatus = translationService.connectionToTranslateApiAvailable();

    ASSERT_EQ(connectionAvailableStatus, TranslationApiConnectionStatus::InvalidApiKey);
}

class DefaultTranslationRetrieverServiceTest_WithoutApiKey
    : public DefaultTranslationRetrieverServiceTest_WithoutApiKey_Base
{
public:
    DefaultTranslationRetrieverService translationService{
        translator, translationRepository, std::move(apiKeyReaderInit), std::move(connectionCheckerInit)};
};

TEST_F(DefaultTranslationRetrieverServiceTest_WithoutApiKey,
       repositoryReturnsNoneTranslation_shouldReturnNone)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate)).WillOnce(Return(boost::none));

    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(actualTranslation, boost::none);
}

TEST_F(DefaultTranslationRetrieverServiceTest_WithoutApiKey,
       repositoryReturnsTranslation_shouldReturnTranslationFromRepository)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate))
        .WillOnce(Return(translationFromRepository));

    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(DefaultTranslationRetrieverServiceTest_WithoutApiKey, shouldReturnSupportedLanguages)
{
    const auto actualSupportedLanguages = translationService.retrieveSupportedLanguages();

    ASSERT_EQ(actualSupportedLanguages, supportedLanguages);
}

TEST_F(DefaultTranslationRetrieverServiceTest_WithoutApiKey, noApiKey_shouldReturnInvalidApiKeyStatus)
{
    const auto connectionAvailableStatus = translationService.connectionToTranslateApiAvailable();

    ASSERT_EQ(connectionAvailableStatus, TranslationApiConnectionStatus::InvalidApiKey);
}