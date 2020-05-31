#include "DefaultTranslationService.h"

#include "gtest/gtest.h"

#include "ApiKeyFileReaderMock.h"
#include "ApiKeyLocationUpdaterMock.h"
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
const std::string apiKeyLocation{"apiKeyLocation"};
}

class DefaultTranslationServiceTest_Base : public Test
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
    std::unique_ptr<ApiKeyLocationUpdaterMock> apiKeyLocationUpdaterInit =
        std::make_unique<StrictMock<ApiKeyLocationUpdaterMock>>();
    ApiKeyLocationUpdaterMock* apiKeyLocationUpdater = apiKeyLocationUpdaterInit.get();
};

class DefaultTranslationServiceTest_WithApiKey_Base : public DefaultTranslationServiceTest_Base
{
public:
    DefaultTranslationServiceTest_WithApiKey_Base()
    {
        EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(apiKey));
    }
};

class DefaultTranslationServiceTest_WithoutApiKey_Base : public DefaultTranslationServiceTest_Base
{
public:
    DefaultTranslationServiceTest_WithoutApiKey_Base()
    {
        EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(boost::none));
    }
};

class DefaultTranslationServiceTest_WithApiKey : public DefaultTranslationServiceTest_WithApiKey_Base
{
public:
    DefaultTranslationService translationService{
        translator, translationRepository, std::move(apiKeyReaderInit), std::move(connectionCheckerInit),
        std::move(apiKeyLocationUpdaterInit)};
};

TEST_F(DefaultTranslationServiceTest_WithApiKey,
       repositoryContainsTranslation_shouldReturnTranslationFromRepository)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate))
        .WillOnce(Return(translationFromRepository));

    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(
    DefaultTranslationServiceTest_WithApiKey,
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

TEST_F(DefaultTranslationServiceTest_WithApiKey,
       repositoryAndTranslatorReturnNoneTranslation_shouldReturnNone)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate)).WillOnce(Return(boost::none));
    EXPECT_CALL(*translator, translate(textToTranslate, sourceLanguage, targetLanguage, apiKey))
        .WillOnce(Return(boost::none));
    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(actualTranslation, boost::none);
}

TEST_F(DefaultTranslationServiceTest_WithApiKey, shouldReturnSupportedLanguages)
{
    const auto actualSupportedLanguages = translationService.retrieveSupportedLanguages();

    ASSERT_EQ(actualSupportedLanguages, supportedLanguages);
}

TEST_F(DefaultTranslationServiceTest_WithApiKey,
       givenConnectionNotAvailableFromTranslatorConnectionChecker_shouldReturnConnectionUnavailableStatus)
{
    EXPECT_CALL(*translatorConnectionChecker, connectionToTranslatorWithApiKeyIsAvailable(_))
        .WillOnce(Return(TranslationApiStatus::Unavailable));

    const auto connectionAvailableStatus = translationService.connectionToTranslateApiAvailable();

    ASSERT_EQ(connectionAvailableStatus, TranslationApiStatus::Unavailable);
}

TEST_F(DefaultTranslationServiceTest_WithApiKey,
       givenConnectionAvailableFromTranslatorConnectionChecker_shouldReturnConnectionAvailableStatus)
{
    EXPECT_CALL(*translatorConnectionChecker, connectionToTranslatorWithApiKeyIsAvailable(_))
        .WillOnce(Return(TranslationApiStatus::Available));

    const auto connectionAvailableStatus = translationService.connectionToTranslateApiAvailable();

    ASSERT_EQ(connectionAvailableStatus, TranslationApiStatus::Available);
}

TEST_F(DefaultTranslationServiceTest_WithApiKey,
       givenInvalidApiKeyStatusFromTranslatorConnectionChecker_shouldReturnInvalidApiKeyStatus)
{
    EXPECT_CALL(*translatorConnectionChecker, connectionToTranslatorWithApiKeyIsAvailable(_))
        .WillOnce(Return(TranslationApiStatus::InvalidApiKey));

    const auto connectionAvailableStatus = translationService.connectionToTranslateApiAvailable();

    ASSERT_EQ(connectionAvailableStatus, TranslationApiStatus::InvalidApiKey);
}

TEST_F(DefaultTranslationServiceTest_WithApiKey, shouldUpdateApiKeyLocationAndReadNewApiKey)
{
    EXPECT_CALL(*apiKeyLocationUpdater, updateApiKeyLocation(apiKeyLocation));
    EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(apiKey));

    translationService.updateApiKeyLocation(apiKeyLocation);
}

class DefaultTranslationServiceTest_WithoutApiKey : public DefaultTranslationServiceTest_WithoutApiKey_Base
{
public:
    DefaultTranslationService translationService{
        translator, translationRepository, std::move(apiKeyReaderInit), std::move(connectionCheckerInit),
        std::move(apiKeyLocationUpdaterInit)};
};

TEST_F(DefaultTranslationServiceTest_WithoutApiKey, repositoryReturnsNoneTranslation_shouldReturnNone)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate)).WillOnce(Return(boost::none));

    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(actualTranslation, boost::none);
}

TEST_F(DefaultTranslationServiceTest_WithoutApiKey,
       repositoryReturnsTranslation_shouldReturnTranslationFromRepository)
{
    EXPECT_CALL(*translationRepository, getTranslation(textToTranslate))
        .WillOnce(Return(translationFromRepository));

    const auto actualTranslation =
        translationService.retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualTranslation, expectedTranslatedText);
}

TEST_F(DefaultTranslationServiceTest_WithoutApiKey, shouldReturnSupportedLanguages)
{
    const auto actualSupportedLanguages = translationService.retrieveSupportedLanguages();

    ASSERT_EQ(actualSupportedLanguages, supportedLanguages);
}

TEST_F(DefaultTranslationServiceTest_WithoutApiKey, noApiKey_shouldReturnInvalidApiKeyStatus)
{
    const auto connectionAvailableStatus = translationService.connectionToTranslateApiAvailable();

    ASSERT_EQ(connectionAvailableStatus, TranslationApiStatus::InvalidApiKey);
}

TEST_F(DefaultTranslationServiceTest_WithoutApiKey, shouldUpdateApiKeyLocationAndReadNewApiKey)
{
    EXPECT_CALL(*apiKeyLocationUpdater, updateApiKeyLocation(apiKeyLocation));
    EXPECT_CALL(*apiKeyReader, readApiKey()).WillOnce(Return(apiKey));

    translationService.updateApiKeyLocation(apiKeyLocation);
}
