#include "DefaultExternalServicesAvailabilityChecker.h"

#include "gtest/gtest.h"

#include "ConnectionCheckerMock.h"
#include "translationService/TranslationRetrieverServiceMock.h"

using namespace ::testing;
using namespace glossary;
using namespace translationService;

namespace
{
auto availableStatus = ExternalServicesAvailabilityStatus{ConnectionStatus::Available,
                                                          TranslationApiConnectionStatus::Available};
auto availableWebConnectionUnavailableTranslation = ExternalServicesAvailabilityStatus{
    ConnectionStatus::Available, TranslationApiConnectionStatus::Unavailable};
auto availableWebConnectionInvalidTranslationApiKey = ExternalServicesAvailabilityStatus{
    ConnectionStatus::Available, TranslationApiConnectionStatus::InvalidApiKey};
auto unavailableStatus = ExternalServicesAvailabilityStatus{ConnectionStatus::Unavailable,
                                                            TranslationApiConnectionStatus::Unavailable};
auto unavailableWebConnectionAvailableTranslation = ExternalServicesAvailabilityStatus{
    ConnectionStatus::Unavailable, TranslationApiConnectionStatus::Available};
auto unavailableWebConnectionInvalidTranslationApiKey = ExternalServicesAvailabilityStatus{
    ConnectionStatus::Unavailable, TranslationApiConnectionStatus::InvalidApiKey};
}

class DefaultExternalServicesAvailabilityCheckerTest : public Test
{
public:
    std::unique_ptr<ConnectionCheckerMock> connectionCheckerInit =
        std::make_unique<StrictMock<ConnectionCheckerMock>>();
    ConnectionCheckerMock* connectionChecker = connectionCheckerInit.get();
    std::shared_ptr<TranslationRetrieverServiceMock> translationService =
        std::make_shared<StrictMock<TranslationRetrieverServiceMock>>();
    DefaultExternalServicesAvailabilityChecker servicesAvailabilityChecker{translationService,
                                                                           std::move(connectionCheckerInit)};
};

TEST_F(DefaultExternalServicesAvailabilityCheckerTest,
       givenAvailableWebConnectionAndAvailableTranslationService_shouldReturnAvailableStatuses)
{
    EXPECT_CALL(*connectionChecker, connectionAvailable()).WillOnce(Return(ConnectionStatus::Available));
    EXPECT_CALL(*translationService, connectionToTranslateApiAvailable())
        .WillOnce(Return(TranslationApiConnectionStatus::Available));

    const auto servicesAvailabilityStatus =
        servicesAvailabilityChecker.checkExternalServicesAvailabilityStatus();

    ASSERT_EQ(servicesAvailabilityStatus, availableStatus);
}

TEST_F(
    DefaultExternalServicesAvailabilityCheckerTest,
    givenAvailableWebConnectionAndUnavailableTranslationService_shouldReturnAvailableWebConnectionAndUnavailableTranslationService)
{
    EXPECT_CALL(*connectionChecker, connectionAvailable()).WillOnce(Return(ConnectionStatus::Available));
    EXPECT_CALL(*translationService, connectionToTranslateApiAvailable())
        .WillOnce(Return(TranslationApiConnectionStatus::Unavailable));

    const auto servicesAvailabilityStatus =
        servicesAvailabilityChecker.checkExternalServicesAvailabilityStatus();

    ASSERT_EQ(servicesAvailabilityStatus, availableWebConnectionUnavailableTranslation);
}

TEST_F(
    DefaultExternalServicesAvailabilityCheckerTest,
    givenAvailableWebConnectionAndInvalidTranslationApiKey_shouldReturnAvailableWebConnectionAndInvalidApiKey)
{
    EXPECT_CALL(*connectionChecker, connectionAvailable()).WillOnce(Return(ConnectionStatus::Available));
    EXPECT_CALL(*translationService, connectionToTranslateApiAvailable())
        .WillOnce(Return(translationService::TranslationApiConnectionStatus::InvalidApiKey));

    const auto servicesAvailabilityStatus =
        servicesAvailabilityChecker.checkExternalServicesAvailabilityStatus();

    ASSERT_EQ(servicesAvailabilityStatus, availableWebConnectionInvalidTranslationApiKey);
}

TEST_F(
    DefaultExternalServicesAvailabilityCheckerTest,
    givenUnavailableWebConnectionAndAvailableTranslationService_shouldReturnUnavailableWebconnectionAndAvailableTranslationService)
{
    EXPECT_CALL(*connectionChecker, connectionAvailable()).WillOnce(Return(ConnectionStatus::Unavailable));
    EXPECT_CALL(*translationService, connectionToTranslateApiAvailable())
        .WillOnce(Return(TranslationApiConnectionStatus::Available));

    const auto servicesAvailabilityStatus =
        servicesAvailabilityChecker.checkExternalServicesAvailabilityStatus();

    ASSERT_EQ(servicesAvailabilityStatus, unavailableWebConnectionAvailableTranslation);
}

TEST_F(DefaultExternalServicesAvailabilityCheckerTest,
       givenUnavailableWebConnectionAndUnavailableTranslationService_shouldReturnUnavailableStatuses)
{
    EXPECT_CALL(*connectionChecker, connectionAvailable()).WillOnce(Return(ConnectionStatus::Unavailable));
    EXPECT_CALL(*translationService, connectionToTranslateApiAvailable())
        .WillOnce(Return(TranslationApiConnectionStatus::Unavailable));

    const auto servicesAvailabilityStatus =
        servicesAvailabilityChecker.checkExternalServicesAvailabilityStatus();

    ASSERT_EQ(servicesAvailabilityStatus, unavailableStatus);
}

TEST_F(
    DefaultExternalServicesAvailabilityCheckerTest,
    givenUnavailableWebConnectionAndInvalidTranslationApiKey_shouldReturnUnavailableWebConnectionAndInvalidApiKey)
{
    EXPECT_CALL(*connectionChecker, connectionAvailable()).WillOnce(Return(ConnectionStatus::Unavailable));
    EXPECT_CALL(*translationService, connectionToTranslateApiAvailable())
        .WillOnce(Return(translationService::TranslationApiConnectionStatus::InvalidApiKey));

    const auto servicesAvailabilityStatus =
        servicesAvailabilityChecker.checkExternalServicesAvailabilityStatus();

    ASSERT_EQ(servicesAvailabilityStatus, unavailableWebConnectionInvalidTranslationApiKey);
}