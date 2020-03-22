#pragma once

#include "wordDescriptionRepository/WordDescription.h"

namespace wordDescriptionDownloader
{
class WordDescriptionDownloader
{
public:
    virtual ~WordDescriptionDownloader() = default;

    virtual boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::EnglishWord&) const = 0;
};
}