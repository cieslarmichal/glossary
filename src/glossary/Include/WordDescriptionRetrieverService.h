#pragma once

#include "boost/optional.hpp"

#include "wordDescriptionRepository/EnglishWord.h"
#include "wordDescriptionRepository/WordDescription.h"

class WordDescriptionRetrieverService
{
public:
    virtual ~WordDescriptionRetrieverService() = default;

    virtual boost::optional<wordDescriptionRepository::WordDescription>
    retrieveWordDescription(const wordDescriptionRepository::EnglishWord&) = 0;
};