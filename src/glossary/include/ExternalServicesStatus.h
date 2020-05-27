#pragma once

#include "translationService/TranslationApiStatus.h"
#include "wordDescriptionService/WordsApiStatus.h"

namespace glossary
{
struct ExternalServicesStatus
{
    wordDescriptionService::WordsApiStatus wordsApiStatus;
    translationService::TranslationApiStatus translationApiStatus;
};

inline bool operator==(const ExternalServicesStatus& lhs, const ExternalServicesStatus& rhs)
{
    return lhs.wordsApiStatus == rhs.wordsApiStatus && lhs.translationApiStatus == rhs.translationApiStatus;
}
}
