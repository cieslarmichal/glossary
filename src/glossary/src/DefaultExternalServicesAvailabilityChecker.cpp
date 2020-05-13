#include "DefaultExternalServicesAvailabilityChecker.h"

namespace glossary
{

DefaultExternalServicesAvailabilityChecker::DefaultExternalServicesAvailabilityChecker(
    std::shared_ptr<translationService::TranslationRetrieverService> service,
    std::unique_ptr<ConnectionChecker> checker)
    : translationService{std::move(service)}, webConnectionChecker{std::move(checker)}
{
}

ExternalServicesAvailabilityStatus
DefaultExternalServicesAvailabilityChecker::checkExternalServicesAvailabilityStatus() const
{
    const auto webConnectionStatus = webConnectionChecker->connectionAvailable();
    const auto translateApiStatus = translationService->connectionToTranslateApiAvailable();
    return {webConnectionStatus, translateApiStatus};
}

}