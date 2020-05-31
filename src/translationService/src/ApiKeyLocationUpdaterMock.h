#pragma once

#include "gmock/gmock.h"

#include "ApiKeyLocationUpdater.h"

namespace glossary::translationService
{
class ApiKeyLocationUpdaterMock : public ApiKeyLocationUpdater
{
public:
    MOCK_CONST_METHOD1(updateApiKeyLocation, void(const std::string& apiKeyLocation));
};
}