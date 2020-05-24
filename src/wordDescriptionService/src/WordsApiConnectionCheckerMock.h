#pragma once

#include "gmock/gmock.h"

#include "WordsApiConnectionChecker.h"

namespace glossary::wordDescriptionService
{
class WordsApiConnectionCheckerMock : public WordsApiConnectionChecker
{
public:
    MOCK_METHOD0(connectionToWordsApiAvailable, WordsApiStatus());
};
}