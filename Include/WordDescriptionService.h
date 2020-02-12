#pragma once

#include "boost/optional.hpp"
#include "wordsDb/wordsDescriptionsDb/WordDescription.h"

class WordDescriptionService
{
public:
    virtual ~WordDescriptionService() = default;

    virtual boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
    getWordDescription(const EnglishWord&) = 0;
};