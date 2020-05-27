#pragma once

#include <memory>

#include "ConnectionChecker.h"
#include "translationService/TranslationRetrieverService.h"
#include "wordDescriptionService/WordDescriptionRetrieverService.h"

namespace glossary
{
class ExternalServicesConnectionChecker : public ConnectionChecker
{
public:
    ExternalServicesConnectionChecker(
        std::shared_ptr<translationService::TranslationRetrieverService>,
        std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService>);

    ExternalServicesStatus checkExternalServicesAvailabilityStatus() const override;

private:
    std::shared_ptr<translationService::TranslationRetrieverService> translationService;
    std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService> wordDescriptionService;
};
}
