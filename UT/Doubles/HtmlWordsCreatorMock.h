#pragma once

#include "gmock/gmock.h"

#include "HtmlWordsCreator.h"

class HtmlWordsCreatorMock : public HtmlWordsCreator
{
public:
    MOCK_CONST_METHOD1(createWord, Word(const WordWithTranslation&));
};
