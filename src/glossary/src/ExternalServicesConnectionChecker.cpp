#include "ExternalServicesConnectionChecker.h"

namespace glossary
{

ExternalServicesConnectionChecker::ExternalServicesConnectionChecker(
    std::shared_ptr<translationService::TranslationRetrieverService> translationServiceInit,
    std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService> wordDescriptionServiceInit)
    : translationService{std::move(translationServiceInit)},
      wordDescriptionService{std::move(wordDescriptionServiceInit)}
{
}

ExternalServicesStatus ExternalServicesConnectionChecker::checkExternalServicesAvailabilityStatus() const
{
    const auto wordsApiStatus = wordDescriptionService->connectionToWordsApiAvailable();
    const auto translateApiStatus = translationService->connectionToTranslateApiAvailable();
    return {wordsApiStatus, translateApiStatus};
}

}