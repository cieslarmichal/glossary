#pragma once

#include "boost/optional.hpp"

#include "wordDescriptionRepository/WordDescription.h"

namespace glossary::wordDescriptionDownloader
{
class WordDescriptionDownloader
{
public:
    virtual ~WordDescriptionDownloader() = default;

    virtual wordDescriptionRepository::WordDescription
    tryDownloadWordDescription(const wordDescriptionRepository::EnglishWord&) const = 0;
};
}