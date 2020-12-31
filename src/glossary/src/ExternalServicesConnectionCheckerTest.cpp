#include "ExternalServicesConnectionChecker.h"

#include "gtest/gtest.h"

#include "translationService/TranslationServiceMock.h"
#include "wordDescriptionService/WordDescriptionServiceMock.h"
#include <boost/optional/optional_io.hpp>

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
    std::shared_ptr<WordDescriptionServiceMock> wordDescriptionService =
        std::make_shared<StrictMock<WordDescriptionServiceMock>>();
    std::shared_ptr<TranslationServiceMock> translationService =
        std::make_shared<StrictMock<TranslationServiceMock>>();
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
