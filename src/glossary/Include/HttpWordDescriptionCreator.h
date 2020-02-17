#pragma once

#include "translationsDb/Translation.h"
#include "wordsDescriptionsDb/WordDescription.h"

class HttpWordDescriptionCreator
{
public:
    virtual ~HttpWordDescriptionCreator() = default;

    virtual boost::optional<wordsDescriptionsDb::WordDescription>
    createWordDescription(
        const translationsDb::Translation&) const = 0;
};