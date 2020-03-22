#pragma once
#include "gmock/gmock.h"

#include "WordsBuilder.h"

class WordsBuilderMock : public WordsBuilder
{
public:
    MOCK_CONST_METHOD2(buildWords, Words(const translationRepository::Translations&,
                                         const wordsDescriptionsDb::WordsDescriptions&));
};
