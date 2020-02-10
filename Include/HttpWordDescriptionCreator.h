#pragma once

#include "wordsDb/translationsDb/Translation.h"
#include "wordsDb/wordsDescriptionsDb/WordDescription.h"

class HttpWordDescriptionCreator
{
public:
    virtual ~HttpWordDescriptionCreator() = default;

    virtual boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
    createWordDescription(
        const wordsDb::translationsDb::Translation&) const = 0;
};