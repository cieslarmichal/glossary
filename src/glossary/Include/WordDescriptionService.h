#pragma once

#include "boost/optional.hpp"

#include "wordDescriptionRepository/EnglishWord.h"
#include "wordDescriptionRepository/WordDescription.h"

class WordDescriptionService
{
public:
    virtual ~WordDescriptionService() = default;

    virtual boost::optional<wordDescriptionRepository::WordDescription>
    getWordDescription(const wordDescriptionRepository::EnglishWord&) = 0;
};