#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "ApiKeyFileReader.h"
#include "ApiKeyFromFileContentRetriever.h"
#include "utils/FileAccess.h"

namespace glossary::translationService
{
class TranslateApiKeyFileReader : public ApiKeyFileReader
{
public:
    explicit TranslateApiKeyFileReader(std::shared_ptr<const utils::FileAccess>);

    boost::optional<std::string> readApiKey() const override;

private:
    boost::optional<std::string> readPathToFileWithApiKey() const;
    boost::optional<std::string> readApiKeyFromFile(const std::string&) const;

    std::shared_ptr<const utils::FileAccess> fileAccess;
    ApiKeyFromFileContentRetriever apiKeyFromFileContentRetriever;

    static const std::string filePathWithPathToFileWithApiKey;
};
}