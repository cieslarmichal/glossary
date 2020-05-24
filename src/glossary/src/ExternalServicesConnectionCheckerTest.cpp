#include "ExternalServicesConnectionChecker.h"

#include "gtest/gtest.h"

#include "translationService/TranslationRetrieverServiceMock.h"
#include "wordDescriptionService/WordDescriptionRetrieverServiceMock.h"

using namespace ::testing;
using namespace glossary;
using namespace translationService;
using namespace wordDescriptionService;

namespace
{
auto availableStatus = ExternalServicesStatus{WordsApiStatus::Available, TranslationApiStatus::Available};
}

class ExternalServicesConnectionCheckerTest : public Test
{
public:
    std::shared_ptr<WordDescriptionRetrieverServiceMock> wordDescriptionService =
        std::make_shared<StrictMock<WordDescriptionRetrieverServiceMock>>();
    std::shared_ptr<TranslationRetrieverServiceMock> translationService =
        std::make_shared<StrictMock<TranslationRetrieverServiceMock>>();
    ExternalServicesConnectionChecker servicesAvailabilityChecker{translationService, wordDescriptionService};
};

TEST_F(ExternalServicesConnectionCheckerTest,
       shouldReturnStatusesFromWordDescriptionServiceAndTranslationService)
{
    EXPECT_CALL(*wordDescriptionService, connectionToWordsApiAvailable())
        .WillOnce(Return(WordsApiStatus::Available));
    EXPECT_CALL(*translationService, connectionToTranslateApiAvailable())
        .WillOnce(Return(TranslationApiStatus::Available));

    const auto servicesAvailabilityStatus =
        servicesAvailabilityChecker.checkExternalServicesAvailabilityStatus();

    ASSERT_EQ(servicesAvailabilityStatus, availableStatus);
}
