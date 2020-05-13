#pragma once

#include <memory>

#include "ConnectionChecker.h"
#include "ExternalServicesAvailabilityChecker.h"
#include "translationService/TranslationRetrieverService.h"

namespace glossary
{
class DefaultExternalServicesAvailabilityChecker : public ExternalServicesAvailabilityChecker
{
public:
    DefaultExternalServicesAvailabilityChecker(
        std::shared_ptr<translationService::TranslationRetrieverService>, std::unique_ptr<ConnectionChecker>);

    ExternalServicesAvailabilityStatus checkExternalServicesAvailabilityStatus() const override;

private:
    std::shared_ptr<translationService::TranslationRetrieverService> translationService;
    std::unique_ptr<ConnectionChecker> webConnectionChecker;
};
}
