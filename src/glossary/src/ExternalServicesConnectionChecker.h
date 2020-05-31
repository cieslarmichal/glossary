#pragma once

#include <memory>

#include "ConnectionChecker.h"
#include "translationService/TranslationService.h"
#include "wordDescriptionService/WordDescriptionService.h"

namespace glossary
{
class ExternalServicesConnectionChecker : public ConnectionChecker
{
public:
    ExternalServicesConnectionChecker(
        std::shared_ptr<translationService::TranslationService>,
        std::shared_ptr<wordDescriptionService::WordDescriptionService>);

    ExternalServicesStatus checkExternalServicesAvailabilityStatus() const override;

private:
    std::shared_ptr<translationService::TranslationService> translationService;
    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionService;
};
}
