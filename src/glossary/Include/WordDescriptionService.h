#pragma once

#include "boost/optional.hpp"
#include "wordsDescriptionsDb/EnglishWord.h"
#include "wordsDescriptionsDb/WordDescription.h"

class WordDescriptionService
{
public:
    virtual ~WordDescriptionService() = default;

    virtual boost::optional<wordsDescriptionsDb::WordDescription>
    getWordDescription(const wordsDescriptionsDb::EnglishWord&) = 0;
};