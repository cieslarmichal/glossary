#pragma once

#include "gmock/gmock.h"

#include "HttpWordDescriptionCreator.h"

class HttpWordDescriptionCreatorMock : public HttpWordDescriptionCreator
{
public:
    MOCK_CONST_METHOD1(createWordDescription,
                       boost::optional<wordsDescriptionsDb::WordDescription>(
                           const wordsDescriptionsDb::EnglishWord&));
    MOCK_CONST_METHOD1(createWordsDescriptions,
                       wordsDescriptionsDb::WordsDescriptions(
                           const wordsDescriptionsDb::EnglishWords&));
};
