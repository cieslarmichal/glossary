#pragma once
#include <string>

namespace glossary::translationService
{
class ApiKeyFromFileContentRetriever
{
public:
    std::string retrieveApiKeyFromFileContent(const std::string& fileContentWithApiKey) const;
};
}