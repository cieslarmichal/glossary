#pragma once

#include "gmock/gmock.h"

#include "ConnectionChecker.h"

namespace glossary
{
class ConnectionCheckerMock : public ConnectionChecker
{
public:
    MOCK_CONST_METHOD0(checkExternalServicesAvailabilityStatus, ExternalServicesStatus());
};
}
