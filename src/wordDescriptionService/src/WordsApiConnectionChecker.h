#pragma once

#include "WordsApiStatus.h"
#include <string>

namespace glossary::wordDescriptionService
{
class WordsApiConnectionChecker
{
public:
    virtual ~WordsApiConnectionChecker() = default;

    virtual WordsApiStatus connectionToWordsApiAvailable(const std::string& wordsApiKey) const = 0;
};
}