#pragma once

#include <string>

namespace glossary::wordDescriptionDownloader
{
class ApiKeyFileFormatter
{
public:
    std::string getFormattedApiKey(const std::string& fileContentWithApiKey) const;
};
}