#pragma once

#include "boost/optional.hpp"

#include "WordsApiStatus.h"
#include "wordDescriptionRepository/EnglishWord.h"
#include "wordDescriptionRepository/WordDescription.h"

namespace glossary::wordDescriptionService
{
class WordDescriptionService
{
public:
    virtual ~WordDescriptionService() = default;

    virtual wordDescriptionRepository::WordDescription
    retrieveWordDescription(const wordDescriptionRepository::EnglishWord&) noexcept = 0;
    virtual boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::EnglishWord&) = 0;
    virtual WordsApiStatus connectionToWordsApiAvailable() const = 0;
    virtual void updateApiKeyLocation(const std::string& apiKeyLocation) = 0;
};
}