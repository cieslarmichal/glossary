#pragma once

#include <memory>

#include "../../common/fileSystem/include/FileAccess.h"
#include "ApiKeyLocationUpdater.h"

namespace glossary::wordDescriptionService
{
class DefaultApiKeyLocationUpdater : public ApiKeyLocationUpdater
{
public:
    explicit DefaultApiKeyLocationUpdater(std::shared_ptr<const common::FileAccess>);

    void updateApiKeyLocation(const std::string& apiKeyLocation) const override;

private:
    std::shared_ptr<const common::FileAccess> fileAccess;

    static const std::string filePathContainingPathToFileWithApiKey;
};
}