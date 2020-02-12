#pragma once

#include "gmock/gmock.h"

#include "HttpWordDescriptionCreator.h"

class HttpWordDescriptionCreatorMock : public HttpWordDescriptionCreator
{
public:
    MOCK_CONST_METHOD1(
        createWordDescription,
        boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>(
            const wordsDb::translationsDb::Translation&));
};
