#pragma once

#include "boost/optional.hpp"

#include "WordsApiStatus.h"
#include "wordDescriptionRepository/EnglishWord.h"
#include "wordDescriptionRepository/WordDescription.h"

namespace glossary::wordDescriptionService
{
class WordDescriptionRetrieverService
{
public:
    virtual ~WordDescriptionRetrieverService() = default;

    virtual wordDescriptionRepository::WordDescription
    retrieveWordDescription(const wordDescriptionRepository::EnglishWord&) = 0;
    virtual WordsApiStatus connectionToWordsApiAvailable() = 0;
};
}