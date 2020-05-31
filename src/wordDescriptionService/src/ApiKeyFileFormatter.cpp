#include "ApiKeyFileFormatter.h"

#include "utils/StringHelper.h"

namespace glossary::wordDescriptionService
{
std::string ApiKeyFileFormatter::getFormattedApiKey(const std::string& fileContentWithApiKey) const
{
    auto fileContent{fileContentWithApiKey};
    utils::trim(fileContent);
    return fileContent;
}
}