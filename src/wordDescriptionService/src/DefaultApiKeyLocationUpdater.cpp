#include "DefaultApiKeyLocationUpdater.h"

#include "../../common/fileSystem/include/GetProjectPath.h"

namespace glossary::wordDescriptionService
{

const std::string DefaultApiKeyLocationUpdater::filePathContainingPathToFileWithApiKey{
    common::getProjectPath("glossary") + "config/wordsApiKeyLocation.txt"};

DefaultApiKeyLocationUpdater::DefaultApiKeyLocationUpdater(
    std::shared_ptr<const common::FileAccess> fileAccessInit)
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