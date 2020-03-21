#pragma once

#include "wordsDescriptionsDb/WordDescription.h"

namespace wordDescriptionDownloader
{
class WordDescriptionDownloader
{
public:
    virtual ~WordDescriptionDownloader() = default;

    virtual boost::optional<wordsDescriptionsDb::WordDescription>
    downloadWordDescription(const wordsDescriptionsDb::EnglishWord&) const = 0;
};
}