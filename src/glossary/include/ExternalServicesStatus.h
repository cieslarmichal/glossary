#pragma once

#include "translationService/TranslationApiStatus.h"
#include "wordDescriptionService/WordsApiStatus.h"

namespace glossary
{

using WordsApiStatus = wordDescriptionService::WordsApiStatus;
using TranslationApiStatus = translationService::TranslationApiStatus;

struct ExternalServicesStatus
{
    WordsApiStatus wordsApiStatus;
    TranslationApiStatus translationApiStatus;
};

inline bool operator==(const ExternalServicesStatus& lhs, const ExternalServicesStatus& rhs)
{
    return lhs.wordsApiStatus == rhs.wordsApiStatus && lhs.translationApiStatus == rhs.translationApiStatus;
}
}
