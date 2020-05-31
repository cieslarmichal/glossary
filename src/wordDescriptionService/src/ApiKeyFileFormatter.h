#pragma once

#include <string>

namespace glossary::wordDescriptionService
{
class ApiKeyFileFormatter
{
public:
    std::string getFormattedApiKey(const std::string& fileContentWithApiKey) const;
};
}