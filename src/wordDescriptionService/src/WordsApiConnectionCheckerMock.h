#pragma once

#include "gmock/gmock.h"

#include "WordsApiConnectionChecker.h"

namespace glossary::wordDescriptionService
{
class WordsApiConnectionCheckerMock : public WordsApiConnectionChecker
{
public:
    MOCK_CONST_METHOD1(connectionToWordsApiAvailable, WordsApiStatus(const std::string& wordsApiKey));
};
}