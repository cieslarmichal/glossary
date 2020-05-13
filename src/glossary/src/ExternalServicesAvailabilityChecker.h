#pragma once

#include "ExternalServicesAvailabilityStatus.h"

namespace glossary
{
class ExternalServicesAvailabilityChecker
{
public:
    virtual ~ExternalServicesAvailabilityChecker() = default;

    virtual ExternalServicesAvailabilityStatus checkExternalServicesAvailabilityStatus() const = 0;
};
}