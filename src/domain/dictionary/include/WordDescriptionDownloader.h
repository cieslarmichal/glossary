#pragma once

#include <optional>

#include "WordDescription.h"

namespace glossary::dictionary
{
class WordDescriptionDownloader
{
public:
    virtual ~WordDescriptionDownloader() = default;

    virtual dictionary::WordDescription tryDownloadWordDescription(const std::string&,
                                                                   const std::string& wordsApiKey) const = 0;
};
}