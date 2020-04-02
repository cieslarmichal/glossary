#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionGenerator.h"

namespace glossary
{
class WordDescriptionGeneratorMock : public WordDescriptionGenerator
{
public:
    MOCK_METHOD1(generateWordsDescriptions, wordDescriptionRepository::WordsDescriptions(
                                                const wordDescriptionRepository::EnglishWords&));
    MOCK_METHOD1(generateWordDescription, boost::optional<wordDescriptionRepository::WordDescription>(
                                              const wordDescriptionRepository::EnglishWord&));
};
}