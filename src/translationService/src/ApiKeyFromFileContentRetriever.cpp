#include "ApiKeyFromFileContentRetriever.h"

#include "utils/StringHelper.h"

namespace glossary::translationService
{

std::string
ApiKeyFromFileContentRetriever::retrieveApiKeyFromFileContent(const std::string& fileContentWithApiKey) const
{
    auto fileContent{fileContentWithApiKey};
    utils::trim(fileContent);
    return fileContent;
}

}