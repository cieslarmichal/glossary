#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionGenerator.h"

class WordDescriptionGeneratorMock : public WordDescriptionGenerator
{
public:
    MOCK_METHOD1(generateWordsDescriptions,
                 wordsDescriptionsDb::WordsDescriptions(const wordsDescriptionsDb::EnglishWords&));
    MOCK_METHOD1(generateWordDescription, boost::optional<wordsDescriptionsDb::WordDescription>(
                                              const wordsDescriptionsDb::EnglishWord&));
};
