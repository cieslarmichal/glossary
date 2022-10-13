#pragma once

#include "boost/optional.hpp"

#include "WordsApiStatus.h"
#include "wordDescriptionRepository/WordDescription.h"
#include "wordDescriptionRepository/std::string.h"

namespace glossary::wordDescriptionService
{
class WordDescriptionService
{
public:
    virtual ~WordDescriptionService() = default;

    virtual wordDescriptionRepository::WordDescription
    retrieveWordDescription(const wordDescriptionRepository::std::string&) noexcept = 0;
    virtual boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::std::string&) = 0;
    virtual WordsApiStatus connectionToWordsApiAvailable() const = 0;
    virtual void updateApiKeyLocation(const std::string& apiKeyLocation) = 0;
};
}