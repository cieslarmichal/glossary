#pragma once

#include "gmock/gmock.h"

#include "WordsCreatorService.h"

class WordsCreatorServiceMock : public WordsCreatorService
{
public:
    MOCK_CONST_METHOD0(createWords, Words());
};
