#pragma once

#include "gmock/gmock.h"

#include "ExternalServicesAvailabilityChecker.h"

namespace glossary
{
class ExternalServicesAvailabilityCheckerMock : public ExternalServicesAvailabilityChecker
{
public:
    MOCK_CONST_METHOD0(checkExternalServicesAvailabilityStatus, ExternalServicesAvailabilityStatus());
};
}
