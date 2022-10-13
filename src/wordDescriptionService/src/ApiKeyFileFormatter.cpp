#include "ApiKeyFileFormatter.h"

#include "../../common/collection/include/StringHelper.h"

namespace glossary::wordDescriptionService
{
std::string ApiKeyFileFormatter::getFormattedApiKey(const std::string& fileContentWithApiKey) const
{
    auto fileContent{fileContentWithApiKey};
    common::trim(fileContent);
    return fileContent;
}
}