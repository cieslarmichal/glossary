#pragma once

#include <string>

namespace glossary::translationService
{
class ApiKeyLocationUpdater
{
public:
    virtual ~ApiKeyLocationUpdater() = default;

    virtual void updateApiKeyLocation(const std::string& apiKeyLocation) const = 0;
};
}