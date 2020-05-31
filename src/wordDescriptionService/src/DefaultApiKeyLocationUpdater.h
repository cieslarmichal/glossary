#pragma once

#include <memory>

#include "ApiKeyLocationUpdater.h"
#include "utils/FileAccess.h"

namespace glossary::wordDescriptionService
{
class DefaultApiKeyLocationUpdater : public ApiKeyLocationUpdater
{
public:
    explicit DefaultApiKeyLocationUpdater(std::shared_ptr<const utils::FileAccess>);

    void updateApiKeyLocation(const std::string& apiKeyLocation) const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;

    static const std::string filePathContainingPathToFileWithApiKey;
};
}