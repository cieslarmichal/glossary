#pragma once

#include "gmock/gmock.h"

#include "WordsGeneratorService.h"

class WordsGeneratorServiceMock : public WordsGeneratorService
{
public:
    MOCK_CONST_METHOD0(generateWord, Word(const wordsDb::translationsDb::Translation&));
    MOCK_CONST_METHOD0(generateWords, Words());
};
