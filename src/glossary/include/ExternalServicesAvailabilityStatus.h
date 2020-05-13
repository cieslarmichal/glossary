#pragma once

#include "ConnectionStatus.h"
#include "translationService/TranslationApiConnectionStatus.h"

namespace glossary
{
struct ExternalServicesAvailabilityStatus
{
    ConnectionStatus merriamWebsterConnectionStatus;
    translationService::TranslationApiConnectionStatus translationApiConnectionStatus;
};

inline bool operator==(const ExternalServicesAvailabilityStatus& lhs,
                       const ExternalServicesAvailabilityStatus& rhs)
{
    return lhs.merriamWebsterConnectionStatus == rhs.merriamWebsterConnectionStatus &&
           lhs.translationApiConnectionStatus == rhs.translationApiConnectionStatus;
}
}
