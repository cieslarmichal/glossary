#include "DefaultApiKeyLocationUpdater.h"

#include "utils/GetProjectPath.h"

namespace glossary::wordDescriptionService
{

const std::string DefaultApiKeyLocationUpdater::filePathContainingPathToFileWithApiKey{
    utils::getProjectPath("glossary") + "config/wordsApiKeyLocation.txt"};

DefaultApiKeyLocationUpdater::DefaultApiKeyLocationUpdater(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

void DefaultApiKeyLocationUpdater::updateApiKeyLocation(const std::string& apiKeyLocation) const
{
    if (fileAccess->exists(filePathContainingPathToFileWithApiKey))
    {
        fileAccess->write(filePathContainingPathToFileWithApiKey, apiKeyLocation);
    }
}

}