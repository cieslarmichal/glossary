#pragma once

#include "boost/optional.hpp"

#include "wordDescriptionRepository/WordDescription.h"

namespace glossary::wordDescriptionDownloader
{
class WordDescriptionDownloader
{
public:
    virtual ~WordDescriptionDownloader() = default;

    virtual boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::EnglishWord&) const = 0;
};
}