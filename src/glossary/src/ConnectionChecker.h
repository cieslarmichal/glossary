#pragma once

#include "ExternalServicesStatus.h"

namespace glossary
{
class ConnectionChecker
{
public:
    virtual ~ConnectionChecker() = default;

    virtual ExternalServicesStatus checkExternalServicesAvailabilityStatus() const = 0;
};
}