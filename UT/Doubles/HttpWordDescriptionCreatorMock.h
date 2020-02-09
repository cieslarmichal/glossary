#pragma once

#include "gmock/gmock.h"

#include "HttpWordDescriptionCreator.h"

class HttpWordDescriptionCreatorMock : public HttpWordDescriptionCreator
{
public:
    MOCK_CONST_METHOD1(createWordDescription, Word(const WordWithTranslation&));
};
