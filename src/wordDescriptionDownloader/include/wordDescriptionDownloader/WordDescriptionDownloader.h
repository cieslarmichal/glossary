#pragma once

#include <optional>

#include "wordDescriptionRepository/WordDescription.h"

namespace glossary::wordDescriptionDownloader
{
class WordDescriptionDownloader
{
public:
    virtual ~WordDescriptionDownloader() = default;

    virtual wordDescriptionRepository::WordDescription
    tryDownloadWordDescription(const wordDescriptionRepository::std::string&,
                               const std::string& wordsApiKey) const = 0;
};
}