#pragma once

#include <memory>
#include <optional>

#include "../../common/fileSystem/include/FileAccess.h"
#include "ApiKeyFileFormatter.h"
#include "ApiKeyReader.h"

namespace glossary::wordDescriptionService
{
class WordsApiKeyFileReader : public ApiKeyReader
{
public:
    explicit WordsApiKeyFileReader(std::shared_ptr<const common::fileSystem::FileAccess>);

    std::optional<std::string> readApiKey() const override;

private:
    std::optional<std::string> readPathToFileWithApiKey() const;
    std::optional<std::string> readApiKeyFromFile(const std::string&) const;

    std::shared_ptr<const common::fileSystem::FileAccess> fileAccess;
    ApiKeyFileFormatter apiKeyFileFormatter;

    static const std::string filePathContainingPathToFileWithApiKey;
};
}